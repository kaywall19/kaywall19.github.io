/*
  A2 Fade
  January 16, 2020
  Kay Waller
  HCDE 439

  This program uses a button to trigger LED's fading and blinking. This program
  borrows heavily from "Button," by:

    Dojo Dave (created 2005)
    Tom Igoe (modified 30 Aug 2011)
*/

// the setup function runs once the reset is pressed or the board is powered
void setup() {

  // for-loop initializes LED pins 5 and 6 as output. These pins can use analogWrite
  for (int thisPin = 5; thisPin < 7; thisPin++) {  
    // the respective LED pin is initialized as output
    pinMode(thisPin, OUTPUT);
  }

  // initializes the pin connected to the button as input
  pinMode(2, INPUT);
  // turn pin 6 LED on
  digitalWrite(6, HIGH);
  // turn pin 5 LED off
  digitalWrite(5, LOW);
}

// the loop function runs continously and fades and blinks all LED's
void loop() {

  // reads the state of the input pin 2 connected to the button
  boolean buttonState = digitalRead(2);  
  
  // if-check used to test whether the button has been pressed or not  
  if (buttonState == HIGH) {
    
    // for-loop used to fade both LED's in an out 3 times
    for (int i = 0; i <= 2; i ++) {
      // variable used to keep track of pin 5 LED's opposite fading to pin 6 LED
      int inverse = 0;    
      // for-loop that gradually brightens pin 5 LED and fades pin 6 LED
      for (int fade = 255; fade >= 0; fade -= 5) {
        // set the dimness of pin 6 LED to the for-loop variable fade
        analogWrite(6, fade);
        // set the brightness of pin 5 LED to the variable inverse
        analogWrite(5, inverse);
        // increase inverse so the LED gets brighter by 1 each time
        inverse = inverse + 1;
        // wait for 30 milliseconds
        delay(30);
      }  

      // for-loop that gradually fades pin 5 LED and brightens pin 6 LED
      for (int fade = 0; fade <= 255; fade += 5) {
        // set the brightness of pin 6 LED to the for-loop variable fade
        analogWrite(6, fade);
        // set the dimness of pin 5 LED to the variable inverse
        analogWrite(5, inverse);
        // decrement inverse so the LED fades by 1 each time
        inverse = inverse - 1;
        // wait for 30 milliseconds
        delay(30);
      }
       
    } 

    // blink LED's so they're opposites for 4 times
    for (int blink = 0; blink < 4; blink ++) {
      // turn pin 5 LED on
      digitalWrite(5, HIGH);
      // turn pin 6 LED off
      digitalWrite(6, LOW);
      // wait for 400 milliseconds
      delay(400);
      // turn pin 5 LED off
      digitalWrite(5, LOW);
      // turn pin 6 LED on
      digitalWrite(6, HIGH);
      // wait for 400 milliseconds
      delay(400);  
    }

    // blink LED's so they're blinking at the same time for 3 times
    for (int blinkTwo = 0; blinkTwo < 3; blinkTwo ++) {
      // turn pin 5 LED on
      digitalWrite(5, HIGH);
      // turn pin 6 LED on
      digitalWrite(6, HIGH);
      // wait for 80 milliseconds
      delay(80);
      // turn pin 5 LED off
      digitalWrite(5, LOW);
      // turn pin 6 LED off
      digitalWrite(6, LOW);
      // wait for 80 milliseconds
      delay(80);  
    }

    // end the sequence by turning both of the LED's on
    // turn pin 5 LED on
    digitalWrite(5, HIGH);
    // turn pin 6 LED on
    digitalWrite(6, HIGH);   
  }
  
}
