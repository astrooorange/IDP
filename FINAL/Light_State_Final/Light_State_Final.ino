#include <TimerOne.h>     // To use internal timer
#include "Light_State_Final.h"      //To get the functions: magnetic_sensing()  toggle_led

int running_led =2; //Light to show robot is running (blue)
int magnetic_led =3; //Light to show waste is magnetic (Red)
int not_magnetic_led = 4; //Light to show waste is not magnetic (Green)
int magneticPin = 13; //Pin to detect magenetic


void setup() {
  pinMode(running_led, OUTPUT); //Set Pin2 as output  
  pinMode(magnetic_led, OUTPUT); //Set Pin3 as output
  pinMode(not_magnetic_led, OUTPUT); //Set Pin4 as output
  pinMode(magneticPin, INPUT); // Set Pin13 as input

  // Interrupts stuff
  Timer1.initialize(500000); // Set timer to overflow every 0.5 seconds
  Timer1.attachInterrupt(toggle_led);  // Attach the interrupt function to Timer1
}
/*
void running_LED() { // this makes the LED flash on and off with a period of 700ms

    digitalWrite(running_led, LOW); 
    delay(700);
    digitalWrite(running_led, HIGH); 
    delay(700);
}*/


void loop()
{
  delay(1000000000000);
  }


/*


*/
