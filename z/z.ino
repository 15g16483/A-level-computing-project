
void setup() {
  //begin serial communication
  Serial.begin(9600);

}


void loop() {
  forward();
  backward();
  left();
  right();
  
}
