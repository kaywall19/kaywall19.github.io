/*
  A1 Blink
  January 9, 2020
  Kay Waller
  HCDE 439

  This program turns on three LED's independently of each other. This program
  borrows heavily from:

    Scott Fitzgerald (modified 8 May 2014)
    Arturo Guadalupi (modified 2 Sep 2016)
    Colby Newman (modified 8 Sep 2016)
*/

// the setup function runs once the reset is pressed or the board is powered.
void setup() {
  
  // initialize digital pin 10 as an output. This is the far right yellow LED.
  pinMode(10, OUTPUT);
  
  // initialize digital pin 6 as an output. This is the middle white LED.
  pinMode(6, OUTPUT);
  
  // initialize digital pin 2 as an output. This is the far left yellow LED.
  pinMode(2, OUTPUT);
  
}

// the loop function runs continously and turns all LED's on and off. 
void loop() {

  // for the far right yellow light
  // turn the far right yellow LED on
  digitalWrite(10, HIGH);
  // wait for 4 seconds
  delay(4000);
  // turn the far right yellow LED off
  digitalWrite(10, LOW);
  // wait for 1/10th of a second
  delay(10);  

  // for the middle white light
  // turn the middle white LED on       
  digitalWrite(6, HIGH); 
  // wait for 1/4th of a second
  delay(250);  
  // turn the middle white LED off       
  digitalWrite(6, LOW);  
  // wait for 1/10th of a second
  delay(10);    
  
  // for the far left yellow light
  // turn the far left yellow light on
  digitalWrite(2, HIGH); 
  // wait for 1 second
  delay(1000);  
  // turn the far left yellow LED off        
  digitalWrite(2, LOW);
  // wait 1/10th of a second
  delay(10);

}
