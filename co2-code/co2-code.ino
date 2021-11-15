/*
CIRCUIT WIRING: 
NANO to LCD: pins 7,6,5,4,3,2 to RS,E,DB4,DB5,DB6,DB7
LCD to +5V: LED+ (with 220o resistor) and VO
LCD to GND: VO (with 1Ko resistor) and LED-
NANO to MH-Z19C: pins 8,9 to TX,RX
If the NANO isn't powered by USB, connect Vin to +5V and GND with the other GND
*/
#include <Arduino.h>
#include "MHZ19.h"                                        
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);                                   
int rxPin=8;
int txPin=9;
int baudRate=9600;
int dt=50;
int j;
MHZ19 myMHZ19;
SoftwareSerial mySerial(rxPin,txPin);

void setup()
{
Serial.begin(baudRate);
mySerial.begin(baudRate); 
myMHZ19.begin(mySerial); 
myMHZ19.autoCalibration();
lcd.begin(16,2);//start the LCD and setup its width and height (16, 2)
lcd.setCursor(0,0);
lcd.print("valeur limite");
delay(500);
lcd.clear();
for (j=0;j<=3;j=j+1){
lcd.setCursor(0,0);
lcd.print("loading");
delay(500);
lcd.clear();
delay(500);
}
lcd.clear();
}

void loop(){
{
int CO2; 
CO2 = myMHZ19.getCO2();//request CO2 as ppm
lcd.setCursor(0,0);                      
lcd.print("CO2 ppm");  
lcd.setCursor(0,1);                      
lcd.print(CO2);
Serial.println(CO2);                               
delay(dt);
}
}
