#include <Arduino.h>
#include "Servo_Final.h"
#include "Line_Following_Final.h"
#include "List_of_Path_Final.h"
#include "Light_State_Final.h"

void pick_up()
{
  
  int val = 0;     // Value for smooth turning

  for (int i =0; i < 3;i++) // repeat collection for 3 times
  {
    while(val < 80)
    {
      val += 1;
      myservo.write(val);
      delay(30);
      Serial.println(val);
    }
    delay(800);  

    while (val > 65)
    {
      val -= 1;
      myservo.write(val);
      delay(30);
      Serial.println(val);
    }
    
    delay(800);
    //Serial.println(i);
  }
}

void drop_off() // Function to drop the object whenever the robot is at the junction facing towards the drop off point
{
  // IF the robot isn't going forward/backward in a straight enough manner i think we can reduce the speed of it going forward and backward so that its slow enough to where like stuff should hit it off or smth (if rlly bad just change each wheel to spin at different amounts)
  chassis_currently_moving = true;

  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 1000 ;      // Time we want the program to run for (in milliseconds)
  while(millis() - startTime < runDuration);
  {
    chassis_forward();
  }

    
    myservo.write(105);     // Spinning the Servos to push the waste out of the catchment 
    delay(700);     // Pushout        
    myservo.write(80);      // Back to initial

    delay(15);


  startTime=millis();     // Variable to store the start time
  runDuration = 1800 ;      // Time we want the program to run for (in milliseconds)
  while(millis() - startTime < runDuration);
  {
    chassis_backward();
  }

  ml -> run(RELEASE);
  mr -> run(RELEASE);

  chassis_currently_moving = false;

}

void object_detection()
{
  int svl1 = digitalRead(sl1);
  int svr1 = digitalRead(sr1);

  //while the chassis is on the line

  chassis_currently_moving = true;
  
  chassis_backward();
  delay(2000);

  while(digitalRead(pe_sensor_pin) == false)
  {
    chassis_forward();
  }

  delay(500);

  chassis_currently_moving = false;

  ml -> run(RELEASE);
  mr -> run(RELEASE);

  delay(5);

}