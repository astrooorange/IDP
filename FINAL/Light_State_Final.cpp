#include "Light_State_Final.h"
#include <Arduino.h>


bool chassis_currently_moving = false ;      // To state whether the chassis is moving or not so to turn on the running led
bool holding_object = false;      // To state if we are holding the object to start the lights to see if the waste is magnetic or not

void magnetic_sensing() {

    if (holding_object == true)
    {
      if (digitalRead(magnetic_sensor_pin) == HIGH) 
      {
          digitalWrite(magnetic_led, HIGH);     // Turn on magnetic waste LED
          digitalWrite(not_magnetic_led, LOW);  
      } 
      else 
      {
          digitalWrite(not_magnetic_led, HIGH);     // Turn on non-magnetic waste LED
          digitalWrite(magnetic_led, LOW);  
      }
    }
    
}


void toggle_led() {
    Serial.println("The interuptts are working! PLease ??");
    if (chassis_currently_moving == true)     // To only flash the running LED when the robot is moving
    {
    digitalWrite(running_led, !digitalRead(running_led));// Toggle the running LED
    }

    if (holding_object == true)     // To only show magnetic/non magnetic lights when the object is in the basket
    {
      magnetic_sensing();
    }
}









