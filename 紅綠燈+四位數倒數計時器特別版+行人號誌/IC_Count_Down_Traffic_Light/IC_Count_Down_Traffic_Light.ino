#include <Led4digit74HC595.h>
#include <Arduino.h>
#include <LedControl.h>

const int data_pin = 12;
const int clk_pin = 11;
const int cs_pin = 10;
const int BUTTON_PIN = 7;       // 按鈕
const int GREEN_LED_PIN =  6;   // 綠燈
const int RED_LED_PIN =  5;     // 紅燈
const int YELLOW_LED_PIN =  4;  // 黃燈
int buttonState = 0; //按鈕狀態變數

LedControl dot_Led = LedControl(data_pin, clk_pin, cs_pin, 1);
Led4digit74HC595 myLedDisplay(A2, A1, A0);	// 接腳:(SCLK, RCLK, DIO)


//小綠人
const uint64_t dot_Led_control [] = {
  0x66442c181e0c0606, //0
  0x42462c5a3e0c0606, //1
  0x4066184d3e0c0606, //2
  0x4063140d261e0303, //3
  0x47645c2d1e060303, //4
  0x23324c2d1e060303, //5
  0x141a0c2e1e060303, //6
  0x203828181c0c0606, //7
  0x66442c181e0c0606, //8;重複一次
  0x42462c5a3e0c0606, //9
  0x4066184d3e0c0606, //10
  0x4063140d261e0303, //11
  0x47645c2d1e060303, //12
  0x23324c2d1e060303, //13
  0x141a0c2e1e060303, //14
  0x203828181c0c0606, //15
  0x662c185a5a3c1818, //16;此為停止
};

//函式：控制點陣顯示器用
//imageIndex 為 代入陣列 的第幾張圖像
void dotLedCortrol(uint64_t imageIndex){
  for (int i = 0; i < 8; i++) {
    byte row = (imageIndex >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      myLedDisplay.loopShow(); //讓行人號誌在運作的時候不要讓七段顯示器閃來閃去
      dot_Led.setLed(0, i, j, bitRead(row, j));
    }
  }
}

//函式:七段顯示器&點陣顯示器
void Seven_Write(byte NM)
{
  int time = 0;
  int animationIndex = 0;
  int fastAnimationIndex =0;
    while (1)
    {
		myLedDisplay.loopShow();	// 每一次loop都要呼叫這個函式
  	myLedDisplay.setNumber(NM);  //顯示數字內容
		delay(0.5);
    time = time +1;
    if (time%125 == 0) //已經過時間剛好能夠被125整除
    { 
      
      if (NM > 5) //並且時間還有5秒以上
      {
        if (time%250 == 0)
        {
            animationIndex = time/250-1;
            dotLedCortrol(dot_Led_control[animationIndex]);
        }
      } 
      if (NM < 6) //並且時間不到5秒
      {
          fastAnimationIndex = time/125 -1;
          dotLedCortrol(dot_Led_control[fastAnimationIndex]);
      }
    }
    if (time >2000)
    {
      myLedDisplay.sleep();
      break;
    }
    }
}


void setup() {
  	dot_Led.shutdown(0, false);
    dot_Led.setIntensity(0, 2);
    dot_Led.clearDisplay(0);
    pinMode(GREEN_LED_PIN, OUTPUT);     // 設定LED_GREEN的PIN腳為輸出
    pinMode(RED_LED_PIN, OUTPUT);       // 設定LED_RED的PIN腳為輸出
    pinMode(YELLOW_LED_PIN, OUTPUT);    // 設定LED_YELLOW的PIN腳為輸出
    pinMode(BUTTON_PIN, INPUT_PULLUP);  // 設定按鈕的接腳為輸入，因為我們要讀取它的狀態
    myLedDisplay.setDecimalPoint(0);
    dotLedCortrol(dot_Led_control[16]);
}


void loop() {
	buttonState = digitalRead(BUTTON_PIN);   //讀取按鍵的狀態 
    if(buttonState == 1){                  //如果按鈕沒被按下
        digitalWrite(GREEN_LED_PIN, 0);        //LED_GREEN關閉
        digitalWrite(RED_LED_PIN, 0);          //LED_RED關閉
        digitalWrite(YELLOW_LED_PIN, HIGH);    //LED_YELLOW開啟
        dotLedCortrol(dot_Led_control[16]); //行人號誌：停止 
        delay (1000);                          //延遲1秒
        dot_Led.clearDisplay(0);
        digitalWrite(YELLOW_LED_PIN, 0);       //LED_YELLOW關閉
        delay (1000);                          //延遲1秒
    }
    else{                                    //如果沒滿足上述條件則執行
        digitalWrite(GREEN_LED_PIN, HIGH);     //LED_GREEN開啟 
        delay(2000);
        digitalWrite(GREEN_LED_PIN, 0);        //LED_GREEN關閉
        digitalWrite(YELLOW_LED_PIN, HIGH);    //LED_YELLOW開啟
        delay (1000);                          //延遲1秒
        digitalWrite(YELLOW_LED_PIN, 0);       //LED_YELLOW關閉
        digitalWrite(RED_LED_PIN, HIGH);       //LED_RED開啟
        delay(2000);
        for(int i=15; i>0; i--){ //倒數計時&行人號誌
            Seven_Write(i);
        }
        dotLedCortrol(dot_Led_control[16]); //行人號誌：停止 
        delay(3000);               
        digitalWrite(RED_LED_PIN, 0);          //LED_RED關閉
}
}
