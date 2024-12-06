#ifndef LIGHT_STATE_FINAL_H
#define LIGHT_STATE_FINAL_H

#include <TimerOne.h> // To use internal timer

// Declaration of Global Variables
extern int running_led;
extern int magnetic_led;
extern int not_magnetic_led;
extern int magnetic_sensor_pin;
extern bool chassis_currently_moving;
extern bool holding_object;

// Declaration of Functions
void magnetic_sensing();
void toggle_led();

#endif
