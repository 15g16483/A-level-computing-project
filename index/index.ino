//set up the pins:
int echoPin1 = 11;
int echoPin2 = 3;
int echoPin3 = 10;
int echoPin4 = 9;
int trigPin1 = 8;
int trigPin2 = 7;
int trigPin3 = 12;
int trigPin4 = 13;


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
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(trigPin4, OUTPUT);
}

void loop() {
  //reset the trig pins
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  digitalWrite(trigPin3, LOW);
  digitalWrite(trigPin4, LOW);

  //sensor 1
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);

  //sensor 2
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);

  //sensor 3
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  duration3 = pulseIn(echoPin3, HIGH);
  
  //sensor 4
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  
  duration4 = pulseIn(echoPin4, HIGH);

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
