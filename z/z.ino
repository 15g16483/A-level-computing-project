//this file has to be z so that it gets compiled last

void setup() {
  //begin serial communication
  Serial.begin(9600);

}


void loop() {
  forward();
  delay(3000);
  allstop();
  delay(1000);
  right();
  delay(2000);
  allstop();
  delay(1000);
  left();
  delay(2000);
  allstop();
  delay(1000);
  backwards();
  delay(3000);
  allstop();
  Serial.println("restarting:");
  delay(5000);
}
