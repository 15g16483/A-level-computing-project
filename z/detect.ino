//function to be called to activate a specific sensor.
float detect(int dir){
  
  //echopins are 3,5,11
  //trig pins are 2,4,12

  //store pins in arrays for future reference
  int echoPin[3] = {3,5,11};
  int trigPin[3] = {2,4,12};
  
  //configure the pins to input and output
  pinMode(echoPin[dir], INPUT);
  pinMode(trigPin[dir], OUTPUT);
  
  //reset the trig pin
  digitalWrite(trigPin[dir], LOW);

  //activate sensor
  digitalWrite(trigPin[dir], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin[dir], LOW);
  
  //find the duration of the pulse
  float duration = pulseIn(echoPin[dir], HIGH);

  
  //calculate the distance from the duration
  float distance = 0.00017 * duration;
  
  return distance;
};
