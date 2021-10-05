//using #include and header files to include both variables and functions in main script. Creates a chain of files starting from detect and finishing at index.ino

#include "navigation.h"

  
//setup function gets called on arduino startup

void setup() {
  //begin serial communication
  Serial.begin(9600);

};

//loop function is called recursivelly when the arduino is turned on

void loop(){ 
  identifyTarget();
  Serial.println(target[0]);
  Serial.println(target[1]);
  //delay(500);

  //expecting to see count down through coordinates from target down to the robots location (0,7)
  if(planRoute() == true){
    Serial.println("coordsToVisit:");
    for(int i = coordsToVisitLength; i > -1; i--){
      Serial.print(coordsToVisit[i][0]);
      Serial.print(",");
      Serial.println(coordsToVisit[i][1]);
    }
  }
  delay(10000);





  
//  //ping the environment
//  ping();
//
//  //update the location at the start of every loop
//  if(robot.updateLocation() == true){
//    //once location updated, update the map with the new information
//    upMap();
//  };
//
//
//  //current navigation code to control where the robot goes based on the surroundings
//  if(input[0] < 0.2){
//    allstop();
//    delay(500);
//    if(input[1] > input[2] && input[0] < input[1]) {
//      right();
//    }else if(input[2] > input[1] && input[0] < input[2]) {
//      left();
//    }else{
//      backwards();
//      delay(10000);
//      right();
//    }
//    allstop();
//  }
//  else {
//    forward();
//  };
//
//  delay(50);
//

}
