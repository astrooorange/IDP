#ifndef LIGHT_STATE_H
#define LIGHT_STATE_H

#include <TimerOne.h> // To use internal timer

// Pin definitions
extern int running_led;
extern int magnetic_led;
extern int not_magnetic_led;
extern int magnetic_sensor_pin;
extern bool chassis_currently_moving;

// Function declarations
void magnetic_sensing();
void toggle_led();

#endif
