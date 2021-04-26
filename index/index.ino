//set up the pins:
int echoPin1 = 11;
int echoPin2 = 3;
int echoPin3 = 10;
int echoPin4 = 9;
int trigPin = 8;


//declare other necessary variables
float duration1,duration2,duration3,duration4,distance1,distance2,distance3,distance4;


void setup() {
  //begin serial communication
  Serial.begin(9600);

  //configure the pins to input and output
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(echoPin4, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  //reset the trig pins
  digitalWrite(trigPin, LOW);

  //define duration vairables before hand to attempt synchronous functionality
  duration1 = pulseIn(echoPin1, HIGH);
  duration2 = pulseIn(echoPin2, HIGH);
  duration3 = pulseIn(echoPin3, HIGH);
  duration4 = pulseIn(echoPin4, HIGH);

  //activate sensors
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  //calculate the distance from the duration
  distance1 = 0.00017 * duration1;
  distance2 = 0.00017 * duration2;
  distance3 = 0.00017 * duration3;
  distance4 = 0.00017 * duration4;

  //display result to serial monitor
  Serial.print("Distance 1: ");
  Serial.println(distance1);
  Serial.print("Distance 2: ");
  Serial.println(distance2);
  Serial.print("Distance 3: ");
  Serial.println(distance3);
  Serial.print("Distance 4: ");
  Serial.println(distance4);

  //delay for a second until the next reading
  delay(1000);

}
