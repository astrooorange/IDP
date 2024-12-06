#include <Arduino.h>
#include "Servo_Final.h"
#include "Line_Following_Final.h"     // For functions1; chassis_forward(),chassis_turn_left90(),chassis_turn_right90()
#include "List_of_Path_Final.h"     // For the global variables sl1 and sr1
#include "Light_State_Final.h"      // To update chassis_currently_moving variable for the flashing lights

void pick_up()
{
  int i = 0;
  int val = 78;     // Value to help rotate the servo smoothly


  delay(10);
  ml->setSpeed(forward_speedL - 100);     // So it moves forward slowly
  mr->setSpeed(forward_speedR - 100);


  while(i<1)     // Opportuninty to repeat collection 
  {
    mr->run(FORWARD);     // So it moves forward a bit then goes to sweep to help get the object inside the basket
    ml->run(FORWARD);
    delay(20);
    mr->run(RELEASE);     
    ml->run(RELEASE);

    while(val < 80)     // Sweeping back to horizontal
    {
      val += 1;
      myservo.write(val);
      delay(15);
    }
    delay(800);  

    while (val > 50)      // Sweeping the object into the basket
    {
      val -= 1;
      myservo.write(val);
      delay(20);
    }
    
    delay(500);
    i+=1;
  }

  mr->run(RELEASE);    
  ml->run(RELEASE);

  holding_object = true;

  // Reverses the robot
  ml->setSpeed(114);
  mr->setSpeed(110);

  ml->run(BACKWARD);      
  mr->run(BACKWARD);
  delay(1200);   

  int svr1 = digitalRead(sr1);
  int svl1 = digitalRead(sl1);

  while ((svl1 == LOW) || (svr1 == LOW))      // Drives forward until the next junction (so the next code in the routing path can be ran)
  {
    chassis_forward();
    svr1 = digitalRead(sr1);
    svl1 = digitalRead(sl1);
  }
}

void drop_off()     // Function to drop the object whenever the robot facing towards the drop off point
{
  int svr1 = digitalRead(sr1);
  int svl1 = digitalRead(sl1);

  chassis_currently_moving = false;

  ml -> run(RELEASE);
  mr -> run(RELEASE);
  
  int val = 65;      // Used for the smooth rotation of the servo 

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
  }

  delay(15);

  holding_object = false;

  int svr = digitalRead(sr);      // Reading all the sensors
  int svl = digitalRead(sl);
  int svm = digitalRead(sm);

  while ((svl1 == LOW) || (svr1 == LOW))      // To get the robot to get back to the junction while doing some line following to stay on track
  {
    // Reading all the sensors
    svr1 = digitalRead(sr1);
    svl1 = digitalRead(sl1);
    svr = digitalRead(sr);     
    svl = digitalRead(sl);
    svm = digitalRead(sm);

    if ((svl == LOW && svm == HIGH && svr == LOW) || (svl == HIGH && svm == HIGH && svr == HIGH) || (svl == LOW && svm == LOW && svr == LOW))     // Go Backward
      {
        ml->setSpeed(forward_speedL);
        mr->setSpeed(forward_speedR);

        ml->run(BACKWARD);      //  The wheels start to spin backwards
        mr->run(BACKWARD);
        delay(5);
      }

    if (svl == HIGH && svm == HIGH && svr == LOW)   // Turn fainlty left
      {
        ml ->setSpeed(forward_speedL - 26);
        mr ->setSpeed(forward_speedR); 

        ml->run(BACKWARD);      //  The wheels start to spin backwards
        mr->run(BACKWARD);
        delay(5);
      }

    if (svl == LOW && svm == HIGH && svr == HIGH)     // Turn faintly right
      {
        ml->setSpeed(forward_speedL);
        mr->setSpeed(forward_speedR - 32);

        ml->run(BACKWARD);      //  The wheels start to spin backwards
        mr->run(BACKWARD);
        delay(5);
      }
  }

  ml -> run(RELEASE);
  mr -> run(RELEASE);

  chassis_currently_moving = false;
}

void object_detection()     // Function finds the object and alligns the robot to be in range to pick it up
{
  int object_found = digitalRead(pe_sensor_pin);
  int svr = digitalRead(sr);     
  int svl = digitalRead(sl);
  int svm = digitalRead(sm);


  while(object_found == HIGH)      // Moves forward while not detected the waste so its currently just finding the block
  {
    object_found = digitalRead(pe_sensor_pin);
    svr = digitalRead(sr);     
    svl = digitalRead(sl);
    svm = digitalRead(sm);

    
    // So its just going forward but at a slower pace and detecting :)
    if ((svl == LOW && svm == HIGH && svr == LOW) || (svl == HIGH && svm == HIGH && svr == HIGH))     // Go forward
    {
      ml->setSpeed(forward_speedL - 50);
      mr->setSpeed(forward_speedR - 50);

      ml->run(FORWARD);      //  The wheels start to spin
      mr->run(FORWARD);
      delay(5);       
    }

    if (svl == HIGH && svm == HIGH && svr == LOW)   // Turn fainlty left
    {
      ml ->setSpeed(forward_speedL - 26 - 50 );
      mr ->setSpeed(forward_speedR - 50); 

      ml->run(FORWARD);      //  The wheels start to spin
      mr->run(FORWARD);
      delay(5);
    }

    if (svl == LOW && svm == HIGH && svr == HIGH)     // Turn faintly right
    {
      ml->setSpeed(forward_speedL - 50);
      mr->setSpeed(forward_speedR - 32 - 50);

      ml->run(FORWARD);      //  The wheels start to spin
      mr->run(FORWARD);
      delay(5);
    }


  }

  // So now it should have detected it and its infront so move forward a bit 

  
  unsigned long start_time=millis();     // Variable to store the start time
  unsigned long run_duration = 1000 ;      // Time we want the program to run for (in milliseconds)
  while(millis() - start_time < run_duration)
  {
    svr = digitalRead(sr);     
    svl = digitalRead(sl);
    svm = digitalRead(sm);

    
    if ((svl == LOW && svm == HIGH && svr == LOW) || (svl == HIGH && svm == HIGH && svr == HIGH))     // Go forward - only middle sensor is on the line so it must be going straight
    {
      chassis_forward();       
    }

    if (svl == HIGH && svm == HIGH && svr == LOW)   // Turn fainlty left
    {
      chassis_turn_left();
    }

    if (svl == LOW && svm == HIGH && svr == HIGH)     // Turn faintly right
    {
      chassis_turn_right();
    }
  }
     

  ml -> run(RELEASE);
  mr -> run(RELEASE);

}