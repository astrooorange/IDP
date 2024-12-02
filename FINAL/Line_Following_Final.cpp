#include "Line_Following_Final.h"
#include "Light_State_Final.h"      // To update chassis_currently_moving variable for the flashing lights


void chassis_forward ()     // Move forward in a straight line
{ 
  chassis_currently_moving = true;

  ml->setSpeed(forward_speedL);
  mr->setSpeed(forward_speedR);

  mr->run(FORWARD);     // Starts the wheels to spin
  ml->run(FORWARD);

  Serial.println("Go Forward");
  delay(15);

}

void chassis_backward ()      // Function to move backwards in a straight line
{ 
  chassis_currently_moving = true;

  ml->setSpeed(backward_speed);
  mr->setSpeed(backward_speed-7);

  ml->run(BACKWARD);      //  The wheels start to spin
  mr->run(BACKWARD);

  delay(15);
}

void chassis_turn_left ()     // Function to make it turn left slightly
{
  chassis_currently_moving = true;

  ml ->setSpeed(forward_speedL - 26);
  mr ->setSpeed(forward_speedR);  
  
  ml->run(FORWARD);
  mr->run(FORWARD);
  delay(15);
}

void chassis_turn_right ()    // Slight right readjustment to the right
{ 
  chassis_currently_moving = true;

  ml->setSpeed(forward_speedL);
  mr->setSpeed(forward_speedR - 32);

  ml->run(FORWARD);
  mr->run(FORWARD);
  delay(15);

}

void chassis_turn_super_left()      // Function to turn strongly to the left, if its off the line by a lot
{  
  chassis_currently_moving = true;

  ml->setSpeed(forward_speedL -50);
  mr->setSpeed(forward_speedR);

  ml->run(FORWARD);
  mr->run(FORWARD);

  delay(15);
}

void chassis_turn_super_right()     // Function to read just the robot by a large amount to get back onto the line
{
  chassis_currently_moving = true;

  ml->setSpeed(forward_speedL);
  mr->setSpeed(forward_speedR - 60);

  ml->run(FORWARD);
  mr->run(FORWARD);

  delay(15);

}

void chassis_turn_left90() 
{  
  chassis_currently_moving = true;

  ml->setSpeed(60);     // Sets inner wheel to a lower speed
  mr->setSpeed(250);      // Sets outer wheel to a greater speed
  mr->run(FORWARD);     // Starts the wheels to spinnnnn
  ml->run(FORWARD);
  delay(2250);

  ml->run(RELEASE);
  mr->run(RELEASE);

  chassis_currently_moving = false;

  delay(5);
}

void chassis_turn_right90() 
{  
  chassis_currently_moving = true;

  mr->setSpeed(50);     // Sets inner wheel to a lower speed
  ml->setSpeed(250);      // Sets outer wheel to a greater speed
  mr->run(FORWARD);     // Starts the wheels to spinnnnn
  ml->run(FORWARD);
  delay(2200);

  ml->run(RELEASE);
  mr->run(RELEASE);

  chassis_currently_moving = false;

  delay(5);
}

void get_me_out_of_the_starting_box()
{
  chassis_currently_moving = true;

  chassis_forward();
  int svr=digitalRead(sr); 
  int svl=digitalRead(sl);
  int svm =digitalRead(sm);
    while ((svm == LOW) || ( svr == LOW) ||(svl==LOW))
    {
      svr=digitalRead(sr); 
      svl=digitalRead(sl);
      svm =digitalRead(sm);
    }
}

void get_me_into_the_starting_box()
{
  chassis_currently_moving = true;
  //enters the box
  chassis_forward();

  //move for 1s
  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 1000 ;      // Time we want the program to run for (in milliseconds)
  while(millis() - startTime < runDuration);
  {
    chassis_forward();
  }

  //stop moving
  ml->run(RELEASE);
  mr->run(RELEASE);     // Starts the wheels to spinnnnn

  chassis_currently_moving = false;
  
}



