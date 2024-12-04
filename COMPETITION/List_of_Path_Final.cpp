#include <Arduino.h>
#include "List_of_Path_Final.h"
#include "Line_Following_Final.h"  // For functions: chassis_forward(),chassis_turn_left90(),chassis_turn_right90()
#include "Servo_Final.h"           // For functions: pick_up(), drop_off()
#include "Route_of_Chassis_Final.h"        // For the routes
#include "Light_State_Final.h"        // To update chassis_currently_moving variable for the flashing lights

//this is the function that intakes a list of path
void execute_list(int list[], int listSize) 
{
  int counter = 0;
  //int listSize = sizeof(list);            // sizeof() gives the 'byte size of the pointer 'list' ' wth

  while (counter < listSize)
  {

    int svr = digitalRead(sr);      // Reading all the sensors
    int svl = digitalRead(sl);
    int svm = digitalRead(sm);
    int svr1 = digitalRead(sr1);
    int svl1 = digitalRead(sl1);

    // ====== Remove this if :_( 
    if (list[counter] == 6)
      { 
        object_detection();
        pick_up();

        // move backward a bit so its back on the line (as it went off the line when getting the block)
        // Using line following so it goes back fine hopefully :/

        /*
        forward_speedL = forward_speedL - 50;     // So it moves slower
        forward_speedR = forward_speedR - 50;
        */
        chassis_backward();
        //delay(0);

        /*

        unsigned long startTime=millis();     // Variable to store the start time
        unsigned long runDuration = 1 ;      // Time we want the program to run for (in milliseconds)
        while((millis() - startTime < runDuration))
        {
          svr = digitalRead(sr);      // Reading all the sensors
          svl = digitalRead(sl);
          svm = digitalRead(sm);

          if ((svl == LOW && svm == HIGH && svr == LOW) || (svl == HIGH && svm == HIGH && svr == HIGH) || (svl == LOW && svm == LOW && svr == LOW))     // Go forward - only middle sensor is on the line so it must be going straight
            {
              ml->setSpeed(forward_speedL);
              mr->setSpeed(forward_speedR);

              ml->run(BACKWARD);      //  The wheels start to spin
              mr->run(BACKWARD);
              delay(5);

            }

          if (svl == HIGH && svm == HIGH && svr == LOW)   // Turn fainlty left
            {
              ml ->setSpeed(forward_speedL - 26);
              mr ->setSpeed(forward_speedR); 

              ml->run(BACKWARD);      //  The wheels start to spin
              mr->run(BACKWARD);
              delay(5);
            }

          if (svl == LOW && svm == HIGH && svr == HIGH)     // Turn faintly right
            {
              ml->setSpeed(forward_speedL);
              mr->setSpeed(forward_speedR - 32);

              ml->run(BACKWARD);      //  The wheels start to spin
              mr->run(BACKWARD);
              delay(5);
            }
        }*/

        counter+= 1;
        // svr1 = digitalRead(sr1);
        // svl1 = digitalRead(sl1);

        // while ((svl1 == LOW) || (svr1 == LOW))
        // {
        //   chassis_forward();
        //   svr1 = digitalRead(sr1);
        //   svl1 = digitalRead(sl1);
        // }

      }
    // ====== Remove this if :_( 

    svr = digitalRead(sr);      // Reading all the sensors
    svl = digitalRead(sl);
    svm = digitalRead(sm);
    svr1 = digitalRead(sr1);
    svl1 = digitalRead(sl1);

    //Can use else if but this works and i feel like it can there is little to no difference so i might as well leave it alone as this is moving perfect
    if ((svl == LOW && svm == HIGH && svr == LOW) || (svl == HIGH && svm == HIGH && svr == HIGH))     // Go forward - only middle sensor is on the line so it must be going straight
    {
      if (list[counter] == 6)
      {
        ml->setSpeed(forward_speedL - 85);
        mr->setSpeed(forward_speedR - 85);

        mr->run(FORWARD);     // Starts the wheels to spin
        ml->run(FORWARD);
      }
      else{
       chassis_forward(); 
      } 
      
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
        counter += 1;
        break;
      } 
      
      else if (list[counter] == 1) 
      {
        chassis_turn_left90();

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
        chassis_turn_right90();

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
      
      /*else if (list[counter] == 3) 
      {
        pick_up();
      } */
      
      else if (list[counter] == 4) 
      {
        chassis_turn_right90();


        // So there is some line following and it can adjust itself
        unsigned long startTime=millis();     // Variable to store the start time
        unsigned long runDuration = 1500 ;      // Time we want the program to run for (in milliseconds)
        while((millis() - startTime < runDuration))
        {
          svr = digitalRead(sr);      // Reading all the sensors
          svl = digitalRead(sl);
          svm = digitalRead(sm);

          if ((svl == LOW && svm == HIGH && svr == LOW) || (svl == HIGH && svm == HIGH && svr == HIGH))     // Go forward - only middle sensor is on the line so it must be going straight
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

      /*else if (list[counter] == 6) 
      {

        object_detection();
        pick_up(); 

        chassis_backward();      // To ensure that its behind the juction
        

        delay(500);

        ml -> run(RELEASE);     // To stop wheels
        mr -> run(RELEASE);
        counter += 1;
        break;
      }*/

      else if (list[counter] == 8) 
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



