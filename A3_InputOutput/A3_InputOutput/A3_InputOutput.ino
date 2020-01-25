/*
  A3 InputOuput
  January 23, 2020
  Kay Waller
  HCDE 439

  This program uses a voltage divide with a variable resistor (thermistor) to
  change the state of an LED. This program borrows heavily from "InputOutput," by:

    Tom Igoe (created 29 Dec 2008)
    Tom Igoe (modified 09 Apr 2012)
*/

// initalizes pin A0 to register the input of the thermistor
const int input = A0;

// creates variables for the RGB LED by assinging pin numbers to each color
// assigns pin 6 as the red part of the RGB LED
const int outputRED = 6;
// assigns pin 5 as the blue part of the RGB LED
const int outputGREEN = 5;
// assigns pin 3 as the blue part of the RGB LED
const int outputBLUE = 3;

// creates a variable to store the reading from the thermistor
int sensorValue = 0;
// creates a variable to store a corresponding output value to be used in analogWrite functions
int outputValue = 0;
// creates a variable to store the color of the LED (determined by the temperature) to print out
char color = "";

// the setup function runs once the reset is pressed or the board is powered
void setup() {
  
  // sets the speed of serial monitor --> Arduino communication to 9600 bits per second
  Serial.begin(9600);

  // initializes the red part of the RGB LED as an output
  pinMode(outputRED, OUTPUT);
  // initializes the red part of the RGB LED as an output
  pinMode(outputGREEN, OUTPUT);
  // initializes the red part of the RGB LED as an output
  pinMode(outputBLUE, OUTPUT);
  
}

// the loop function runs continously and fades and blinks all LED's
void loop() {

  // reads the in-value from the analog pin listening to the thermistor
  sensorValue = analogRead(input);
  // maps the out-value from the thermistor to a value that can be used for analogWrite
  outputValue = map(sensorValue, 220, 500, 0, 30);
  
  // creates three colors which will be shown depending on the value read from the thermistor
  // tests if the value from the thermistor maps to under 10
  if (outputValue < 10) {
    // set the color variable to pink to print to the monitor
    color = "pink";
    // since the value is under 10, turn the green LED off because pink needs to be made
    digitalWrite(outputGREEN, LOW);
    // set the value of the red LED higher than blue so the LED is more pink than purple
    analogWrite(outputRED, 80); 
    // set the value of the blue LED so it tempers the red and makes pink
    analogWrite(outputBLUE, 20); 

    // tests if the value from the thermistor maps to 10 or above and under 20
  } else if (outputValue >= 10 && outputValue < 20) {
    // set the color variable to teal to print to the monitor
    color = "teal";
    // since the value is 10 or over, turn the red LED off because teal needs to be made
    digitalWrite(outputRED, LOW);
    // set the value of the blue LED lower than green so the LED is an aqua/teal instead of light blue
    analogWrite(outputBLUE, 10); 
    // set the value of the green LED higher than the blue so it creates an aqua/teal color
    analogWrite(outputGREEN, 50); 

    // tests if the value from the thermistor maps to between 20 and 30 (inclusive)
  } else if (outputValue >= 20 && outputValue <= 30) {
    // set the color variable to orange to print to the monitor
    color = "orange";
    // since is the value is between 20 and 30, turn the blue LED off because orange need to be made
    digitalWrite(outputBLUE, LOW);
    // set the value of the red LED higher than green so the LED is orange instead of yellow
    analogWrite(outputRED, 80); 
    // set the value of the green LED with just enough green to make the red LED orange
    analogWrite(outputGREEN, 10);    
  }

  // print the word sensor so the data values are readable and assigned to categories
  Serial.print("sensor = ");
  // print the value the analog pin is reading from the thermistor to the monitor
  Serial.print(sensorValue);
  // print the word color so the colors are readable and assigned to categories
  Serial.print("\t color = ");
  // print the color the LED should be displaying to the monitor
  Serial.println(color);
  
  // wait 5 milliseconds before next reading to allow data values to settle
  delay(5);
  
}
