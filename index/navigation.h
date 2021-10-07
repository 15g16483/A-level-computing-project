#include "motor_control.h"

int instructions[10][2]; //first number is the bearing, second is the distance in terms of how many coordinate points to move. 

int target[2]; //the target for the routing algorithm

int coordsToVisit[20][2]; //where the plan route function pushes its output to

int coordsToVisitLength = 0; //hae to read coordsToVisit in reverese, so this points to end of array.

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

bool planRoute() { //find which coordinates the robot needs to visit
  //can only use 300 bytes of local variables within this function

  int nextCheck[80][4] = {{robot.x, robot.y, robot.x, robot.y}};

  int checkSpace = 1; //next free space in nextCheck array, 

  int checking = 0; //pointer to element currently processing in nextCheck array

  int neighbour[2]; //holds the neighbour of the point being checked


  while(true){
    //find if the coordinate we are checking is a space.
    bool inSpace = false;
    for(int i = nextSpace - 1; i > -1; i--){ 
      if(nextCheck[checking][0] == space[i][0] && nextCheck[checking][1] == space[i][1]){
        i = 0;
        inSpace = true;
      };
    };
    if(nextCheck[checking][0] == target[0] && nextCheck[checking][1] == target[1]) {
      //reset coordinates to visit
      for(int y = 0; y < 20; y++){
        coordsToVisit[y][0] = 0;
        coordsToVisit[y][1] = 0;
      }
      coordsToVisitLength = 0;
      //builds the coordsToVisit array
      int nextUpload[2] = {nextCheck[checking][0], nextCheck[checking][1]};
      int pointer;
      for(int i = checking; i > -1; i--){
        coordsToVisit[coordsToVisitLength][0] = nextUpload[0];
        coordsToVisit[coordsToVisitLength][1] = nextUpload[1];

        //check if we have reached the robot yet
        if(coordsToVisit[coordsToVisitLength][0] == robot.x && coordsToVisit[coordsToVisitLength][1] == robot.y){
          return true;
        };
        for(int c = checking; c > -1; c--){
          if(nextCheck[c][0] == nextUpload[0] && nextCheck[c][1] == nextUpload[1]){
          pointer = c;
          }
        }

        nextUpload[0] = nextCheck[pointer][2];
        nextUpload[1] = nextCheck[pointer][3];

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
        for(int c = nextSpace - 1; c > -1; c--){
          if(neighbour[0] == space[c][0] && neighbour[1] == space[c][1]){
            neighbInSpace = true;
            c = 0;
          }
        }
        for(int z = checkSpace - 1; z > -1; z--){
          if(neighbour[0] == nextCheck[z][0] && neighbour[1] == nextCheck[z][1] ){
            exist = true;
            z = 0;
          };
        }; 
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
            return false;
          };
        };
      };
    };
    
    //after each check, need to update what to check for next iteration   
    checking++; //increment the next item to check
    if(checking == 80){
      return false;
    };
  }
  
  
};  

void compileRoute() { //turn the coordinates into instructions for the robot. make as efficient as possible
  int oldDir = 5; //1st direction
  int newDir; //2nd direction
  int inc = 0; //default incrementing forwards
  int instructionc = 0; //pointer to free element in instruction set
  int upc = 0;
  int rightc = 0;
  int downc = 0;
  int leftc = 0;
  for(int i = coordsToVisitLength; i > -1; i--){
    //find where the points would be
    int up[2] = {coordsToVisit[i][0],coordsToVisit[i][1] + 1};
    int right[2] = {coordsToVisit[i][0] + 1,coordsToVisit[i][1]};
    int down[2] = {coordsToVisit[i][0],coordsToVisit[i][1] - 1};
    int left[2] = {coordsToVisit[i][0] - 1,coordsToVisit[i][1]};

    if(up[0] == coordsToVisit[i-1][0] && up[1] == coordsToVisit[i-1][1]){
      newDir = 0;
    }
    if(right[0] == coordsToVisit[i-1][0] && right[1] == coordsToVisit[i-1][1]){
      newDir = 1;
    }
    if(down[0] == coordsToVisit[i-1][0] && down[1] == coordsToVisit[i-1][1]){
      newDir = 2;
    }
    if(left[0] == coordsToVisit[i-1][0] && left[1] == coordsToVisit[i-1][1]){
      newDir = 3;
    }
    if(newDir == oldDir && i != 0){
      switch(inc){
        case 0:
          upc++;
          break;
        case 1:
          rightc++;
          break;
        case 2:
          downc++;
          break;
        case 3:
          leftc++;
          break;
      }
    }else{
      //pass the instruction
      inc = newDir;
      instructions[instructionc][0] = oldDir;
      switch(oldDir){
        case 0:
          instructions[instructionc][1] = upc + 1;
          break;
        case 1:
          instructions[instructionc][1] = rightc + 1;
          break;
        case 2:
          instructions[instructionc][1] = downc + 1;
          break;
        case 3:
          instructions[instructionc][1] = leftc + 1;
          break;
      }
      upc = 0;
      rightc = 0;
      downc = 0;
      leftc = 0;
      instructionc++;
    }
    oldDir = newDir;
    
  }
};
