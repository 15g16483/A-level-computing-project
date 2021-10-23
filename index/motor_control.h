//file for motor control

#include <DRV8835MotorShield.h>
#include "mapping.h"

/*Using the pololu drv8835 motorshield library
 * Reference links:
 * https://github.com/pololu/drv8835-motor-shield
 * https://www.arduino.cc/reference/en/libraries/drv8835motorshield/
 */

DRV8835MotorShield motors;

 //define speeds for motors
int speedF = 400; //forwards
int speedB = -400; //negative is backwards
int speedS = 0; //stop

//functions to be called in other files
void allStop(){     //"stop" seems to be a reserved keyword. using allstop instead
  //set motor speeds to 0
  motors.setM1Speed(speedS); 
  motors.setM2Speed(speedS);
};

void forward(void){
  //set motors forward
  motors.setM1Speed(speedF);
  motors.setM2Speed(speedF);
};

void backwards(void) {
  //set mortors backward
  motors.setM1Speed(speedB);
  motors.setM2Speed(speedB);
};

void left(void) {
  //one forward, one backward. You may have to change depending on your robot
  motors.setM1Speed(speedF);
  motors.setM2Speed(speedB);

  //set the new bearing
  robot.bearing -= 1;
  
  delay(4000); //may need to adjust the delay based on your specific robot and how it turns

  robot.updateBearing(); //handle post update bearing
};

void right(void) {
  motors.setM1Speed(speedB);
  motors.setM2Speed(speedF);
  
  robot.bearing += 1;
  
  delay(4000);

  robot.updateBearing(); //handle post bearing update
};
