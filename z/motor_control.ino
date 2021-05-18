//file for motor control

#include <DRV8835MotorShield.h>

/*Using the pololu drv8835 motorshield library
 * Reference links:
 * https://github.com/pololu/drv8835-motor-shield
 * https://www.arduino.cc/reference/en/libraries/drv8835motorshield/
 */

DRV8835MotorShield motors;

 //define speeds for motors
int speedF = 400;
int speedB = -400;
int speedS = 0;

//functions to be called in other files
void allstop(){     //"stop" seems to be a reserved keyword
  Serial.println("stopped");
  motors.setM1Speed(speedS);
  motors.setM2Speed(speedS);
};

void forward(void){
  Serial.println("forwards");
  motors.setM2Speed(speedF);
  motors.setM1Speed(speedF);
};

void backward(void) {
  Serial.println("backwards");
  motors.setM1Speed(speedB);
  motors.setM2Speed(speedB);
};

void left(void) {
  Serial.println("left");
  motors.setM1Speed(speedF);
  motors.setM2Speed(speedB);
  delay(500);
};

void right(void) {
  Serial.println("right");
  motors.setM1Speed(speedB);
  motors.setM2Speed(speedF);
  delay(500);
};
