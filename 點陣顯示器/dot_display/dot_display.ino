#include <Arduino.h>
#include <LedControl.h>
int data_pin = 12;
int clk_pin = 11;
int cs_pin = 10;
LedControl dot_Led = LedControl(data_pin, clk_pin, cs_pin, 1);

//小綠人動畫
byte dot_Led_control [5][8] = {
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
}
};

//程式設定
void setup()
{
    dot_Led.shutdown(0, false);
    dot_Led.setIntensity(0, 2);
    dot_Led.clearDisplay(0);
}
void loop()
{
    //橫排（row）與直排（col） 
    for(int row=0; row<8; row++){
        dot_Led.setRow(0, row, dot_Led_control[0][row]);
    }
    delay(1000);
    for(int row=0; row<8; row++){
        dot_Led.setRow(0, row, dot_Led_control[1][row]);
    }
    delay(1000);
    for(int row=0; row<8; row++){
        dot_Led.setRow(0, row, dot_Led_control[2][row]);
    }
    delay(1000);
    for(int row=0; row<8; row++){
        dot_Led.setRow(0, row, dot_Led_control[3][row]);
    }
    delay(1000);
    for(int row=0; row<8; row++){
        dot_Led.setRow(0, row, dot_Led_control[4][row]);
    }
    delay(1000);
}
