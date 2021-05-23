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
  pinMode(2, OUTPUT);  //設定2號腳位為輸出
  pinMode(3, OUTPUT);  //設定3號腳位為輸出
  pinMode(4, OUTPUT);  //設定4號腳位為輸出
  pinMode(5, OUTPUT);  //設定5號腳位為輸出
  pinMode(6, OUTPUT);  //設定6號腳位為輸出
  pinMode(7, OUTPUT);  //設定7號腳位為輸出
  pinMode(8, OUTPUT);  //設定8號腳位為輸出
  pinMode(9, OUTPUT);  //設定9號腳位為輸出
  digitalWrite(9, 0);  // 關閉小數點
}

// 在七段顯示器上顯示指定的一個數字從0~9 
void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte seg = 0; seg < 7; ++seg) {
    digitalWrite(pin, seven_seg_digits[digit][seg]);
    ++pin;
  }
}

void loop() {
  for (byte digit = 10; digit > 0; --digit) {
    delay(1000);
    sevenSegWrite(digit - 1); 
  }
 delay(4000);  // 暫停 4 秒鐘
}
