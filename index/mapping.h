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
  bool updateLocation(){
    if(pingOnLoc[0] - input[0] >= 0.1){
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
      return true;
      
    }else{
      return false;
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

//declare class for robot
Robot robot;

//these are the arrays that hold the points that are free and the points that are obstacles. Storing the coordinate values as int so I can store more. Just needs simple conversion to turn back to float form. 

int space[16][2]; 
int nextSpace = 0;
int obstacle[16][2];
int nextObstacle = 0;
int coordinate[2];

 //now we need to check if this coordinate has already been recorded. Used later on in the main function
bool coordRecorded(){
  for(int i = 0; i < 8116; i++){
    if(space[i] == coordinate || obstacle[i] == coordinate){
      return true;
    }else if(i  >= nextSpace && i >= nextObstacle){
      return false;
    }else{
      return false;
    };
  };
};

void upMap() {
  
  for(int look = 0; look < 3; look++){
    Serial.println(look);

    //check if we are hitting the wall
    bool wallHit = false;
    for(int dist = 0; dist < 40; dist++){
      //Serial.println(dist);
      if(dist/10 >= robot.pingOnLoc[look]) {
        wallHit = true;
        dist = 50;
        
      };
    
      //handles the assigning of the coordinate depending on the direction and used sensor. 
      //!!!WARNING!!! IF STATEMENT HELL AHEAD
      if(robot.bearing == 1){
        if(look == 0){
          coordinate[0] = (robot.x)*10;
          coordinate[1] = (robot.y + dist/10)*10;
        }else if(look == 1){
          coordinate[0] = (robot.x  + dist/10)*10;
          coordinate[1] = (robot.y)*10;
        }else{
          coordinate[0] = (robot.x  - dist/10)*10;
          coordinate[1] = (robot.y)*10;
        };
      }else if(robot.bearing == 2){
        if(look == 0){
          coordinate[0] = (robot.x  + dist/10)*10;
          coordinate[1] = (robot.y)*10;
        }else if(look == 1){
          coordinate[0] = (robot.x)*10;
          coordinate[1] = (robot.y - dist/10)*10;
        }else{
          coordinate[0] = (robot.x)*10;
          coordinate[1] = (robot.y + dist/10)*10;
        };
      }else if(robot.bearing == 3){
        if(look == 0){
          coordinate[0] = (robot.x)*10;
          coordinate[1] = (robot.y - dist/10)*10;
        }else if(look == 1){
          coordinate[0] = (robot.x - dist/10)*10;
          coordinate[1] = (robot.y)*10;
        }else{
          coordinate[0] = (robot.x + dist/10)*10;
          coordinate[1] = (robot.y)*10;
        };
      }else{
        if(look == 0){
          coordinate[0] = (robot.x - dist/10)*10;
          coordinate[1] = (robot.y)*10;
        }else if(look == 1){
          coordinate[0] = (robot.x)*10;
          coordinate[1] = (robot.y + dist/10)*10;
        }else{
          coordinate[0] = (robot.x)*10;
          coordinate[1] = (robot.y - dist/10)*10;
        };
      };
        //check the arrays to see if the coordinate is already recorded.
        bool isElementPresent = coordRecorded();

        //assign the coordinate to the relevant storage array
        if(wallHit == false && isElementPresent == false){
          space[nextSpace][0] = coordinate[0];
          space[nextSpace][1] = coordinate[1];

          
          nextSpace++;
        }else if(isElementPresent == false){
          obstacle[nextObstacle][0] = coordinate[0];
          obstacle[nextObstacle][1] = coordinate[1];
          nextObstacle++;
        };
        Serial.println(dist);
      
    }; //for loop
  }; //for loop
}; //function
