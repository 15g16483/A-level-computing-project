#include "motor_control.h"

int instructions[10][2]; //first number is the bearing, second is the distance in terms of how many coordinate points to move. 

int coordsToVisit[20][2]; //where the routing algorithm will push the coords to visit too. 

int target[2]; //the target for the routing algorithm

void identifyTarget() {
  bool targetFound = false;
  for(int i = nextSpace - 1; i > 0; i--){

    //find the neighbours of the space and put into list
    int neighbours[4][2] = {{space[i][0], space[i][1] + 1}, {space[i][0] + 1, space[i][1]}, {space[i][0], space[i][1] - 1}, {space[i][0] - 1, space[i][1]}}; // top, right, bottom, left

    int neighbExplored = 0; //a count of how many of the neighbours are already explored. If this is 4 then all of them are there.

    //compare with obstacles array to potentially eliminate comparrisons
    for(int a = 0; a < 4; a++){
      for(int o = nextObstacle - 1; o > 0; o--){
        if(neighbours[a][0] == obstacle[o][0] && neighbours[a][1] == obstacle[o][1]){
          neighbExplored++;
          o = 0; //end this for loop. reduce comparisons.

          //redefine the neighbours so that this coordinate doesn't get compared again. redefined to origin as this is guaranteed to be explored.
          neighbours[a][0] = 0; 
          neighbours[a][1] = 0;
          
        }; //endif
      }; //endfor 
    }; // endfor
    
    //now that the obstacle have been eliminated, check within the spaces array
    for(int a = 0; a < 4; a++){
      if((neighbours[a][0] == 0 && neighbours[a][1] != 0) || (neighbours[a][0] != 0 && neighbours[a][1] == 0) || (neighbours[a][0] != 0 && neighbours[a][1] != 0)){
        for(int s = nextSpace - 1; s > 0; s--){
          if(neighbours[a][0] == space[s][0] && neighbours[a][1] == space[s][1]){
            neighbExplored++;
            s = 0;
          }; //endif
        }; //endfor
      }; //endif
    }; //endfor
    if(neighbExplored != 4){
      target[0] = space[i][0];
      target[1] = space[i][1];

      targetFound = true;

      //end the whole function so that no more unecessary comparrisons occur. This way the closest coordinate to the robot with an unexplored neighbour is targeted.
      i = 0;
    };
  }; //endfor

  if(targetFound == false){
    //declare an end to the progam. All spaces found
  };
};

void planRoute() { //find which coordinates the robot needs to visit
  //can only use 300 bytes of local variables within this function
  
};  

void compileRoute() { //turn the coordinates into instructions for the robot.
  
};
