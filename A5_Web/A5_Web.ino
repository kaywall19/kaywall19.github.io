//associate the button with pin 2
const int button = 2;
//associate the thermistor sensor with analog input pin A0
const int therm = A0;

//the setup function runs once the reset is pressed or the board is powered
void setup() {

  //sets the speed of Arduino communication to 9600
  Serial.begin(9600);
  //initializes the button pin as INPUT so I can read in the values
  pinMode(button, INPUT);
  //initializes the thermistor pin as INPUT so I can read in the values
  pinMode(therm, INPUT);
  
}

//the loop function runs continously
void loop() {

  //reads in the state of the button (1 if pressed, 0 if not)
  boolean buttonState = digitalRead(button); 
  //reads in the value of the thermistor sensor
  int thermValue = analogRead(therm); 

  //prints the state of the button to the screen as part of the tuple
  Serial.print(buttonState);
  //a space in between two values makes a tuple
  Serial.print(" ");
  //prints the thermistor value to complete the tuple of value pairs
  Serial.println(thermValue);

  //wait 200ms before reading next press or value
  delay(200);
}
