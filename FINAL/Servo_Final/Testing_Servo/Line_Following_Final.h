#ifndef LINE_FOLLOWING_FINAL_H
#define LINE_FOLLOWING_FINAL_H

#include <Adafruit_MotorShield.h>


// Declare global variables
extern int forward_speedL;
extern int forward_speedR;
extern int backward_speed;

// Declaring motors
extern Adafruit_DCMotor* ml;
extern Adafruit_DCMotor* mr;

// Declaring Functions
void chassis_forward(); 
void chassis_backward();
void chassis_turn_left();
void chassis_turn_right();
void chassis_turn_super_left();
void chassis_turn_super_right();
void chassis_turn_left90();
void chassis_turn_right90();

#endif