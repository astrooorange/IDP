#include "Line_Following_Final.h"

void chassis_forward ()     // Move forward in a straight line
{ 
  ml->setSpeed(forward_speedL);
  mr->setSpeed(forward_speedR);

  mr->run(FORWARD);     // Starts the wheels to spin
  ml->run(FORWARD);

  Serial.println("Go Forward");
  delay(15);

}

void chassis_backward ()      // Function to move backwards in a straight line
{ 
  ml->setSpeed(backward_speed);
  mr->setSpeed(backward_speed-7);

  ml->run(BACKWARD);      //  The wheels start to spin
  mr->run(BACKWARD);

  delay(15);
}

void chassis_turn_left ()     // Function to make it turn left slightly
{

  ml ->setSpeed(forward_speedL - 26);
  mr ->setSpeed(forward_speedR);  
  
  ml->run(FORWARD);
  mr->run(FORWARD);
  delay(15);
}

void chassis_turn_right ()    // Slight right readjustment to the right
{ 
  ml->setSpeed(forward_speedL);
  mr->setSpeed(forward_speedR - 32);

  ml->run(FORWARD);
  mr->run(FORWARD);
  delay(15);

}

void chassis_turn_super_left()      // Function to turn strongly to the left, if its off the line by a lot
{  
  ml->setSpeed(forward_speedL -50);
  mr->setSpeed(forward_speedR);

  ml->run(FORWARD);
  mr->run(FORWARD);

  delay(15);
}

void chassis_turn_super_right()     // Function to read just the robot by a large amount to get back onto the line
{
  ml->setSpeed(forward_speedL);
  mr->setSpeed(forward_speedR - 60);

  ml->run(FORWARD);
  mr->run(FORWARD);

  delay(15);

}

void chassis_turn_leftt90() 
{  
  ml->setSpeed(250);     // Sets inner wheel to a lower speed
  mr->setSpeed(250);      // Sets outer wheel to a greater speed
  ml->run(BACKWARD);     // Starts the wheels to spinnnnn
  mr->run(FORWARD);
  delay(15);
}

void chassis_turn_right90() 
{  
  ml->setSpeed(250);     // Sets inner wheel to a lower speed
  mr->setSpeed(250);      // Sets outer wheel to a greater speed
  ml->run(FORWARD);
  mr->run(BACKWARD);     // Starts the wheels to spinnnnn
  delay(15);
}






