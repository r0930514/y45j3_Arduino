const byte Control =2; //控制器腳位
const byte G_LED = 3; //綠燈
const byte Y_LED = 4; //黃燈
const byte R_LED = 5; //紅燈
bool Control_State ; //控制器變數

//設定一個二維陣列，共十組 
byte Seven_Areas[10][7] = {
//  {a,b,c,d,e,f,g}
//  {6,7,8,9,10,11,12}
    {0,1,1,1,1,1,1}, //0
    {0,0,0,1,0,0,1}, //1
    {1,0,1,1,1,1,0}, //2
    {1,0,1,1,0,1,1}, //3
    {1,1,0,1,0,0,1}, //4
    {1,1,1,0,0,1,1}, //5
    {1,1,1,0,1,1,1}, //6
    {0,1,1,1,0,0,1}, //7
    {1,1,1,1,1,1,1}, //8
    {1,1,1,1,0,1,1}, //9
};

void setup (){
    for (int i = 6; i < 14; i++) //將6-13的腳位全部設為輸出
    {
        pinMode(i, 1);
    }
    pinMode(Control, INPUT); //將控制器腳位設定為輸入
    
}

//函式
//輸入一個數字決定7段顯示器顯示1-9
//NM為該函式所輸入值，在二維陣列的第幾排（數字幾）
//i則為該排第幾個，因為有七個所以重複七次（判定開或關
void Seven_Write(byte NM){
    byte Pin = 6; //七段顯示器上的初始腳位
    for (byte i = 0; i < 7; i++)
    {
        digitalWrite(Pin, Seven_Areas[NM][i]);
        int t = Seven_Areas[NM][i];
        Pin ++;
    }
}

//紅綠燈函式
//0=關閉七段顯示器
//1=紅綠燈重置
void Light(byte Light_N){
    if(Light_N == 0){
        for (int i = 6; i <13 ; i++)
        {
        digitalWrite(i, 0);
        }
    }
    if (Light_N == 1)
    {
        for (int i = 3; i < 6 ; i++)
        {
        digitalWrite(i, 0);
        }
    }
    
}
void loop()
{
    Control_State = digitalRead(Control);
    if (Control_State == 0) //控制器已斷開
    {
        Light(0);
        Light(1);
        digitalWrite(Y_LED, 1);
        delay(1000);
        digitalWrite(Y_LED, 0);
        delay(1000);
    }
    else if(Control_State == 1) //控制器已連接
    {
       //紅=>黃/初始
       Light(0);
       Light(1);
       digitalWrite(G_LED, 1);
       delay(5000);
       //綠->黃
       Light(1);
       digitalWrite(Y_LED, 1);
       delay(2000);
       //黃=>紅
       Light(1);
       digitalWrite(R_LED, 1);
       for (byte NM = 10; NM > 0; NM--)
       {
           delay(1000);
           Seven_Write(NM-1);
       }
       Light(0);
       delay(1000);
    }
    
}

