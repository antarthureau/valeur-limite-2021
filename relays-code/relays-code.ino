const unsigned int TRIG_PIN=13;
const unsigned int ECHO_PIN=12;
const unsigned int BAUD_RATE=9600;
int relayCtrlPin = 8;
int dt = 50; //latence en ms
unsigned long getDataTimer = 0;



//variables a changer__________________________//
int maxDist = 50; //distance maximum en cm
int minDist = 7;  //distance minimum en cm
int vibDuration = 5000; //duree de vibration en ms
//__________________________________________________//



void setup() {    
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(relayCtrlPin, OUTPUT);
  Serial.begin(BAUD_RATE);
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

delay(dt);
 
 }
