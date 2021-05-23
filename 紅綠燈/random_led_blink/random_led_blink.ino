const int BUTTON_PIN = 7;       // 按鈕的接腳設為7號腳位
const int GREEN_LED_PIN =  6;   // 設定LED_GREEN的接腳為6號腳位
const int RED_LED_PIN =  5;     // 設定LED_RED的接腳為5號腳位
const int YELLOW_LED_PIN =  4;  // 設定LED_YELLOW的接腳為4號腳位
int buttonState = 0;            // 按鈕的狀態


void setup() {
  pinMode(GREEN_LED_PIN, OUTPUT);     // 設定LED_GREEN的PIN腳為輸出
  pinMode(RED_LED_PIN, OUTPUT);       // 設定LED_RED的PIN腳為輸出
  pinMode(YELLOW_LED_PIN, OUTPUT);    // 設定LED_YELLOW的PIN腳為輸出
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 設定按鈕的接腳為輸入，因為我們要讀取它的狀態
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
    delay (2500);                          //延遲2.5秒
    digitalWrite(RED_LED_PIN, 0);          //LED_RED關閉
  }
}
