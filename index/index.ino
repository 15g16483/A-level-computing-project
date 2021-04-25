//set up the pins:
int echoPin = 9;
int trigPin = 8;

//declare other necessary variables
float duration;


void setup() {
  //begin serial communication
  Serial.begin(9600);

  //configure the pins to input and output
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  //reset the trig pin
  digitalWrite(trigPin, LOW);

  //activate the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //read the pulse duration on echo pin
  duration = pulseIn(echoPin, HIGH);

  //display result to serial monitor
  Serial.print("Echo Pin Input: ");
  Serial.println(duration);

  //delay for a second until the next reading
  delay(1000);

}
