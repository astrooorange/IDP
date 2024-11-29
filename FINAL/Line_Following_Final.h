#ifndef LINE_FOLLOWING_FINAL_H
#define LINE_FOLLOWING_FINAL_H

#include <Adafruit_MotorShield.h>


// Declare global variables
extern int forward_speedL;
extern int forward_speedR;
extern int backward_speed;
extern int sr;
extern int sl;
extern int sm;


// Declare motors
extern Adafruit_DCMotor* ml;
extern Adafruit_DCMotor* mr;

// Declare your functions here
void chassis_forward(); // Example function declaration
void chassis_backward();
void chassis_turn_left();
void chassis_turn_right();
void chassis_turn_super_left();
void chassis_turn_super_right();
void chassis_turn_left90();
void chassis_turn_right90();
void get_me_out_of_the_starting_box();
void get_me_into_the_starting_box();

#endif
