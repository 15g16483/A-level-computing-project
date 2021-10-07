//using #include and header files to include both variables and functions in main script. Creates a chain of files starting from detect and finishing at index.ino

#include "navigation.h"

//function that handles the beggining operations required for the robot
void start(){
  Serial.println("starting");
  
  while(true){
    ping();
    if(input[0] > 0.2){
      forward();
      if(robot.updateLocation() == true){
        upMap();
        Serial.print("L:");
        Serial.print(robot.x);
        Serial.print(",");
        Serial.println(robot.y);
      }
    }else{
      allStop();
      break;
    }
  }
  
}

  
//setup function gets called on arduino startup

void setup() {
  //begin serial communication
  Serial.begin(9600);

  start();

};

//loop function is called recursivelly when the arduino is turned on

void loop(){ 
  if(identifyTarget() == true){
    Serial.print("Target: ");
    Serial.print(target[0]);
    Serial.print(",");
    Serial.println(target[1]);
    planRoute();
    compileRoute();
    Serial.print("Instructions: ");
    for(int z = 0; z < 10; z++){
      Serial.print("(");
      Serial.print(instructions[z][0]);
      Serial.print(",");
      Serial.print(instructions[z][1]);
      Serial.print("), ");
    }
    Serial.println(" ");
  
    //execute compiled route
    //iterate through instruction list
    for(int instruct = 0; instruct < 10; instruct++){
      if(instructions[instruct][1] != 0){
        switch(instructions[instruct][0]){
          case 0:
            switch(robot.bearing){
              case 0:
                moving(instruct);
                break;
              case 1:
                left();
                robot.updateBearing();
                moving(instruct);
                break;
              case 2:
                left();
                robot.updateBearing();
                left();
                robot.updateBearing();
                moving(instruct);
                break;
              case 3:
                right();
                robot.updateBearing();
                moving(instruct);
                break;
            }
            break;
          case 1:
            switch(robot.bearing){
              case 1:
                moving(instruct);
                break;
              case 2:
                left();
                robot.updateBearing();
                moving(instruct);
                break;
              case 3:
                left();
                robot.updateBearing();
                left();
                robot.updateBearing();
                moving(instruct);
                break;
              case 0:
                right();
                robot.updateBearing();
                moving(instruct);
                break;
            }
            break;  
          case 2:
            switch(robot.bearing){
              case 2:
                moving(instruct);
                break;
              case 3:
                left();
                robot.updateBearing();
                moving(instruct);
                break;
              case 0:
                left();
                robot.updateBearing();
                left();
                robot.updateBearing();
                moving(instruct);
                break;
              case 1:
                right();
                robot.updateBearing();
                moving(instruct);
                break;
            }
            break;
          case 3:
            switch(robot.bearing){
              case 3:
                moving(instruct);
                break;
              case 0:
                left();
                robot.updateBearing();
                moving(instruct);
                break;
              case 1:
                left();
                robot.updateBearing();
                left();
                robot.updateBearing();
                moving(instruct);
                break;
              case 2:
                right();
                robot.updateBearing();
                moving(instruct);
                break;
            }
            break;
        }
      }
    }
  }else{
    Serial.println("Program complete");
  }
}
