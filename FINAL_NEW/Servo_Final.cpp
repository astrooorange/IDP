#include <Arduino.h>
#include "Servo_Final.h"
#include "Line_Following_Final.h"     // For functions1; chassis_forward(),chassis_turn_left90(),chassis_turn_right90()
#include "List_of_Path_Final.h"     // For the global variables sl1 and sr1
#include "Light_State_Final.h"      // To update chassis_currently_moving variable for the flashing lights

void pick_up()
{
//   myservo.write(80);
//   delay(15);
//   myservo.write(65);
//   myservo.write(80);
//   delay(15);
//   myservo.write(65);
//   myservo.write(80);
//   delay(15);
//   myservo.write(65);
  int i = 0;
  int val = 78;     // Value to help rotate the servo smoothly




//myservo.write(80); // 明确设置为初始角度 0°
  delay(100);
  ml->setSpeed(forward_speedL - 100);
  mr->setSpeed(forward_speedR - 100);


  mr->run(FORWARD);     // Starts the wheels to spin
  ml->run(FORWARD);

  while(i<1)     // Repeat collection 3 times
  {
    
    while(val < 80)     // Sweeping back to horizontal
    {
      val += 1;
      myservo.write(val);
      delay(15);
      Serial.println('now it is turning',val);
    }
    delay(800);  

    while (val > 60)      // Sweeping the object into the basket
    {
      val -= 1;
      myservo.write(val);
      delay(20);
      //Serial.println(val);
    }
    
    delay(500);
    //Serial.println(i);
    i+=1;
  }


  holding_object = true;

  ml -> run(RELEASE);
  mr -> run(RELEASE);
}

void drop_off()     // Function to drop the object whenever the robot is at the junction facing towards the drop off point
{
  int svr1 = digitalRead(sr1);
  int svl1 = digitalRead(sl1);

  chassis_currently_moving = true;
  Serial.println('drop off function is now running!!');

  ml -> run(RELEASE);
  mr -> run(RELEASE);
  
  int val = 65;      // From the pickup function and is used for the smooth rotation of the servo 

  // The actual code that pushes the waste off
  while (val < 105)     // Spinning the Servos to push the waste out of the catchment smoothly
  {
    val += 1;
    myservo.write(val);
    delay(15);
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

  // unsigned long startTime=millis();     // Variable to store the start time
  // unsigned long runDuration = 1000 ;      // Time we want the program to run for (in milliseconds)
  // while(millis() - startTime < runDuration)
  // {
  //   chassis_backward();
  // }

  chassis_backward();

  while ((svl1 == LOW) || (svr1 == LOW))
  {
    svr1 = digitalRead(sr1);
    svl1 = digitalRead(sl1);
  }

  // unsigned long startTime=millis();     // Variable to store the start time
  // unsigned long runDuration = 500 ;      // Time we want the program to run for (in milliseconds)
  // while(millis() - startTime < runDuration)
  // {
  //   chassis_backward();
  // }

  ml -> run(RELEASE);
  mr -> run(RELEASE);

  chassis_currently_moving = false;

}

void object_detection()
{
  // //while the chassis is on the line
  // chassis_currently_moving = true;
  
  chassis_backward();
  delay(30);

  int object_found = digitalRead(pe_sensor_pin);


  while(object_found == LOW)
  {
    Serial.println("This is pe sensor -> ");
    Serial.print(object_found);
    ml->setSpeed(forward_speedL - 30);
    mr->setSpeed(forward_speedR - 30);
    mr->run(FORWARD);     // Starts the wheels to spin
    ml->run(FORWARD);
    object_found = digitalRead(pe_sensor_pin);
  }

  delay(600);

  chassis_currently_moving = false;

  ml -> run(RELEASE);
  mr -> run(RELEASE);
}