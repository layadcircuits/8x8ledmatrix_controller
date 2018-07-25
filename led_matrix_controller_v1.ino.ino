/***************************************************************************
 This code integrates an Android App to control an 8x8 LED matrix over bluetooth.
 This code works with the App "LED Matrix With Aduino" from Play Store
 
 Author(s): C.D.Malecdan for Layad Circuits Electronics Engineering
 Revision: 1.0 - 2018/07/26 - initial creation
 Layad Circuits Electronics Engineering Supplies and Services
 B314 Lopez Bldg., Session Rd. cor. Assumption Rd., Baguio City, Philippines
 www.layadcircuits.com
 facebook.com/layadcircuits
 general: info@layadcircuits.com
 sales: sales@layadcircuits.com
 +63-916-442-8565
 ***************************************************************************/

#include <SoftwareSerial.h>
#include <LedControl.h>

uint8_t PIN_DIN = A0;
uint8_t PIN_CLK =  A2;
uint8_t PIN_CS = A1;
uint8_t PIN_RX = 2;
uint8_t PIN_TX = 3;

SoftwareSerial bt(PIN_RX,PIN_TX);
LedControl ledmod=LedControl(PIN_DIN,PIN_CLK,PIN_CS,1);

uint8_t r,c;
char temp;
uint8_t cnt;
char buf[5]="";
uint32_t tmr;
char on;

void setup()
{
 ledmod.shutdown(0,false);       
 ledmod.setIntensity(0,5);
 ledmod.clearDisplay(0);
 Serial.begin(9600);
 bt.begin(9600);
 Serial.println(">");
}

void loop()
{ 
  if(bt.available())
  {
    tmr = millis();
    memset(buf,0,5);
    cnt=0;
    while(millis() - tmr < 100)
    {
      if(bt.available())
      {
         temp = bt.read();
         Serial.write(temp);
         if((temp >= '0' && temp <= '9') || temp == 'n' || temp == 'f')
         {
          buf[cnt++] = temp; 
         }
         else if(temp == 'r')
         {
            ledmod.clearDisplay(0);
            return;
         }
         if(temp == 'n' || temp == 'f') break;
         if(cnt>=3) break;
      }
    }
    r = buf[0] - 0x30;
    c = buf[1] - 0x30;
    on = buf[2];
    if(on == 'n') ledmod.setLed(0,r,c,true);
    else ledmod.setLed(0,r,c,false);
  }
}
