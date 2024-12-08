#include <Arduino.h>
#include "List_of_Path_Final.h"
#include "Line_Following_Final.h"  // For functions: chassis_forward(),chassis_turn_left90(),chassis_turn_right90()
#include "Servo_Final.h"           // For functions: pick_up(), drop_off()
#include "Route_of_Chassis_Final.h"        // For the routes
#include "Light_State_Final.h"        // To update chassis_currently_moving variable for the flashing lights


void execute_list(int list[], int listSize)     // This function intakes a list of the path to take and the size of that list, it then follows it
{
  int counter = 0;

  while (counter < listSize)
  {
    int svr = digitalRead(sr);      // Reading all the sensors
    int svl = digitalRead(sl);
    int svm = digitalRead(sm);
    int svr1 = digitalRead(sr1);
    int svl1 = digitalRead(sl1);


    if (list[counter] == 6)     // This is put here so it can start once its past the prior junction and can go along the entire length of the line to find and pickup the block
      { 
        object_detection();
        pick_up();

        chassis_backward();
        counter+= 1;
      }
    

    svr = digitalRead(sr);      // Reading all the sensors
    svl = digitalRead(sl);
    svm = digitalRead(sm);
    svr1 = digitalRead(sr1);
    svl1 = digitalRead(sl1);


    if ((svl == LOW && svm == HIGH && svr == LOW) || (svl == HIGH && svm == HIGH && svr == HIGH))     // Go forward
    {
      chassis_forward(); 
    }   
    
    if (svl == HIGH && svm == HIGH && svr == LOW)   // Turn fainlty left
    {
      chassis_turn_left();
    }

    if (svl == HIGH && svm == LOW && svr == LOW)      // Turn strongly left
    {
      chassis_turn_super_left();
    }

    if (svl == LOW && svm == HIGH && svr == HIGH)     // Turn faintly right
    {
      chassis_turn_right();
    }

    if (svl == LOW && svm == LOW && svr == HIGH)      // Turn strongly right
    {
      chassis_turn_super_right();
    }

    while ((svl1 == HIGH) || (svr1 == HIGH))      // So what happens when the robot is at the junction
    {

      if (list[counter] == 0)     // Goes past the junction
      { 
        chassis_forward();
        delay(600);
        counter += 1;
        break;
      } 
      
      else if (list[counter] == 1)      // To turn left at the junction 
      {
        chassis_turn_left90();

        // This is so the robot auto-corrects itself if it over turns
        svr = digitalRead(sr);      // Reading all the sensors
        svl = digitalRead(sl);
        svm = digitalRead(sm);
        while (svl == LOW && svm == LOW && svr == LOW)
        {
          svr = digitalRead(sr);      
          svl = digitalRead(sl);
          svm = digitalRead(sm);

          mr->setSpeed(180);     // Sets inner wheel to a lower speed
          ml->setSpeed(250);      // Sets outer wheel to a greater speed
          mr->run(FORWARD);     // Starts the wheels to spinnnnn
          ml->run(FORWARD);
        }

        ml->run(RELEASE);
        mr->run(RELEASE); 
        counter += 1;
        break;
      } 
      
      else if (list[counter] == 2) 
      {
        chassis_turn_right90();     // To turn left at the junction

        // This is so the robot auto-corrects itself if it over turns
        svr = digitalRead(sr);      // Reading all the sensors
        svl = digitalRead(sl);
        svm = digitalRead(sm);
        while (svl == LOW && svm == LOW && svr == LOW)
        {
          svr = digitalRead(sr);      
          svl = digitalRead(sl);
          svm = digitalRead(sm);

          ml->setSpeed(180);     // Sets inner wheel to a lower speed
          mr->setSpeed(250);      // Sets outer wheel to a greater speed
          mr->run(FORWARD);     // Starts the wheels to spinnnnn
          ml->run(FORWARD);
        }

        ml->run(RELEASE);
        mr->run(RELEASE);

        counter += 1;
        break;
      } 
      
      else if (list[counter] == 4)      // Once at a junction before the drop off point, that drops the waste inside the collection centre
      {
        chassis_turn_right90();

        // So there is some line following and it can adjust itself
        unsigned long start_time=millis();     // Variable to store the start time
        unsigned long run_duration = 1500 ;      // Time we want the program to run for (in milliseconds)
        while((millis() - start_time < run_duration))
        {
          svr = digitalRead(sr);      // Reading all the sensors
          svl = digitalRead(sl);
          svm = digitalRead(sm);

          if ((svl == LOW && svm == HIGH && svr == LOW) || (svl == HIGH && svm == HIGH && svr == HIGH))     // Go forward 
            {
              chassis_forward();
              delay(5);
            }

          if (svl == HIGH && svm == HIGH && svr == LOW)   // Turn fainlty left
            {
              chassis_turn_left();
              delay(5);
            }

          if (svl == LOW && svm == HIGH && svr == HIGH)     // Turn faintly right
            {
              chassis_turn_right();
              delay(5);
            }
        }

        drop_off();
        counter += 1;
        break;
      }   

      else if (list[counter] == 8)      // This is just to detemine which path to drop off the waste 
      {  
        if (digitalRead(magnetic_sensor_pin) == HIGH)
        {
        execute_list(node7_magnetic,3);     // This recursion should be fine - if problem can just make a funciton that just runs afer each execute_list(list) that just reads sensors and executes the list like make a void dropoff_pathing(){ if...}
        }
        
        else
        {
        execute_list(node7_nonmagnetic,5);
        }
      
        counter += 1;
        break;
      }

      else if (list[counter] == 10)     // Turn around 180 degreess (then reverse so its ontop of the junction)
      {
        chassis_currently_moving = true;
        
        ml->setSpeed(250);     // Sets inner wheel to a lower speed
        mr->setSpeed(250);      // Sets outer wheel to a greater speed
        mr->run(FORWARD);     // Starts the wheels to spinnnnn
        ml->run(BACKWARD);
        delay(2000);

        while((svl1 == LOW) || (svr1 == LOW))
        {
          chassis_backward();
          svr1 = digitalRead(sr1);
          svl1 = digitalRead(sl1);
        }

        ml->run(RELEASE);
        mr->run(RELEASE);

        chassis_currently_moving = false;

        delay(5);
        counter += 1;
        break;
      }
        
    }
  }
}



