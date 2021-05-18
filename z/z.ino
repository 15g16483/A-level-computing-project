//this file has to be z so that it gets compiled last

void setup() {
  //begin serial communication
  Serial.begin(9600);

}


void loop() {
  right();
  delay(2000);
  left();
  delay(2000);
}
