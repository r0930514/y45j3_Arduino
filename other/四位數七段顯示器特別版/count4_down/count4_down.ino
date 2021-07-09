/*
 * 本範程式為Arduino結合4位7段LED模組的範例程式
 * 針對4位，且有4個小數點的款式，模組是由2個74HC595控制
 * 程式由傑森創工提供
 * 由LuBossCzech/Led4digit74HC595範例程式進行簡化改寫
 * 
 * 請先安裝LuBossCzech/Led4digit74HC595函式庫，
 * 下載網址：
 * https://github.com/LuBossCzech/Led4digit74HC595
 * 
 * 粉絲團：https://www.facebook.com/jasonshow
 * 傑森創工購物網：https://www.jmaker.com.tw/
 * 傑森創工部落格：https://blog.jmaker.com.tw/
 */

#include <Led4digit74HC595.h>

Led4digit74HC595 myLedDisplay(A2, A1, A0);	// 接腳:(SCLK, RCLK, DIO)


//函式
//輸入一個數字決定7段顯示器顯示1-9
//NM為該函式所輸入值，在二維陣列的第幾排（數字幾）
void Seven_Write(byte NM)
{
    int time =1500; //設定要幾毫秒
	int twodisplaydelay =5; //設定兩個顯示器之間的延遲
    while (1)
    {
		myLedDisplay.loopShow();	// 每一次loop都要呼叫這個函式
  		myLedDisplay.setNumber(NM);  //顯示數字內容
		delay(twodisplaydelay);
		time = time - 2*twodisplaydelay ;        //時間計算
        if (time <0)
        {
            break;
        }
    }
}

void setup() {
  	Serial.begin(9600);
  	Serial.println("Start...");
	myLedDisplay.setDecimalPoint(0); //顯示第幾個小數點，最右側向左邊算起為1,2,3,4
}


void loop() {

	for(int i=10; i>0; i--){
		Seven_Write(i);
	}

	
}