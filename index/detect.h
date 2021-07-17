//function to be called to activate a specific sensor.
float detect(int dir){
  
  //echopins are front: 3, right: 5, left: 11
  //trig pins are front: 2, right: 4, left:12

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

//get a distance from each detector returned as an array in the input variable. This can't be in the detect script as it is impossible to return arrays in functions in C.

float input[3];

void ping() {
  
  //using a for loop to iterate through the different pins in the detect file.
  for(int i = 0; i < 3; i++){
    input[i] = detect(i);
  };
};
