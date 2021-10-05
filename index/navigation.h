#include "motor_control.h"

int instructions[10][2]; //first number is the bearing, second is the distance in terms of how many coordinate points to move. 

int target[2]; //the target for the routing algorithm

int coordsToVisit[20][2]; //where the plan route function pushes its output to

int coordsToVisitLength = 0; //hae to read coordsToVisit in reverese, so this points to end of array.

void identifyTarget() {
  Serial.println("target");
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

bool planRoute() { //find which coordinates the robot needs to visit
  //can only use 300 bytes of local variables within this function

  int nextCheck[80][4] = {{robot.x, robot.y, robot.x, robot.y}};

  int checkSpace = 1; //next free space in nextCheck array, 

  int checking = 0; //pointer to element currently processing in nextCheck array

  int neighbour[2]; //holds the neighbour of the point being checked

  Serial.println("hello");

  while(true){
   // Serial.println(checking);
    //find if the coordinate we are checking is a space.
    bool inSpace = false;
    for(int i = nextSpace - 1; i > 0; i--){ 
      if(nextCheck[checking][0] == space[i][0] && nextCheck[checking][1] == space[i][1]){
        i = 0;
        inSpace = true;
      };
    };
    Serial.println(checkSpace);
    Serial.println(checking);
    Serial.print(nextCheck[checking][0]);
    Serial.print(",");
    Serial.println(nextCheck[checking][1]);
    Serial.print(target[0]);
    Serial.print(",");
    Serial.println(target[1]);
    if(nextCheck[checking][0] == target[0] && nextCheck[checking][1] == target[1]) {
      //builds the coordsToVisit array
      int nextUpload[2] = {nextCheck[checking][0], nextCheck[checking][1]};
      for(int i = checking; i > 0; i--){
        coordsToVisit[coordsToVisitLength][0] = nextUpload[0];
        coordsToVisit[coordsToVisitLength][1] = nextUpload[1];

        //check if we have reached the robot yet
        if(coordsToVisit[coordsToVisitLength][0] == robot.x && coordsToVisit[coordsToVisitLength][1] == robot.y){
          return true;
        };

        nextUpload[0] = nextCheck[checking][2];
        nextUpload[1] = nextCheck[checking][3];

        coordsToVisitLength++;

      }
    } else if(inSpace == true){
      //find the neighbours of the coordinate. these should be visited next.
      for(int i = 0; i < 4; i++){
        switch(i) { //indentify between the neighbours
          case 0:
            neighbour[0] = nextCheck[checking][0];
            neighbour[1] = nextCheck[checking][1] + 1;
            break;
          case 1:
            neighbour[0] = nextCheck[checking][0] + 1;
            neighbour[1] = nextCheck[checking][1];
            break;
          case 2:
            neighbour[0] = nextCheck[checking][0];
            neighbour[1] = nextCheck[checking][1] - 1;
            break;
          case 3:
            neighbour[0] = nextCheck[checking][0] - 1;
            neighbour[1] = nextCheck[checking][1];
            break;
        };
        //check if the neighbour already exists in the nextCheck array
        bool exist = false;
        bool neighbInSpace = false;
        for(int c = nextSpace - 1; c > 0; c--){
          if(neighbour[0] == space[c][0] && neighbour[1] == space[c][1]){
            neighbInSpace = true;
            c = 0;
          }
        }
        for(int z = checkSpace - 1; z > 0; z--){
          if(neighbour[0] == nextCheck[z][0] && neighbour[1] == nextCheck[z][1] ){
            exist = true;
            z = 0;
          };
        }; 
//        Serial.println(exist);
//        Serial.println(neighbInSpace);
//        Serial.print(neighbour[0]);
//        Serial.print(",");
//        Serial.println(neighbour[1]);
        if(exist == false && neighbInSpace == true){
          //set the next element to check to the neighbour
          nextCheck[checkSpace][0] = neighbour[0];
          nextCheck[checkSpace][1] = neighbour[1];
          nextCheck[checkSpace][2] = nextCheck[checking][0];
          nextCheck[checkSpace][3] = nextCheck[checking][1];
  
          //increment the next space to load.
          checkSpace++;
          if(checkSpace == 80){
            //no more memory so have to return false
            Serial.println("f1");
            return false;
          };
        };
      };
    };
    
    //after each check, need to update what to check for next iteration   
    checking++; //increment the next item to check
    if(checking == 80){
      Serial.println("f2");
      return false;
    };
  }
  
  
};  

void compileRoute() { //turn the coordinates into instructions for the robot. make as efficient as possible
  
};
