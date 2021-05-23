
void setup() {
  pinMode(13, OUTPUT); //設定13號腳位LED燈為輸出
}

void loop() {
  digitalWrite(13, HIGH);   //13號腳位LED燈亮燈
  delay(300);               //延遲0.3秒        
  digitalWrite(13, LOW);    //13號腳位LED燈滅
  delay(300);               //延遲0.3秒        
}
