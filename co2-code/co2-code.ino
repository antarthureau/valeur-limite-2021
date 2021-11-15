#include <Arduino.h>
#include "MHZ19.h"                                        
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
int rxPin=6;  // MHZ19 Tx to Rx (noir)
int txPin=7;  // MHZ19 Rx to Tx (jaune)
int baudRate=9600;
int dt=50;
MHZ19 myMHZ19;
SoftwareSerial mySerial(rxPin,txPin);

void setup()
{
Serial.begin(baudRate);
mySerial.begin(baudRate); 
myMHZ19.begin(mySerial); 
myMHZ19.autoCalibration();
lcd.begin(16,2); //start the LCD and setup its width and height (16, 2)
}

void loop()
{
int CO2; 
CO2 = myMHZ19.getCO2();// Request CO2 (as ppm)
lcd.setCursor(0,0);                      
lcd.print("CO2 ppm");  
lcd.setCursor(0,1);                      
lcd.print(CO2);                               
delay(dt);
}
