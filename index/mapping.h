#include "detect.h"


//builing a parent class so every object will have a 2D coordinate value

class Coordinate {
  public:
  
  int x;
  int y;
  
};

//inherit coordinate class for the robot.

class Robot: public Coordinate {
  public:

  float pingOnLoc[3];

  int bearing = 1; //direction will be 1 as forward, 2 as right, 3 as back and 4 as left.

  //create constructor for robot
  Robot(){
    ping(); //call ping so that pingOnLoc in mapping.h has a value.
    //artificially name location for 5.2 test
    x = 0;
    y = 7;
    pingOnLoc[0] = input[0];
  };
  
  //create a method to update the location on call
  bool updateLocation(){
    if(pingOnLoc[0] - input[0] >= 0.1){
      if(bearing == 1){
        y += 1;
      }else if(bearing == 2){
        x += 1;
      }else if(bearing == 3){
        y -= 1;
      }else{
        x -= 1;
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

//artificially building arrays to test target location. expecting to target {-6,2} (made a mistake on other iterations. was always {-6,2})

//getting stability issue with 5.2 testing so have to reduce size of these arrays to make stable again. need to simplify test as currently failing memory requirements for navigation
short space[][2] = {{0,0},{-1,0},{-2,0},{-3,0},{-4,0},{-5,0},{-6,0},{1,0},{2,0},{3,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{-1,1},{-2,1},{-3,1},{-4,1},{-5,1},{-6,1},{1,1},{2,1},{3,1},{-1,2},{-2,2},{-3,2},{-4,2},{-5,2},{-6,2},{1,2},{2,2},{3,2},{-1,3},{-2,3},{-3,3},{1,3},{2,3},{3,3},{-1,4},{-2,4},{-3,4},{1,4},{2,4},{3,4},{-1,5},{-2,5},{-3,5},{1,5},{2,5},{3,5},{-1,6},{-2,6},{-3,6},{1,6},{2,6},{3,6},{-1,7},{-2,7},{-3,7},{1,7},{2,7},{3,7}};
int nextSpace = 65;
short obstacle[][2] = {{0,8},{4,0},{4,1},{4,2},{4,3},{4,4},{4,5},{4,6},{4,7},{-4,3},{-4,4},{-4,5},{-4,6},{-4,7},{1,8},{2,8},{3,8},{-1,8},{-2,8},{-3,8},};
int nextObstacle = 21;
int coordinate[2];

 //now we need to check if this coordinate has already been recorded. Used later on in the main function
bool coordRecorded(){
  for(int i = 0; i < 300; i++){
    if((space[i][0] == coordinate[0] && space[i][1] == coordinate[1]) || (obstacle[i][0] == coordinate[0] && obstacle[i][1] == coordinate[1])){
      return true;
    }else if(i  >= nextSpace && i >= nextObstacle){
      return false;
    }else{
    };
  };
  return false;
};

void upMap() {
  
  for(int look = 0; look < 3; look++){

    //check if we are hitting the wall
    bool wallHit = false;
    for(int i = 0; i < 40; i++){

      int dist = i; //cast the opperands to floats so that the division can take place
      
      if((float)dist/(float)10 > robot.pingOnLoc[look]) {
        wallHit = true;
        i = 50;
        
      };
    
      //handles the assigning of the coordinate depending on the direction and used sensor. 
      //!!!WARNING!!! IF STATEMENT HELL AHEAD
      if(robot.bearing == 1){
        if(look == 0){
          coordinate[0] = robot.x;
          coordinate[1] = robot.y + dist;
        }else if(look == 1){
          coordinate[0] = robot.x  + dist;
          coordinate[1] = robot.y;
        }else{
          coordinate[0] = robot.x  - dist;
          coordinate[1] = robot.y;
        };
      }else if(robot.bearing == 2){
        if(look == 0){
          coordinate[0] = robot.x  + dist;
          coordinate[1] = robot.y;
        }else if(look == 1){
          coordinate[0] = robot.x;
          coordinate[1] = robot.y - dist;
        }else{
          coordinate[0] = robot.x;
          coordinate[1] = robot.y + dist;
        };
      }else if(robot.bearing == 3){
        if(look == 0){
          coordinate[0] = (robot.x)*10;
          coordinate[1] = (robot.y - dist)*10;
        }else if(look == 1){
          coordinate[0] = (robot.x - dist)*10;
          coordinate[1] = (robot.y)*10;
        }else{
          coordinate[0] = (robot.x + dist)*10;
          coordinate[1] = (robot.y)*10;
        };
      }else{
        if(look == 0){
          coordinate[0] = (robot.x - dist)*10;
          coordinate[1] = (robot.y)*10;
        }else if(look == 1){
          coordinate[0] = (robot.x)*10;
          coordinate[1] = (robot.y + dist)*10;
        }else{
          coordinate[0] = (robot.x)*10;
          coordinate[1] = (robot.y - dist)*10;
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
      
    }; //for loop
  }; //for loop
}; //function
