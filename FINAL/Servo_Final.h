#ifndef SERVO_FINAL_H
#define SERVO_FINAL_H

#include <Servo.h>  

// Declaring the Servo 
extern Servo myservo;  

// Declaring Global Variables
extern int pe_sensor_pin;
/*extern int sl1;
extern int sr1;*/

// Declaring Functions
void pick_up();
void drop_off();
void object_detection();


#endif