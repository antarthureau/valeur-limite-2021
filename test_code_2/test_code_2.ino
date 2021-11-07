#include <SoftwareSerial.h>
SoftwareSerial co2Serial(6, 7); // define MH-Z19 RX TX
unsigned long startTime = millis();
int co2SensorPin=9;
const unsigned int TRIG_PIN=13;
const unsigned int ECHO_PIN=12;
const unsigned int BAUD_RATE=9600;
int relayCtrlPin = 8;
int dt = 10; //latence en ms
int dtco2 = 10; //duree loop co2
unsigned long getDataTimer = 0;
int j;



//variables a changer__________________________//
int maxDist = 50; //distance maximum en cm
int minDist = 7;  //distance minimum en cm
int vibDuration = 5000; //duree de vibration en ms
//__________________________________________________//



void setup() {
    
  pinMode(co2SensorPin, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(relayCtrlPin, OUTPUT);
  Serial.begin(BAUD_RATE);
  co2Serial.begin(BAUD_RATE);
}

void loop() {
  
//ultrasonic sensor data in__________________________//
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
 const unsigned long duration= pulseIn(ECHO_PIN, HIGH);
 int distance= duration/29/2;
//__________________________________________________//


//relay logic_______________________________________//
if (distance <= maxDist && distance >+ minDist) {
  digitalWrite(relayCtrlPin, HIGH);
  delay(vibDuration);
}
else {
  digitalWrite(relayCtrlPin, LOW);
}

//__________________________________________________//


/*
//ultrasonic data serialprint_______________________//
 if(duration==0){
  Serial.println("DISTANCE----------------------");
   Serial.println("Warning: no pulse from sensor");
   Serial.println("------------------------------");
   Serial.println("");
   } 
  else{
  Serial.println("DISTANCE----------------------");;
      Serial.print("distance to nearest object: ");
      Serial.print(distance);
      Serial.println(" cm");
      Serial.println("------------------------------");
      Serial.println("");
  }
//__________________________________________________//
*/



//CO2 sensor data serialprint_______________________//
Serial.println("CO2---------------------------");
  Serial.print("Time from start: ");
  Serial.print((millis() - startTime) / dtco2);
  Serial.println(" s");
  int ppm_uart = readCO2UART();
  int ppm_pwm = readCO2PWM();
  delay(dtco2);
}

int readCO2UART(){
  byte cmd[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
  byte response[9]; // for answer

  Serial.println("Sending CO2 request...");
  co2Serial.write(cmd, 9); //request PPM CO2

  // clear the buffer
  memset(response, 0, 9);
  int i = 0;
  while (co2Serial.available() == 0) {
//    Serial.print("Waiting for response ");
//    Serial.print(i);
//    Serial.println(" s");
    delay(dtco2);
    i++;
  }
  if (co2Serial.available() > 0) {
      co2Serial.readBytes(response, 9);
  }
  // print out the response in hexa
  for (int i = 0; i < 9; i++) {
    Serial.print(String(response[i], HEX));
    Serial.print("   ");
  }
  Serial.println("");

  // checksum
  byte check = getCheckSum(response);
  if (response[8] != check) {
    Serial.println("Checksum not OK!");
    Serial.print("Received: ");
    Serial.println(response[8]);
    Serial.print("Should be: ");
    Serial.println(check);
  }
  
  // ppm
  int ppm_uart = 256 * (int)response[2] + response[3];
  Serial.print("PPM UART: ");
  Serial.println(ppm_uart);

  // temp
  byte temp = response[4] - 40;
  Serial.print("Temperature? ");
  Serial.println(temp);

  // status
  byte status = response[5];
  Serial.print("Status? ");
  Serial.println(status); 
  if (status == 0x40) {
    Serial.println("Status OK"); 
  }
  
  return ppm_uart;
}

byte getCheckSum(char *packet) {
  byte i;
  unsigned char checksum = 0;
  for (i = 1; i < 8; i++) {
    checksum += packet[i];
  }
  checksum = 0xff - checksum;
  checksum += 1;
  return checksum;
}

int readCO2PWM() {
  unsigned long th, tl, ppm_pwm = 0;
  do {
    th = pulseIn(9, HIGH, 1004000) / 1000;
    tl = 1004 - th;
    ppm_pwm = 5000 * (th-2)/(th+tl-4);
  } while (th == 0);
  Serial.print("PPM PWM: ");
  Serial.println(ppm_pwm);
  Serial.println("------------------------------");
  Serial.println("");
  return ppm_pwm;  
//__________________________________________________//



delay(dt);
 
 }
