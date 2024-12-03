#ifndef SERVO_FINAL_H
#define SERVO_FINAL_H

#include <Servo.h>  

// Declaring the Servo 
extern Servo myservo;  

// Declaration of Global Variables
extern int pe_sensor_pin;


// Declaration of Functions
void pick_up();
void drop_off();
void object_detection();


#endif