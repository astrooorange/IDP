#include <Arduino.h>
#include <Servo.h>
#include "Line_Following_Final.h"
#include "Servo_Final.h"

Servo myservo;  // Create servo object to control a servo
int pe_sensor_pin = 12; // Pin for Photoelectric sensor
int pe_sensor_value = 0;


void setup() {
  myservo.attach(11);     // Pin for Servo
  pinMode(pe_sensor_pin,INPUT);
  Serial.begin(9600); 
  myservo.write(80);      // To set the servo to a starting angle     
}

/*
void grab_object()
{
  
  for(int i = 0 ;i <6 ;i++)      // Tries 5 times to sweep in so the object certainly is in
  {
  myservo.write(80);      // Attempts to sweep in the object
  delay(800);         
  myservo.write(20);
  delay(800);

  Serial.println(i);      // Debug
  }
}

void drop_off() // Function to drop the object whenever the robot is at the junction facing towards the drop off point
{
  // IF the robot isn't going forward/backward in a straight enough manner i think we can reduce the speed of it going forward and backward so that its slow enough to where like stuff should hit it off or smth (if rlly bad just change each wheel to spin at different amounts)

  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 1000 ;      // Time we want the program to run for (in milliseconds)
  while(millis() - startTime < runDuration);
  {
    chassis_forward();
  }

  // ADD CODE TO SPIN SERVOS
    myservo.write(-20); // pushout
    myservo.write(80);  // back to initial

    delay(15);

  // then it should just spin the servos to push the box off the catchment

  startTime=millis();     // Variable to store the start time
  runDuration = 1800 ;      // Time we want the program to run for (in milliseconds)
  while(millis() - startTime < runDuration);
  {
    chassis_backward();
  }
}
*/


void loop() {

  pe_sensor_value = digitalRead(pe_sensor_pin);

  if (pe_sensor_value == LOW)
  {
    Serial.println("pick up");
    grab_object();
    delay(1000);  //pick up for 1s
    myservo.write(-20); // pushout
    myservo.write(80);  // back to initial
  }
  else
  {
    Serial.println("nothing");
  }
  delay(15);   // waits for the servo to get there
}