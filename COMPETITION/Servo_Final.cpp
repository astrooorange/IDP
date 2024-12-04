#include <Arduino.h>
#include "Servo_Final.h"
#include "Line_Following_Final.h"     // For functions1; chassis_forward(),chassis_turn_left90(),chassis_turn_right90()
#include "List_of_Path_Final.h"     // For the global variables sl1 and sr1
#include "Light_State_Final.h"      // To update chassis_currently_moving variable for the flashing lights

void pick_up()
{
  int i = 0;
  int val = 78;     // Value to help rotate the servo smoothly




//myservo.write(80); // 明确设置为初始角度 0°
  delay(10);
  ml->setSpeed(forward_speedL - 100);
  mr->setSpeed(forward_speedR - 100);


  while(i<1)     // Repeat collection 3 times
  {
    mr->run(FORWARD);     // So it moves forward a bit then goes to sweep then moves forward then sweeps to ensure its like inside the basket
    ml->run(FORWARD);
    delay(20);
    mr->run(RELEASE);     // So it moves forward a bit then goes to sweep then moves forward then sweeps to ensure its like inside the basket
    ml->run(RELEASE);

    while(val < 80)     // Sweeping back to horizontal
    {
      val += 1;
      myservo.write(val);
      delay(15);
      //Serial.println('now it is turning',val);
    }
    delay(800);  

    while (val > 50)      // Sweeping the object into the basket
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

  mr->run(RELEASE);     // So it moves forward a bit then goes to sweep then moves forward then sweeps to ensure its like inside the basket
  ml->run(RELEASE);
  holding_object = true;

  ml->setSpeed(114);
  mr->setSpeed(110);

  ml->run(BACKWARD);      //  The wheels start to spin
  mr->run(BACKWARD);
  delay(1200);   

  int svr1 = digitalRead(sr1);
  int svl1 = digitalRead(sl1);

  while ((svl1 == LOW) || (svr1 == LOW))
  {
    chassis_forward();
    svr1 = digitalRead(sr1);
    svl1 = digitalRead(sl1);
  }


}

void drop_off()     // Function to drop the object whenever the robot is at the junction facing towards the drop off point
{
  int svr1 = digitalRead(sr1);
  int svl1 = digitalRead(sl1);

  chassis_currently_moving = false;
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

  //chassis_backward();

  int svr = digitalRead(sr);      // Reading all the sensors
  int svl = digitalRead(sl);
  int svm = digitalRead(sm);

  while ((svl1 == LOW) || (svr1 == LOW))
  {
    svr1 = digitalRead(sr1);
    svl1 = digitalRead(sl1);

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

  //== Hypethetical object_detection() prior one is below if you wanna remove this :) - Also edit execute_list if you want to revert just the top if object == 6 line

  int object_found = digitalRead(pe_sensor_pin);
  int svr = digitalRead(sr);     
  int svl = digitalRead(sl);
  int svm = digitalRead(sm);

  //forward_speedL = forward_speedL - 50;     // So it moves slower
  //forward_speedR = forward_speedR - 50;

  while(object_found == HIGH)      // Moves forward while not detected the waste so its currently just finding the block
  {
    object_found = digitalRead(pe_sensor_pin);
    svr = digitalRead(sr);     
    svl = digitalRead(sl);
    svm = digitalRead(sm);

    
    // So its just going forward but only like slower and detecting :)
    if ((svl == LOW && svm == HIGH && svr == LOW) || (svl == HIGH && svm == HIGH && svr == HIGH))     // Go forward - only middle sensor is on the line so it must be going straight
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

  // So now it should have detected it and its infront

  
  // This is just s that it continue to move forward for runDuration (0.3 sec)  so that the waste is infront of the grabber, value needs to be changed depending on how far the chassis goes to the box. Alter until perfeclty in it
  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 1000 ;      // Time we want the program to run for (in milliseconds)
  while(millis() - startTime < runDuration)
  {
    svr = digitalRead(sr);     
    svl = digitalRead(sl);
    svm = digitalRead(sm);

    
    // So its just going forward but only like slower and detecting :)
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


  /*
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


  */

}