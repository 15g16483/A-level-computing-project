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
    x = 0;
    y = 0;
    pingOnLoc[0] = input[0];
  };
  
  //create a method to update the location on call
  void updateLocation(int distance){
    if(pingOnLoc[0] - distance >= 10){
      if(bearing = 1){
        y++;
      }else if(bearing = 2){
        x++;
      }else if(bearing = 3){
        y--;
      }else{
        x--;
      };
      ping();
      for(int i = 0; i < 3; i++){
        pingOnLoc[i] = input[i];
      };

      //for testing purposes
      Serial.println(x, y);
    };
  };
  
};

Robot robot; //create robot class immediately so that motor-control file can edit bearing value
