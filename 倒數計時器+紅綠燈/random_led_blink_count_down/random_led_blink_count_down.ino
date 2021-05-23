const int BUTTON_PIN = 9;       // 按鈕的接腳設為7號腳位
const int GREEN_LED_PIN =  10;   // 設定LED_GREEN的接腳為6號腳位
const int RED_LED_PIN =  11;     // 設定LED_RED的接腳為5號腳位
const int YELLOW_LED_PIN =  12;  // 設定LED_YELLOW的接腳為4號腳位
int buttonState = 0;            // 按鈕的狀態
// 七段顯示器製作倒數功能
// 利用八位元Bit運算方式來控制顯示LED的明滅
byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                 { 0,1,1,0,0,0,0 },  // = 1
                                 { 1,1,0,1,1,0,1 },  // = 2
                                 { 1,1,1,1,0,0,1 },  // = 3
                                 { 0,1,1,0,0,1,1 },  // = 4
                                 { 1,0,1,1,0,1,1 },  // = 5
                                 { 1,0,1,1,1,1,1 },  // = 6
                                 { 1,1,1,0,0,0,0 },  // = 7
                                 { 1,1,1,1,1,1,1 },  // = 8
                                 { 1,1,1,0,0,1,1 }   // = 9
                             };

void setup() {
  pinMode(GREEN_LED_PIN, OUTPUT);     // 設定LED_GREEN的PIN腳為輸出
  pinMode(RED_LED_PIN, OUTPUT);       // 設定LED_RED的PIN腳為輸出
  pinMode(YELLOW_LED_PIN, OUTPUT);    // 設定LED_YELLOW的PIN腳為輸出
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 設定按鈕的接腳為輸入，因為我們要讀取它的狀態
  pinMode(2, OUTPUT);  //設定2號腳位為輸出
  pinMode(3, OUTPUT);  //設定3號腳位為輸出
  pinMode(4, OUTPUT);  //設定4號腳位為輸出
  pinMode(5, OUTPUT);  //設定5號腳位為輸出
  pinMode(6, OUTPUT);  //設定6號腳位為輸出
  pinMode(7, OUTPUT);  //設定7號腳位為輸出
  pinMode(8, OUTPUT);  //設定8號腳位為輸出
}
//// 在七段顯示器上顯示指定的一個數字從0~9 
void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte seg = 0; seg < 7; ++seg) {
    digitalWrite(pin, seven_seg_digits[digit][seg]);
    ++pin;
  }
}

void loop() {
  
  buttonState = digitalRead(BUTTON_PIN);   //讀取按鍵的狀態 
     
  if(buttonState == LOW){                  //如果按鈕按下
    digitalWrite(GREEN_LED_PIN, 0);        //LED_GREEN關閉
    digitalWrite(RED_LED_PIN, 0);          //LED_RED關閉
    digitalWrite(YELLOW_LED_PIN, HIGH);    //LED_YELLOW開啟
    delay (1000);                          //延遲1秒
    digitalWrite(YELLOW_LED_PIN, 0);       //LED_YELLOW關閉
    delay (1000);                          //延遲1秒
  }
  else{                                    //如果沒滿足上述條件則執行
    digitalWrite(GREEN_LED_PIN, HIGH);     //LED_GREEN開啟
    delay (5000);                          //延遲5秒 
    digitalWrite(GREEN_LED_PIN, 0);        //LED_GREEN關閉
    digitalWrite(YELLOW_LED_PIN, HIGH);    //LED_YELLOW開啟
    delay (1000);                          //延遲1秒
    digitalWrite(YELLOW_LED_PIN, 0);       //LED_YELLOW關閉
    digitalWrite(RED_LED_PIN, HIGH);       //LED_RED開啟
    //開始倒數從0~9
    for (byte digit = 10; digit > 0; --digit) { 
    delay(1000);                           //延遲4秒
    sevenSegWrite(digit - 1); 
  }
    delay (2500);                          //延遲2.5秒
    digitalWrite(RED_LED_PIN, 0);          //LED_RED關閉
  }
}
