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

  ml->setSpeed(50);     // Sets inner wheel to a lower speed:50
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

  mr->setSpeed(30);     // Sets inner wheel to a lower speed
  ml->setSpeed(250);      // Sets outer wheel to a greater speed
  mr->run(FORWARD);     // Starts the wheels to spinnnnn
  ml->run(FORWARD);
  delay(2500);   //2100

  ml->run(RELEASE);
  mr->run(RELEASE);

  chassis_currently_moving = false;

  delay(5);
}

void get_me_out_of_the_starting_box()     // This function simply gets the robot out of the inital starting area so it can then continue with the line following after that
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

void get_me_into_the_starting_box()     // Gets back into starting area
{
  chassis_currently_moving = true;
  // Enters the box
  chassis_forward();

  // Move for 1s
  unsigned long start_time=millis();     // Variable to store the start time
  unsigned long run_duration = 1000 ;      // Time we want the program to run for (in milliseconds)
  while(millis() - start_time < run_duration);
  {
    chassis_forward();
  }

  // Stop moving
  ml->run(RELEASE);
  mr->run(RELEASE);     // Starts the wheels to spinnnnn

  chassis_currently_moving = false;
  
}



