int platform = 3;
int push_signal = 4;
int data_pin = 2;
//控制哪顆七段顯示器要發光
int control_10 = 9; 
int control_1 =8;
int button_pin = 5;
const byte G_LED = 10; //綠燈
const byte Y_LED = 11; //黃燈
const byte R_LED = 12; //紅燈
bool Control_State ; //控制器變數

//設定一個二維陣列，共十組 
int Seven_Areas[10] = {
  0x7E, 0x30, 0x6D, 0x79, 0x33,
  0x5B, 0x5F, 0x70, 0x7F, 0x73
};

void setup()
{
    pinMode(platform, 1);
    pinMode(push_signal, 1);
    pinMode(data_pin, 1);
    pinMode(control_10, 1);
    pinMode(control_1, 1);
    pinMode(G_LED, 1);
    pinMode(Y_LED, 1);
    pinMode(R_LED, 1);
    pinMode(button_pin, 0);
    digitalWrite(control_10, 1);
    digitalWrite(control_1 , 1);
    
}

//函式
//輸入一個數字決定7段顯示器顯示1-9
//NM為該函式所輸入值，在二維陣列的第幾排（數字幾）
void Seven_Write(byte NM)
{
    int NM10 = NM /10;
    int NM1 = NM %10 ;
    int time =1000; //設定要幾毫秒
    int twodisplaydelay =5; //設定兩個顯示器之間的延遲
    while (1)
    {
        //顯示十位數
        digitalWrite(control_1, 1);
        digitalWrite(platform, 0); //重置平台
        shiftOut(data_pin, push_signal, LSBFIRST, Seven_Areas[NM10]);
        digitalWrite(platform, 1); //送出平台
        digitalWrite(control_10, 0);
        delay(twodisplaydelay);
        //顯示個位數
        digitalWrite(control_10, 1);
        digitalWrite(platform, 0); //重置平台
        shiftOut(data_pin, push_signal, LSBFIRST, Seven_Areas[NM1]);
        digitalWrite(platform, 1); //送出平台
        digitalWrite(control_1, 0);
        delay(twodisplaydelay);
        //時間計算
        time = time - 2*twodisplaydelay ;
        if (time <0)
        {
            break;
        }
    }
}

//紅綠燈函式
//1=關閉七段顯示器
//0=紅綠燈重置
void light (byte light_N){
  if (light_N == 0)
  {
        digitalWrite(G_LED, 0);
        digitalWrite(Y_LED, 0);
        digitalWrite(R_LED, 0);
  }
  if (light_N == 1)
  {
        digitalWrite(control_1, 1);
        digitalWrite(control_10, 1);
  }
}

//主程式
void loop()
{
  {
    Control_State = digitalRead(button_pin);
    if (Control_State == 0) //控制器已斷開
    {
        light(0);
        light(1);
        digitalWrite(Y_LED, 1);
        delay(1000);
        digitalWrite(Y_LED, 0);
        delay(1000);
    }
    else if(Control_State == 1) //控制器已連接
    {
       //紅=>黃/初始
       light(0);
       light(1);
       digitalWrite(G_LED, 1);
       delay(5000);
       //綠->黃
       light(0);
       digitalWrite(Y_LED, 1);
       delay(2000);
       //黃=>紅
       light(0);
       digitalWrite(R_LED, 1);
       for (byte NM = 20; NM > 0; NM--)
       {
           Seven_Write(NM-1);
       }
       light(1);
       delay(1000);
    }

}
}
