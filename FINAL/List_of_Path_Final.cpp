#include <Arduino.h>
#include "List_of_Path_Final.h"
#include "Line_Following_Final.h"  // For functions1; chassis_forward(),chassis_turn_left90(),chassis_turn_right90()
#include "Servo_Final.h"           // For functions: pick_up(), drop_off()
#include "Route_of_Chassis_Final.h"        // For the routes
#include "Light_State_Final.h"        // For the chassis_currently_moving variable for the flashing lights

//this is the function that intakes a list of path
void execute_list(int list[]) 
{
  int counter = 0;
  int listSize = sizeof(list);

  while (counter <= listSize)
  {

    int svr = digitalRead(sr);      // Reading all the sensors
    int svl = digitalRead(sl);
    int svm = digitalRead(sm);
    int svr1 = digitalRead(sr1);
    int svl1 = digitalRead(sl1);

    if ((svl == LOW && svm == HIGH && svr == LOW) || (svl == HIGH && svm == HIGH && svr == HIGH))     // Go forward - only middle sensor is on the line so it must be going straight
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

    while ((svl1 == HIGH) || (svr1 == HIGH))
    {

      if (list[counter] == 0) 
      { 
        chassis_forward();
        delay(600);
      } 
      
      else if (list[counter] == 1) 
      {
        chassis_turn_left90();
      } 
      
      else if (list[counter] == 2) 
      {
        chassis_turn_right90();
      } 
      
      /*else if (list[counter] == 3) 
      {
        pick_up();
      } */
      
      else if (list[counter] == 4) 
      {
        drop_off();
      } 
        
      else if (list[counter] == 6) 
      {
        object_detection();
        pick_up(); 

        chassis_backward();      // To ensure that its behind the juction
        delay(1000);

        ml -> run(RELEASE);     // To stop :P
        mr -> run(RELEASE);
      } 
      

      else if (list[counter] == 8) 
      {
        int magneticOutput = digitalRead(magnetic_sensor_pin);
        
        if (magneticOutput = HIGH)
        {
        execute_list(node7_magnetic) ;
        }
        else
        {
        execute_list(node7_nonmagnetic);
        }
      }

      else if (list[counter] == 10)     // Turn around 180 degreess (then reverse so its ontop of the junction)
      {
        chassis_currently_moving = true;
        
        ml->setSpeed(250);     // Sets inner wheel to a lower speed
        mr->setSpeed(250);      // Sets outer wheel to a greater speed
        mr->run(BACKWARD);     // Starts the wheels to spinnnnn
        ml->run(FORWARD);
        delay(2000);

        while((svl1 == LOW) || (svr1 == LOW))
        {
          chassis_backward();
        }

        ml->run(RELEASE);
        mr->run(RELEASE);

        chassis_currently_moving = false;

        delay(5);

      }
      
      counter += 1;
      
    }
  }
}



