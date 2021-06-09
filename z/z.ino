//this file has to be z so that it gets compiled last

//get a distance from each detector returned as an array in the input variable. This can't be in the detect script as it is impossible to return arrays in functions in C.

float input[3];

void ping(void) {
  
  //using println to test if this function is getting called
  Serial.println("this is being called");
  
  //using a for loop to iterate through the different pins in the detect file.
  for(int i = 0; i < 3; i++){
    input[i] = detect(i);
  };
};

//setup function gets called on arduino startup

void setup() {
  //begin serial communication
  Serial.begin(9600);

}

//loop function is called recursivelly when the arduino is turned on

void loop() {
  ping();

  //cant parse an array into a function so have to do each element individually
  for(int i = 0; i < 3; i++){
    Serial.println(input[i]);
  }

  Serial.println("");
  delay(1000);
  
}
