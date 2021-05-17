//file for motor control

/*Using the pololu drv8835 motorshield library
 * Reference links:
 * https://github.com/pololu/drv8835-motor-shield
 * https://www.arduino.cc/reference/en/libraries/drv8835motorshield/
 */

 //define speeds for motors
int speedF = 400;
int speedB = -400;
int speedS = 0;

//functions to be called in other files
void allstop(){     //"stop" seems to be a reserved keyword
  Serial.println("stopped");
  void setM1Speed(int speedS);
  void setM2Speed(int speedS);
};

void forward(void){
  Serial.printlng("forwards");
  void setM1Speed(int speedF);
  void setM2Speed(int speedF);
};

void backward(void) {
  void setM1Speed(int speedB);
  void setM2Speed(int speedB);
};

void left(void) {
  void setM1Speed(int speedF);
  void setM2Speed(int speedB);
  delay(500);
};

void right(void) {
  void setM1Speed(int speedB);
  void setM2Speed(int speedF);
  delay(500);
};
