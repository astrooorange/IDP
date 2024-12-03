#include <Arduino.h>
#include "Servo_Final.h"
#include "Line_Following_Final.h"     // For functions1; chassis_forward(),chassis_turn_left90(),chassis_turn_right90()
#include "List_of_Path_Final.h"     // For the global variables sl1 and sr1
#include "Light_State_Final.h"      // To update chassis_currently_moving variable for the flashing lights

void pick_up()
{
  int i = 0;
  int val = 0;     // Value to help rotate the servo smoothly

  while(i<3)     // Repeat collection 3 times
  {
    while(val < 80)     // Sweeping back to horizontal
    {
      val += 1;
      myservo.write(val);
      delay(15);
      //Serial.println(val);
    }
    delay(800);  

    while (val > 65)      // Sweeping the object into the basket
    {
      val -= 1;
      myservo.write(val);
      delay(15);
      //Serial.println(val);
    }
    
    delay(800);
    //Serial.println(i);
    i+=1;
  }

  holding_object = true;
}

void drop_off()     // Function to drop the object whenever the robot is at the junction facing towards the drop off point
{

  chassis_currently_moving = true;

  // Move Robot down to the drop off point
  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 600 ;      // Time we want the program to run for (in milliseconds)
  while(millis() - startTime < runDuration)
  {
    chassis_forward();
  }

  ml -> run(RELEASE);
  mr -> run(RELEASE);
  
  int val = 65;      // From the pickup function and is used for the smooth rotation of the servo 

  // The actual code that pushes the waste off
  while (val < 105)     // Spinning the Servos to push the waste out of the catchment smoothly
  {
    val += 1;
    myservo.write(val);
    delay(15);
    //Serial.println(val);
  }
  delay(700);     // Pushout        
  
  while (val > 80)      // Smooth push back to initial
  {
    val -= 1;
    myservo.write(val);
    delay(15);
    //Serial.println(val);
  }

  delay(15);

  holding_object = false;

  // Reverses the robot back to the junction
  startTime=millis();     // Variable to store the start time
  runDuration = 1200 ;      // Time we want the program to run for (in milliseconds)
  while(millis() - startTime < runDuration)
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
  delay(800);

  chassis_forward();
  while(digitalRead(pe_sensor_pin) == false)
  {}

  delay(500);     // So once the object is detected to move it into good grabbing distance for the sweeper

  chassis_currently_moving = false;

  ml -> run(RELEASE);
  mr -> run(RELEASE);

  delay(5);

}