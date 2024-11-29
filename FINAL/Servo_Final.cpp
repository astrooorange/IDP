#include <Arduino.h>
#include "Servo_Final.h"
#include "Line_Following_Final.h"
#include "List_of_Path_Final.h"

void pick_up()
{  
  for(int i = 0 ;i <6 ;i++)      // Tries 5 times to sweep in, so the object IS in
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

  
  // robot enters the site, initially facing the site
  
  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 1000 ;      // Time we want the program to run for (in milliseconds)
  while(millis() - startTime < runDuration);
  {
    chassis_forward();
  }

    ml -> run(RELEASE);
    mr -> run(RELEASE);

  //robot drops the object
  
    myservo.write(-20);     // Spinning the Servos to push the waste out of the catchment     
    myservo.write(80);      // Back to initial

    delay(15);

  //robot returns to initial position with the same orientation
  while(millis() - startTime < runDuration);
  {
    chassis_backward();
  }

    ml -> run(RELEASE);
    mr -> run(RELEASE);
}

void object_detection()
{
  int svl1 = digitalRead(sl1);
  int svr1 = digitalRead(sr1);

  //while the chassis is on the line
  
  chassis_backward();
  delay(2000);

  while(digitalRead(pe_sensor_pin) == false)
  {
    chassis_forward();
  }

  delay(500);

  ml -> run(RELEASE);
  mr -> run(RELEASE);

  delay(5);

}
