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
int speedF = 400;
int speedB = -400;
int speedS = 0;

//functions to be called in other files
void allstop(){     //"stop" seems to be a reserved keyword
  motors.setM1Speed(speedS);
  motors.setM2Speed(speedS);
};

void forward(void){
  motors.setM1Speed(speedF);
  motors.setM2Speed(speedF);
};

void backwards(void) {
  motors.setM1Speed(speedB);
  motors.setM2Speed(speedB);
};

void left(void) {
  motors.setM1Speed(speedF);
  motors.setM2Speed(speedB);

  //set the new bearing
  robot.bearing -= 1;
  if(robot.bearing == 0){
    robot.bearing = 4;
  };
  delay(2500);
};

void right(void) {
  motors.setM1Speed(speedB);
  motors.setM2Speed(speedF);
  robot.bearing += 1;
  if(robot.bearing = 5){
    robot.bearing = 1;
  };
  delay(2500);
};
