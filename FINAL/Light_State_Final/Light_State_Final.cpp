#include "Light_State_Final.h"
#include <Arduino.h> // Necessary for Arduino functions like pinMode, digitalWrite, etc.

bool chassis_currently_moving = false ;      // To state whether the chassis is moving or not so to turn on the running led


void magnetic_sensing() {
    int magneticOutput =HIGH; // Read if the magnetic sensor has an output

    if (magneticOutput == HIGH) {
        digitalWrite(not_magnetic_led, HIGH); 
        digitalWrite(magnetic_led, LOW);  // Turn on magnetic waste LED
    } else {
        digitalWrite(magnetic_led, HIGH); 
        digitalWrite(not_magnetic_led, LOW);  // Turn on non-magnetic waste LED
    }
}


void toggle_led() {
    // Toggle the running LED
    
    
      digitalWrite(running_led, !digitalRead(running_led));
      magnetic_sensing();
    
}









