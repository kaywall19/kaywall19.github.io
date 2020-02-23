const int button = 2;
const int therm = A0;


void setup() {

  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(therm, INPUT);
  
}

void loop() {

  boolean buttonState = digitalRead(button); 
  int thermValue = analogRead(therm); 

  Serial.print(buttonState);
  Serial.print(" ");
  Serial.println(thermValue);

  delay(200);
}
