//#include <Servo.h>
//
//Servo myServo;  // create a servo object
//
//void setup() {
//  myServo.attach(6); // attaches the servo on pin 9 to the servo object
//}
//
//void loop() {
//  // set the servo position
//  for (int i = 0; i < 181; i++) {
//     myServo.write(i);
//     delay(15);
//  }
//}

#include <IRremote.h>

int motorPin = 10;
int sensorPin = 6;
int velocity = 0;
IRrecv irrecv(sensorPin);
decode_results results;

void setup() {
   pinMode(motorPin, OUTPUT);
   Serial.begin(9600);
   irrecv.enableIRIn();
   irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){
    
     if (results.value == 0xFF629D) {
      Serial.println("+");
      Serial.println(velocity);
      velocity = velocity + 30;
      if (velocity > 255) {
        velocity = 255;
      }
      Serial.println(velocity);
      int val = constrain(velocity, 0, 255);
      analogWrite(motorPin, val);
      delay(1000);
    }

    if (results.value == 0xFFA857) {
      Serial.println("-");
      Serial.println(velocity);
      velocity = velocity - 30;
      if (velocity < 0) {
        velocity = 0;
      }
      Serial.println(velocity);
      int val = constrain(velocity, 0, 255);
      analogWrite(motorPin, val);
      delay(1000);
    }

    if (results.value != 0xFFA857 && results.value != 0xFF629D) {
      analogWrite(motorPin, velocity);
    }
    
//    if (results.value == 0xFFA857) {
//      Serial.println("-");
//      Serial.println(velocity);
//      velocity = velocity - 30;
//      if (velocity < 0) {
//        velocity = 0;
//      }
//      int val = constrain(velocity, 0, 255);
//      analogWrite(motorPin, val);  
//    }
//    
//    if (results.value != 0xFFA857 && results.value != 0xFF629D) {
//      analogWrite(motorPin, velocity);
//    }
//    delay(1000);
//    Serial.println("delay");
    irrecv.resume(); 
  }
}
