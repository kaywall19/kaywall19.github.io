// import an arduino library for the IR remote functionality
#include <IRremote.h>

// declare arduino pin 6 as the pin connected to the sensor
const int sensor_pin = 6;
// declare arduino pin 10 as the pin connected to the transistor
const int transistor_pin = 10;

// instantiates an object of type irrecv
IRrecv irrecv(sensor_pin);
// creating a variable of type decode_results to store the sensor input
decode_results results;


// the setup function runs once the reset is pressed or the board is powered
void setup(){
  
  // sets the speed of serial monitor --> Arduino communication to 9600 bits per second
  Serial.begin(9600);
  // use the properties of the irrecv object to enable the IR sensor and begin receiving process
  irrecv.enableIRIn();  
  // Tells the light on the arduino to blink if the receiver gets a signal
  irrecv.blink13(true);
  // initializes the transistor pin as output
  pinMode(transistor_pin, OUTPUT);
  
}

// the loop function runs continously
void loop(){

  // tries to receive an IR code. If no code is received, the expression returns false. If a code
  // is received, the expression returns true and the code is stored in results.
  if (irrecv.decode(&results)){

    // checks to see if the results hex is equal to the hex that corresponds with the vol + button
    if (results.value == 0xFF629D) {
      
      // prints the button to the screen for easy debugging
      Serial.println("+");
      
      // begins a slow brightening of the LED strip
      for (int i = 0; i < 256; i += 5) {
        // writes the current value of i to the transistor pin
        analogWrite(transistor_pin, i);
        // delay 20ms to observe change
        delay(20);
        // prints i so you can see the LED increase brightness along with i
        Serial.println(i);
      }
      
    }

    // checks to see if the results hex is equal to the hex that corresponds with the vol - button
    if (results.value == 0xFFA857) {
      
      // prints the button to the screen for easy debugging
      Serial.println("-");
      
      // begins a slow dimming of the LED strip
      for (int i = 255; i >= 0; i -= 5) {
        // writes the current value of i to the transistor pin
        analogWrite(transistor_pin, i);
        // delay 20ms to observe change
        delay(20);
        // prints i so you can see the LED dim along with i
        Serial.println(i);
      }
      
    }

    // resets the receiver so it can read another code
    irrecv.resume(); 
  }
}
