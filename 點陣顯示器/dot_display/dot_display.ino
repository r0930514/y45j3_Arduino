#include "Arduino.h"
#include "LedControl.h"
int data_pin = 12;
int clk_pin = 11;
int cs_pin = 10;
LedControl dot_Led = LedControl(data_pin, clk_pin, cs_pin, 1);
void setup()
{
    dot_Led.shutdown(0,false);
    dot_Led.setIntensity(0,15);
    dot_Led.clearDisplay(0);
}
void loop()
{
    //橫排（row）與直排（col） 
    for(int row=0; row<8; row++){
        for(int col=0; col<8; col++){
           dot_Led.setLed(0, row, col, 1);
        }
    }
}
