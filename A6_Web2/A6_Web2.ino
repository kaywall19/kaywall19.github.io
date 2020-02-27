//associate the button with pin 2
const int button = 2;
//associate the thermistor sensor with analog input pin A0
const int therm = A0;
//associate the LED with digital output pin 13
const int LED = 13;

//the setup function runs once the reset is pressed or the board is powered
void setup() {

  //sets the speed of Arduino communication to 9600
  Serial.begin(9600);
  //initializes the button pin as INPUT so I can read in the values
  pinMode(button, INPUT);
  //initializes the thermistor pin as INPUT so I can read in the values
  pinMode(therm, INPUT);
  //initializes the LED as output so I can make it turn on and off
  pinMode(LED, OUTPUT);
  
}

//the loop function runs continously
void loop() {

  //reads in the state of the button (1 if pressed, 0 if not)
  boolean buttonState = digitalRead(button); 
  //reads in the value of the thermistor sensor
  int thermValue = analogRead(therm); 

  //if there's serial data
  if (Serial.available() > 0) {

    //read in the written serial data into variable
    int inByte = Serial.read();
    //print the variable to the monitor for easy debugging and confirmation
    Serial.print(inByte);
    //if the read value is 49
    //49 is "1" in ASCII and means the button is pressed
    if (inByte == 49) {
      //turns on the white LED
      digitalWrite(LED, HIGH);
    //if the read value is 48
    //49 is "0" in ASCII and means the button is not pressed     
    } else if (inByte == 48) {
      //turns off the white LED
      digitalWrite(LED, LOW);
    }

 }



  //prints the start of the array for the tuple
  Serial.print("[");
  //prints the state of the button to the screen as part of the tuple
  Serial.print(buttonState);
  //a space in between two values makes a tuple
  Serial.print(",");
  //prints the thermistor value to complete the tuple of value pairs
  Serial.print(thermValue);
  //prints end of the array for the tuple
  Serial.println("]");

  //wait 200ms before reading next press or value
  delay(200);
}
