//bonjour

const unsigned int TRIG_PIN=13;
const unsigned int ECHO_PIN=12;
const unsigned int BAUD_RATE=9600;
int relayCtrlPin = 8;

int dt = 50; //latence en ms
int maxDist = 50; //distance maximum en cm
int minDist = 7;  //distance minimum en cm


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
}
else {
  digitalWrite(relayCtrlPin, LOW);
}
//__________________________________________________//

//ultrasonic data serialprint_______________________//
 if(duration==0){
   Serial.println("Warning: no pulse from sensor");
   } 
  else{
      Serial.print("distance to nearest object: ");
      Serial.print(distance);
      Serial.println(" cm");
  }
//__________________________________________________//
 delay(dt);
 }
