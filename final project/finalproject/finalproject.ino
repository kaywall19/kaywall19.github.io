/*
 * Kay Waller
 * Final Project
 * HCDE 439, Winter 2020
 * 04 March 2020
 * 
 * This project borrows from code examples by Paul Badger (for capacitive sensing),
 * Angelo Qiao (for DFPlayerMini), and David Mellis (for smoothing the capacative
 * sensing). 
 * 
 */


// THESE ARE LIBRARIES
// include the capacative sensor library
#include "CapacitiveSensor.h"
// include the arduino library
#include "Arduino.h"
// include the software serial library
#include "SoftwareSerial.h"
// include the DFPlayerMini (MP3 player) library
#include "DFRobotDFPlayerMini.h"
// END LIBRARIES


// THIS IS THE SMOOTHING CODE
// declaring value of int that determines amount the sensing values are smoothed
const int numReadings = 10;

// this section of code corresponds to the capacitive sensor in the otter's belly
// declare variable to store the readings from the sensor input as an array of the declared length
int readings_belly[numReadings];
// declare variable to keep track of the index of the current reading
int readIndex_belly = 0;
// declare variable to keep track of running total of inputs
int total_belly = 0;             
// declare variable to store the average (smoothed) value of all readings
int average_belly = 0;

// this section of code corresponds to the capacitive sensor in the otter's nose
// declare variable to store the readings from the sensor input as an array of the declared length
int readings_nose[numReadings];
// declare variable to keep track of the index of the current reading
int readIndex_nose = 0;
// declare variable to keep track of running total of inputs
int total_nose = 0;
// declare variable to store the average (smoothed) value of all readings
int average_nose = 0;
// SMOOTHING CODE ENDS


// THIS IS CALIBRATING CODE
// sets the initial value for calibration for the belly
int calibrating_belly = 0;
// CALIBRATING CODE ENDS


// THIS IS DFPLAYERMINI CODE
// instantiates a SoftwareSerial object with RX, TX pins so the arduino can communicate with the component
SoftwareSerial mySoftwareSerial(10, 11);
// create a DFPlayer object to access properties later
DFRobotDFPlayerMini myDFPlayer;
// DFPLAYERMINI CODE ENDS


// THIS IS CAPACATIVE SENSING CODE
// creates a capacitive sensing object with pin 4 as the sensor pin, and 2 as the receiving
CapacitiveSensor belly = CapacitiveSensor(4,2);
// creates a capacitive sensing object with pin 6 as the sensor pin, and 8 as the receiving
CapacitiveSensor nose = CapacitiveSensor(6,8);
// CAPACITIVE SENSING CODE ENDS


// THIS IS BREAKPOINT CODE
// declares the variable to store the previous value of the sensor. Used for determining sound breakpoint
int previousVal_belly = 1000;
// declares the variable to store the previous value of the sensor. Used for determining sound breakpoint
int previousVal_nose = 1000;
// BREAKPOINT CODE ENDS

//the setup function runs once the reset is pressed or the board is powered
void setup() {

  // sets the speed of Arduino --> DFPlayerMini communication to 9600
  mySoftwareSerial.begin(9600);
  // sets the speed of Arduino communication to 9600
  Serial.begin(9600);

  // prints status of DFPlayerMini for debugging purposes
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  // prints status of DFPlayerMini for debugging purposes
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  // if there isn't communication with the DFPlayerMini
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    // prints error message for debugging purposes
    Serial.println(F("Unable to begin:"));
    // prints helpful debugging message
    Serial.println(F("1.Please recheck the connection!"));
    // prints helpful debugging message
    Serial.println(F("2.Please insert the SD card!"));
    // repeat this process while the DFPlayerMini is still not communicating
    while(true);
  }

  // if the communication between the arduino and the DFPlayerMini has started, print a success message
  Serial.println(F("DFPlayer Mini online."));

  // FOR THE BELLY
  // for loop that goes through the readings array
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    // sets each index to 0
    readings_belly[thisReading] = 0;
  }
  // END THE BELLY

  // FOR THE NOSE
  // for loop that goes through the readings array
  for (int thisReading2 = 0; thisReading2 < numReadings; thisReading2++) {
    // sets each index to 0
    readings_nose[thisReading2] = 0;
  }
  // END THE NOSE

  
  // sets the volume of the speaker (a value from 0 - 30)
  myDFPlayer.volume(25);
  
}



//the loop function runs continously
void loop() {

  // SMOOTHING CODE FOR BELLY
  // subtracts the last reading so the array doesn't have old values
  total_belly = total_belly - readings_belly[readIndex_belly];
  // read from the sensor and store the value in the array
  readings_belly[readIndex_belly] = belly.capacitiveSensor(30);
  // add the reading to the total
  total_belly = total_belly + readings_belly[readIndex_belly];
  // move forward to the next index in the array
  readIndex_belly = readIndex_belly + 1;

  // if the end of the array has been reached
  if (readIndex_belly >= numReadings) {
    // return to the beginning of the array
    readIndex_belly = 0;
  }

  // calculate the average of the readings
  average_belly = total_belly / numReadings;
  // print the sensor number to the screen for debugging purposes
  Serial.print("1: ");
  // print the smoothed sensor value to the screen for debugging purposes
  Serial.println(average_belly);
  // END SMOOTHING CODE FOR BELLY


  // SMOOTHING CODE FOR NOSE
  // subtracts the last reading so the array doesn't have old values
  total_nose = total_nose - readings_nose[readIndex_nose];
  // read from the sensor and store the value in the array
  readings_nose[readIndex_nose] = nose.capacitiveSensor(30); 
  // add the reading to the total
  total_nose = total_nose + readings_nose[readIndex_nose];
  // move forward to the next index in the array
  readIndex_nose = readIndex_nose + 1;

  // if the end of the array has been reached
  if (readIndex_nose >= numReadings) {
    // return to the beginning of the array
    readIndex_nose = 0;
  }

  // calculate the average of the readings
  average_nose = total_nose / numReadings;
  // print the sensor number to the screen for debugging purposes
  Serial.print("2: ");
  // print the smoothed sensor value to the screen for debugging purposes
  Serial.println(average_nose);
  // END SMOOTHING CODE FOR NOSE


  // calculate if the smoothed value is significantly larger than the previous value (meaning it was touched)
  int touched_belly = average_belly - 3;
  // calculate if the smoothed value is significantly larger than the previous value (meaning it was touched)
  int touched_nose = average_nose - 5;

  // if the new value for the belly is still larger than the previous value with some subtractions, that means the area was pressed
  if (touched_belly > previousVal_belly && calibrating_belly > 10) {
    // play the first track on the mp3 player
    myDFPlayer.play(1);
    // wait until the 7-second track finishes
    delay(7000);
    // if the new value for the nose is still larger than the previous value with some subtractions, that means the area was pressed
  } else if (touched_nose > previousVal_nose) {
    // play the second track on the mp3 player
    myDFPlayer.play(2);
    // wait for the 9-second track to finish
    delay(9000);
  }

  // set the old current value to the new previous value for the belly sensor
  previousVal_belly = average_belly;
  // set the old current value to the new previous value for the nose sensor
  previousVal_nose = average_nose;

  // increment calibrating so the belly knows when it can accept readings
  calibrating_belly = calibrating_belly + 1;
  
  // delay in between readings for more stability
  delay(500);

}
