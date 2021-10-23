//using #include and header files to include both variables and functions in main script. Creates a chain of files starting from detect and finishing at index.ino

#include "navigation.h"

//function that handles the beggining operations required for the robot
void start(){
  Serial.println("starting");
  
  while(true){
    ping();
    upMap();
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
  if(identifyTarget() == true){ //has the robot been able to find a suitable target?

    //relay data back to the monitor
    Serial.println("Obstacles");
    if(int i = nextObstacle - 1; i > -1; i--){
      Serial.print("(");
      Serial.print(obstacles[i][0]);
      Serial.print(",");
      Serial.print(obstacles[i][1]);
      Serial.print("), ");
    }
    Serial.println(" ");

    //use code written in navigation script to build an instruction set for the robot to run
    planRoute();
    compileRoute();
  
    //execute compiled route
    //iterate through instruction list
    for(int instruct = 0; instruct < 10; instruct++){
      
      if(instructions[instruct][1] != 0){ //filter out values where distance value does not equal 0
        //depending on the current bearing and direction of the robot, reorientate the robot to face correct direction, then move
        switch(instructions[instruct][0]){
          case 0:
            switch(robot.bearing){
              case 0:
                moving(instruct); //moving found in navigation.h
                break;
              case 1:
                left();
                
                moving(instruct);
                break;
              case 2:
                left();
                
                left();
                
                moving(instruct);
                break;
              case 3:
                right();
                
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
                
                moving(instruct);
                break;
              case 3:
                left();
                
                left();
                
                moving(instruct);
                break;
              case 0:
                right();
                
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
                
                moving(instruct);
                break;
              case 0:
                left();
                
                left();
                
                moving(instruct);
                break;
              case 1:
                right();
                
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
                
                moving(instruct);
                break;
              case 1:
                left();
                
                left();
                
                moving(instruct);
                break;
              case 2:
                right();
                
                moving(instruct);
                break;
            }
            break;
        }
      }
    }
  }else{
    //if no target is found, the entire area must be explored, so program complete
    Serial.println("Program complete");
  }
}
