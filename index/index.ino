//using #include and header files to include both variables and functions in main script. Creates a chain of files starting from detect and finishing at index.ino

#include "motor_control.h"

  
//setup function gets called on arduino startup

void setup() {
  //begin serial communication
  Serial.begin(9600);

};

//loop function is called recursivelly when the arduino is turned on

void loop(){ 
  //ping the environment
  ping();

  //update the location at the start of every loop
  if(robot.updateLocation() == true){
    //once location updated, update the map with the new information
    upMap();

    //testing purposes
    Serial.println("spaces:"); 
    for(int i = 0; i < 10; i++){
      Serial.print(space[i][0]);
      Serial.print(",");
      Serial.print(space[i][1]);
      Serial.print("; ");
    }
    Serial.println("obstacles:"); 
    for(int i = 0; i < 10; i++){
      Serial.print(obstacle[i][0]);
      Serial.print(",");
      Serial.print(obstacle[i][1]);
      Serial.print("; ");
    }
  }

  //current navigation code to control where the robot goes based on the surroundings
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
