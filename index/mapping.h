#include "detect.h"


//builing a parent class so every object will have a 2D coordinate value

class Coordinate {
  public:
  
  float x;
  float y;
  
};

//inherit coordinate class for the robot.

class Robot: public Coordinate {
  public:

  float pingOnLoc[3];

  int bearing = 1; //direction will be 1 as forward, 2 as right, 3 as back and 4 as left.

  //create constructor for robot
  Robot(){
    ping(); //call ping so that pingOnLoc in mapping.h has a value.
    x = 0;
    y = 0;
    pingOnLoc[0] = input[0];
  };
  
  //create a method to update the location on call
  void updateLocation(){
    if(pingOnLoc[0] - input[0] >= 0.1){
      Serial.println("update being called");
      if(bearing == 1){
        y += 0.1;
      }else if(bearing == 2){
        x += 0.1;
      }else if(bearing == 3){
        y -= 0.1;
      }else{
        x -= 0.1;
      };
      ping();
      for(int i = 0; i < 3; i++){
        pingOnLoc[i] = input[i];
      };

      //for testing purposes
      Serial.println(x);
      Serial.println(y);
      
    };
  };
  void updateBearing(){ //this method handles everything after the bearing has been updated.
    ping();
    pingOnLoc[0] = input[0]; //redefine location

    //make sure bearing doesn't become an invalid value
    if(bearing == 0){
      bearing = 4;
    };

    if(bearing == 5) {
      bearing = 1;
    };
  };
};

//class for obstacles in the environment. Also handles classification of empty spaces.

class Point: public Coordinate {
  public:

  int explored = 0; //every point at first is unexplored

  int obstacle = 0; //until we know what the point it, it cannot be an obstacle


  
  
};

int generateNum = 0; //this is the number of points that has been generated. 


//start positions of each of the generated points stored here to prevent repeats
float generated[100][2];

//generate a 1x1 metre area of unexplored area. 
void generate(float start[2]) {
  bool isAlreadyGen = false;
  for(int i = 0; i < 100; i++){
    if(start == generated[i]){
      isAlreadyGen = true;
    };
  };
  if(isAlreadyGen == false){
    for(int z = 0; z < 10; z++){
      for(int i = 0; i < 10; i++){
        Point id;
        generateNum.x = start[0] + i/10;
        generateNum.y = start[1] + z/10;
        generateNum++;
      };
    };
    generated[generateNum/100] = start;
  };
};

//declare class for robot
Robot robot;
