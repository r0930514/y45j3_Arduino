#include <Led4digit74HC595.h>
#include <Arduino.h>
#include <LedControl.h>

int data_pin = 12;
int clk_pin = 11;
int cs_pin = 10;
LedControl dot_Led = LedControl(data_pin, clk_pin, cs_pin, 1);
int BUTTON_PIN = 7;       // 按鈕的接腳設為7號腳位
int GREEN_LED_PIN =  6;   // 設定LED_GREEN的接腳為6號腳位
int RED_LED_PIN =  5;     // 設定LED_RED的接腳為5號腳位
int YELLOW_LED_PIN =  4;  // 設定LED_YELLOW的接腳為4號腳位
int buttonState = 0;
Led4digit74HC595 myLedDisplay(A2, A1, A0);	// 接腳:(SCLK, RCLK, DIO)

//小綠人動畫
byte dot_Led_control [9][8] = {
{
  B01100000,
  B01100000,
  B00110000,
  B01111000,
  B00011000,
  B00110100,
  B00100010,
  B01100110
},{
  B01100000,
  B01100000,
  B00110000,
  B01111100,
  B01011010,
  B00110100,
  B01100010,
  B01000010
},{
  B01100000,
  B01100000,
  B00110000,
  B01111100,
  B10110010,
  B00011000,
  B01100110,
  B00000010
},{
  B11000000,
  B11000000,
  B01111000,
  B01100100,
  B10110000,
  B00101000,
  B11000110,
  B00000010
},{
  B11000000,
  B11000000,
  B01100000,
  B01111000,
  B10110100,
  B00111010,
  B00100110,
  B11100010
},{
  B11000000,
  B11000000,
  B01100000,
  B01111000,
  B10110100,
  B00110010,
  B01001100,
  B11000100
},{
  B11000000,
  B11000000,
  B01100000,
  B01111000,
  B01110100,
  B00110000,
  B01011000,
  B00101000
},{
  B01100000,
  B01100000,
  B00110000,
  B00111000,
  B00011000,
  B00010100,
  B00011100,
  B00000100
},{
  B00011000,
  B00011000,
  B00111100,
  B01011010,
  B01011010,
  B00011000,
  B00110100,
  B01100110
}
};

//函式
//輸入一個數字決定7段顯示器顯示1-9
//NM為該函式所輸入值，在二維陣列的第幾排（數字幾）
void Seven_Write(byte NM)
{
  int time = 0;
  int animation = 0;
  int fastAnimation =0;
    while (1)
    {
		myLedDisplay.loopShow();	// 每一次loop都要呼叫這個函式
  	myLedDisplay.setNumber(NM);  //顯示數字內容
		delay(4);
    time = time +4;
    if (time % 124 == 0 and NM > 5)
    {
      animation = time / 124 -1;
      for(int row=0; row<8; row++){
        dot_Led.setRow(0, row, dot_Led_control[animation][row]);
      }
    }
    if (time % 62 == 0 and NM < 6)
      {
        fastAnimation = time / 62 -1;
        if (fastAnimation > 8)
        {
          fastAnimation = fastAnimation -8;
        }
        
        for(int row=0; row<8; row++){
          dot_Led.setRow(0, row, dot_Led_control[fastAnimation][row]);
        }
      }
    
    if (time >992)
    {
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
}


void loop() {
	buttonState = digitalRead(BUTTON_PIN);   //讀取按鍵的狀態 
    if(buttonState == 1){                  //如果按鈕沒被按下
        digitalWrite(GREEN_LED_PIN, 0);        //LED_GREEN關閉
        digitalWrite(RED_LED_PIN, 0);          //LED_RED關閉
        digitalWrite(YELLOW_LED_PIN, HIGH);    //LED_YELLOW開啟
        for(int row=0; row<8; row++){
          
          dot_Led.setRow(0, row, dot_Led_control[8][row]);
        }
        delay (1000);                          //延遲1秒
        dot_Led.clearDisplay(0);
        digitalWrite(YELLOW_LED_PIN, 0);       //LED_YELLOW關閉
        delay (1000);                          //延遲1秒
    }
    else{                                    //如果沒滿足上述條件則執行
        digitalWrite(GREEN_LED_PIN, HIGH);     //LED_GREEN開啟 
        delay(5000);
        digitalWrite(GREEN_LED_PIN, 0);        //LED_GREEN關閉
        digitalWrite(YELLOW_LED_PIN, HIGH);    //LED_YELLOW開啟
        delay (1000);                          //延遲1秒
        digitalWrite(YELLOW_LED_PIN, 0);       //LED_YELLOW關閉
        digitalWrite(RED_LED_PIN, HIGH);       //LED_RED開啟
        delay(2000);
        for(int i=15; i>0; i--){
            Seven_Write(i);
        }
        for(int row=0; row<8; row++){
          dot_Led.setRow(0, row, dot_Led_control[8][row]);
        }     
        delay(3000);               
        digitalWrite(RED_LED_PIN, 0);          //LED_RED關閉
}
}