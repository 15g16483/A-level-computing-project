//this file has to be z so that it gets compiled last

void setup() {
  //begin serial communication
  Serial.begin(9600);

}


void loop() {
  forward();
  delay(3000);
  allstop();  
  delay(5000);
}
