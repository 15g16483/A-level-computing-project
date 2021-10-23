How to use the program:

Robot requirements:
Arduino Uno
3 HC-SR04 ultrasonic sensors for arduino
DRV8835MotorShield for Arduino.
2 6V motors.
6V power supply (only required to run the robot independantly from the PC - not reccommended as no data exchange available)
Serial cable (to exchange data to PC)

System requirements:
Arduino IDE for updating and installing the code on the robot.
DRV8835MotorShield library on Arduino IDE.
USB port for data communication.

Instructions for operation:
Connect the Serial cable between the PC and your robot.
Use the Arduino IDE to "upload" the code. Completed using the arrow next to the tick in the top left.
Open a Serial Monitor on the IDE. Keyboard shortcut: Ctrl+Shift+M
If the message "uploading to I/O board" appears above the terminal, re-run the upload. 
Make sure the robot is set on the ground before it begins the program. Make sure to restart if this is not the case.
Make sure the Serial Cable is not tugging on the robot whilst it moves. Can use portable laptop or longer Serial cable to fix this issue. 
Use the Serial Monitor to analyse the positions of objects within the environment. These are given as coordinates relative to the robots origin, where 1 represents 10 cm.
Wait for the robot to complete the program. In current iteration this step may not occur due to bugs.

Common issues:
"Board is not available": make sure you have the correct board and COM port selected on the Arduino IDE "tools" drop down.
No data is returned on Serial Monitor: make sure the monitor is linked up to the correct COM port. 
The robot does not move forward or turns incorrectly: May require you to edit the direction functions in the "motor_control.h" file so that it works for your robot.
Robot turns to little or too much: Adjust the time for which the robot turns in the "left" and "right" function in "motor_control.h"


