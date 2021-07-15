//using #include and header files to include both variables and functions in main script
#include "detect.h"
#include "mapping.h"
#include "motor_control.h"

//setup function gets called on arduino startup

void setup() {
  //begin serial communication
  Serial.begin(9600);
}

//loop function is called recursivelly when the arduino is turned on

void loop(){ 
  //ping the environment
  ping();

  //update the location at the start of every loop
  robot.updateLocation(input[0]);
  
  if(input[0] < 0.2){
    allstop();
    delay(500);
    if(input[1] > input[2] && input[0] < input[1]) {
      right();
    }else if(input[2] > input[1] && input[0] < input[2]) {
      left();
    }else{
      backwards();
      delay(10000);
      right();
    }
    allstop();
  }
  else {
    forward();
  };

  delay(50);
}
