#include <Adafruit_MotorShield.h>

int magneticSensor = 2;     // Pin for Magnetic sensor
int button_pin = 3; // Pin for Button 
int sr = 4;  // Pin for right sensor  (of the three in a row)
int sl = 5;    // Pin for left sensor  (of the three in a row)
int sm = 6;   // Pin for middle sensor  (of the three)
int sr1 = 7 ; // Pin for  top right sensor
int sl1 = 8;  // Pin for  top left sensor
int pe_sensor_pin = 9; // Pin for Photoelectric sensor



int svr = 0;   // Default values of sensors
int svr1 = 0;
int svl = 0;
int svl1 = 0;
int svm = 0;
int pe_sensor_value = 0;

int forward_speedL = 220;  // Default values of motor //might want to change this back up if time to complete the path is a problem and reduce this value if line following is really bad
int forward_speedR = 210;
int backward_speed = 150;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();     // Setting up MotorShield
Adafruit_DCMotor *mr = AFMS.getMotor(3);      // Setting up motors M3, M4
Adafruit_DCMotor *ml = AFMS.getMotor(4);

// All below is just pathing stuff, creating an array of list of all the commands it should do
int current_path = 0;
int turning_counter = 0;

int path0[] = {1,2,0,2,99,3};     // Once we finish the picking up object code the path should be {5,1,2,0,2,3} // this new line works fine if 5 (picking up the box) doesnt move the robot :)
int path1[] = {5,2,2,2,3};
int path2[] = {1,6,1,1,4};
int path3[] = {1,2,2,6,0,2,0,2,3};
int path4[] = {2,1,1,2};      // This just code returning the AGV back to the start box // we need to add some extra code to make it go into that final finish box maybe something like we did at the start to get it back in the boxxx

int* array_of_paths[] = {path0,path1,path2,path3,path4};

//so you want it to go on array_of_paths[current_path][turning_counter]


void setup()
{
  pinMode(sr,INPUT);         // Setting up each line sensor
  pinMode(sl,INPUT);
  pinMode(sm,INPUT);
  pinMode(sl1,INPUT);
  pinMode(sr1,INPUT);
  pinMode(pe_sensor_pin,INPUT);      //Setting up PhotoElectric Sensor
  pinMode(magneticSensor,INPUT);        //Setting up Magnetic Sensor
  pinMode(button_pin, INPUT);      //Setting up Button


  Serial.begin(9600);           // Set up Serial library at 9600 bps

  // 0, 1（左）, 2（右） 转向
  // 碰到junction就判断是否要转向
  //转到左边的垃圾场

  if (!AFMS.begin()) // Setting up Motor Shield
  {         
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");


  while (digitalRead(button_pin) == LOW) // Code only starts once the button is pressed
  {}

}



void chassis_forward ()     // Move forward in a straight line
{ 
  ml->setSpeed(forward_speedL);
  mr->setSpeed(forward_speedR);

  mr->run(FORWARD);     // Starts the wheels to spin
  ml->run(FORWARD);

  delay(5);
}

void chassis_backward ()      // Function to move backwards in a straight line
{ 
  ml->setSpeed(backward_speed);
  mr->setSpeed(backward_speed-7);

  ml->run(BACKWARD);      //  The wheels start to spin
  mr->run(BACKWARD);
}

void chassis_turn_left ()     // Function to make it turn left slightly
{
  /*
  //if the for loop doesnt work :(
  ml->setSpeed(forward_speed-25);
  */

  ml ->setSpeed(forward_speedL - 26);
  mr ->setSpeed(forward_speedR);  
  
  ml->run(FORWARD);
  mr->run(FORWARD);
  
  delay(5);

  // for (int i=forward_speed; i>forward_speed-26; i-=2)     // Slowly decreases speed down so its smoother (if it works)
  // {
  //   // if (svl == LOW && svm == HIGH && svr == HIGH)  // So the for loop breaks if its realligned itself/ gone far off the line intead of continuing the loop even though this piece of code is no longer relevant
  //   // {
  //   ml->setSpeed(i);
  //   mr->setSpeed(forward_speed);

  // //     Serial.println(i);

  // //     // svr=digitalRead(sr); // reading all the sensors
  //     // svl=digitalRead(sl);
  //     // svm =digitalRead(sm);

  //     mr->run(FORWARD);
  //     ml->run(FORWARD);

  // }
  // while (svl == LOW && svm == HIGH && svr == HIGH){
  //   ml->setSpeed(forward_speed-26);
  //   ml->run(FORWARD);
  //   svr=digitalRead(sr); // reading all the sensors
  //   svl=digitalRead(sl);
  //   svm =digitalRead(sm);
  // }
}
  
  
  // // while(svr == LOW && svm == HIGH && svl == HIGH)     // To hold the motor at the lowest speed until the parameters change (because if it leaves the function when the loop ends itll just recall this function changing the speed back to forward_speed and do the loop, basically if this wasnt here it would continues do the loop of=ver and over which is not good [ it might be good yk])
  // // {
  //   svr=digitalRead(sr);      // Reading all the sensors
  //   svl=digitalRead(sl);
  //   svm =digitalRead(sm);
  // // } 
    
void chassis_turn_super_left()      // Function to turn strongly to the left, if its off the line by a lot
{  
  ml->setSpeed(forward_speedL -50);
  mr->setSpeed(forward_speedR);

  ml->run(FORWARD);
  mr->run(FORWARD);

  delay(5);

  // for (int i=forward_speed; i>forward_speed-70; i-=10)     // Slowly decreases speed down so its smoother (if it works)
  // {
  //   // if (svl == LOW && svm == LOW && svr == HIGH)          // So the for loop breaks if its realligned itself/ gone far off the line intead of continuing the loop even though this piece of code is no longer relevant
  //   // {
  //     ml->setSpeed(i);
  //     mr->setSpeed(forward_speed);

  //     Serial.println(i);

  //     // svr=digitalRead(sr); // reading all the sensors
  //     // svl=digitalRead(sl);
  //     // svm =digitalRead(sm);

  //     mr->run(FORWARD);
  //     ml->run(FORWARD);
  // }
  // while (svl == LOW && svm == LOW && svr == HIGH){
  //   ml->setSpeed(forward_speed-70);
  //   ml->run(FORWARD);
  //   svr=digitalRead(sr); // reading all the sensors
  //   svl=digitalRead(sl);
  //   svm =digitalRead(sm);
  // }

    // }

    // else
    // {
    //   break;
    // }  
  }
 

void chassis_turn_right ()    // Slight right readjustment to the right
{ 
  ml->setSpeed(forward_speedL);
  mr->setSpeed(forward_speedR - 32);

  ml->run(FORWARD);
  mr->run(FORWARD);

  delay(5);
  // for (int i=forward_speed; i>forward_speed-26; i-=2)
  // {
  //   // if (svl == HIGH && svm == HIGH && svr == LOW)    // So the for loop breaks if its realligned itself/ gone far off the line intead of continuing the loop even though this piece of code is no longer relevant
  //   // {
  //     mr->setSpeed(i);
  //     ml->setSpeed(forward_speed);

  //     Serial.println(i);

  //     // svr=digitalRead(sr); // reading all the sensors
  //     // svl=digitalRead(sl);
  //     // svm =digitalRead(sm);

  // //     mr->run(FORWARD);

  // }

  
  //  while (svl == HIGH && svm == HIGH && svr == LOW){
  //   mr->setSpeed(forward_speed-26);
  //   mr->run(FORWARD);
  //   svr=digitalRead(sr); // reading all the sensors
  //   svl=digitalRead(sl);
  //   svm =digitalRead(sm);
  //   }
}
   

    //   ml->run(FORWARD);
    // }
    // else
    // {
    //   break;
    // }
  // }
  // // while(svr == HIGH && svm == HIGH && svl == LOW)     // To hold the motor at the lowest speed until the parameters change (because if it leaves the chassis turn function when the loop ends itll just recall this function changing the speed back to forward_speed and do the loop again, basically if this wasnt here it would continues do the loop over and over which is not good [ it might be good yk])
  // // {
  //   svr=digitalRead(sr); // Reading all the sensors
  //   svl=digitalRead(sl);
  //   svm =digitalRead(sm);

void chassis_turn_super_right()     // Function to read just the robot by a large amount to get back onto the line
{
  ml->setSpeed(forward_speedL);
  mr->setSpeed(forward_speedR - 60);

  ml->run(FORWARD);
  mr->run(FORWARD);
  
  delay(5);

  // for (int i=forward_speed; i>forward_speed-70; i-=10)
  // {
  //   // if(svl == HIGH && svm == LOW && svr == LOW)   
  //   // {

  //     ml->setSpeed(i);
  //     mr->setSpeed(forward_speed);

  //     Serial.println(i);

  //     // svr=digitalRead(sr); // reading all the sensors
  //     // svl=digitalRead(sl);
  //     // svm =digitalRead(sm);

  //     mr->run(FORWARD);
  //     ml->run(FORWARD);
  // }

  // while (svl == HIGH && svm == LOW && svr == LOW){
  //   mr->setSpeed(forward_speed-70);
  //   mr->run(FORWARD);
  //   svr=digitalRead(sr); // reading all the sensors
  //   svl=digitalRead(sl);
  //   svm =digitalRead(sm);
  // }
  }
  //   else
  //   {
  //     break;
  //   }  
  // // }
  // while(svl == HIGH && svm == LOW && svr == LOW)     // To hold the motor at the lowest speed until the parameters change (because if it leaves the chassis turn function when the loop ends itll just recall this function changing the speed back to forward_speed and do the loop again, basically if this wasnt here it would continues do the loop over and over which is not good [ it might be good yk])
  // // {
  //   svr=digitalRead(sr); // Reading all the sensors
  //   svl=digitalRead(sl);
  //   svm =digitalRead(sm);
  // } 


void chassis_turn_left90()      // Rotates the robot 90 degress to the left
{  
  //backward
  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 800 ;      // Time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration)
  {
    chassis_backward();
  }  
  //first turning : total time for turning = 2600 to make the chassis horizontal, given its speed (0,250)
  ml->setSpeed(100);     // Sets inner wheel to a lower speed
  mr->setSpeed(250);      // Sets outer wheel to a greater speed
  mr->run(FORWARD);     // Starts the wheels to spinnnnn
  ml->run(FORWARD);

  startTime=millis();     // Variable to store the start time
  runDuration = 2800 ;      // Time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration)
  {}

  //forward
  startTime=millis();     // Variable to store the start time
  runDuration = 800 ;      // Time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration)
  {
    chassis_forward();
  }

  //second turning
  // So it continues to turn until it lines up (hopefully works :)  )
  while(digitalRead(sr) == LOW){
    ml->setSpeed(0); 
  }

  ml->run(RELEASE);
  mr->run(RELEASE);

  delay(5);
}

void chassis_turn_right90()     // Turns the robot 90 degress to the right
{
//backward
  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 800 ;      // Time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration)
  {
    chassis_backward();
  }  
//first turning : total time for turning = 2600 to make the chassis horizontal, given its speed (0,250)
  mr->setSpeed(100);     // Sets inner wheel to a lower speed
  ml->setSpeed(250);      // Sets outer wheel to a greater speed
  mr->run(FORWARD);     // Starts the wheels to spinnnnn
  ml->run(FORWARD);

  startTime=millis();     // Variable to store the start time
  runDuration = 2800 ;      // Time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration)
  {}

//forward
  startTime=millis();     // Variable to store the start time
  runDuration = 800 ;      // Time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration)
  {
    chassis_forward();
  }
//second turning
  // So it continues to turn until it lines up (hopefully works :)  )
  while(digitalRead(sl) == LOW){
    mr->setSpeed(0); 
  }



  /*mr->setSpeed(0);     // Sets inner wheel to a lower speed
  ml->setSpeed(250);      // Sets outer wheel to a greater speed
  mr->run(FORWARD);     // Starts the wheels to spinnnnn
  ml->run(FORWARD);

  startTime=millis();     // Variable to store the start time
  runDuration = 500 ;      // Time we want the program to run for (in milliseconds)



  while(millis() - startTime < runDuration)
  {}*/

  ml->run(RELEASE);
  mr->run(RELEASE);

  delay(5);
}

/*      
// NEED TO FINISH THIS FUNCTION OFF + CHANGE THE TIMING SO IT WORKS PROPERLLY
void drop_off() // Function to drop the object whenever the robot is at the junction facing towards the drop off point
{
  // IF the robot isn't going forward/backward in a straight enough manner i think we can reduce the speed of it going forward and backward so that its slow enough to where like stuff should hit it off or smth (if rlly bad just change each wheel to spin at different amounts)

  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 1000 ;      // Time we want the program to run for (in milliseconds)
  while(millis() - startTime < runDuration);
  {
    chassis_forward();
  }

  // ADD CODE TO SPIN SERVOS
  // then it should just spin the servos to push the box off the catchment

  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 1800 ;      // Time we want the program to run for (in milliseconds)
  while(millis() - startTime < runDuration);
  {
    chassis_backward();
  }
}

void grab_object()
{
  // the code here is literally only: spin the servo so that it pushes the object into the basket. Thats it :)

}

void chassis_path_from7()      // Function to drop off the waste at the respective drop off point given that the robot is at junction number 7 (all junctions were numbered and that photo can be seen on the word document we shared) (the robot is assumed ot be facing to the left) (chassis_dropoff_fromL) 
{     
  //so put like code here on what to do when it reaches junction 7 / bit where it needs to consider drop off of the waste
  
  if (digitalRead(magneticSensor)==HIGH)      // If the waste is detected to be magnetic it goes down the path that goes from junction 8 to the recycling centre then back to junction 5
  { 
    
    chassis_turn_right90();
    delay(10);
    while (svr1==LOW)
    {
      svr1 = digitalRead(sr1);
      chassis_forward();
    }
    chassis_turn_right90();
    drop_off(); //this should just go forward drop off item then reverse back to the junction []
    chassis_turn_left90();
    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward();
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    ml->run(RELEASE);
    mr->run(RELEASE);
    

  }

  else if (digitalRead(magneticSensor) == LOW)      // If the waste is detected to be non-magnetic it goes down the path that goes from junction 8 to the landfill then back to junction 5
  {

    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward();
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    chassis_turn_right90();
    drop_off(); // this should just go forward drop off item then reverse back to the junction []
    chassis_turn_right90();

    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward();
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    chassis_turn_left90();
    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward();
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    // This below is so it can drive past the junction (as we cant use the sensors as they are already ontop of the current junction, so it needs to get past the junction using some other method - therefore moving it forward for a small amount of time will be fine to allow it drive onto the next junction)
    unsigned long startTime=millis();     // Variable to store the start time
    unsigned long runDuration = 1000 ;      // Time we want the program to run for (in milliseconds)
    while(millis() - startTime < runDuration);
    {
      chassis_forward();
    }

    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward();
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    ml->run(RELEASE);
    mr->run(RELEASE);

  }

  else      // This code is just to catch any logical errors come up
  {
    ml -> run(RELEASE);
    mr -> run(RELEASE);
    while(true)
    {}
  }


}


void chassis_path_from8()      // Function to drop off waste in correct position given the robot is at junction 8 (facing to the left)
{

  if (digitalRead(magneticSensor)==HIGH)      // If the waste is detected to be magnetic it goes down the path that goes from junction 8 to the recycling centre then back to junction 5
  {
    // To drive past the current junction 
    unsigned long startTime=millis();     // Variable to store the start time
    unsigned long runDuration = 1000 ;      // Time we want the program to run for (in milliseconds)
    while(millis() - startTime < runDuration)
    {
      chassis_forward();
    }

    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward();
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    chassis_turn_left90();

    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward();
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    chassis_turn_right90();
    drop_off();
    chassist_turn_left90();

    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward()
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    ml->run(RELEASE);
    mr->run(RELEASE);
    
  }
  else if (digitalRead(magneticSensor) == LOW)      // If the waste is detected to be non-magnetic it goes down the path that goes from junction 8 to the landfill then back to junction 5
  {
    chassis_turn_left90();
    drop_off();
    chassis_turn_right90();

    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward();
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    chassis_turn_left90();

    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward();
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    // To drive past the current junction 
    unsigned long startTime=millis();     // Variable to store the start time
    unsigned long runDuration = 1000 ;      // Time we want the program to run for (in milliseconds)
    while(millis() - startTime < runDuration)
    {
    chassis_forward();
    }

    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward();
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    ml->run(RELEASE);
    mr->run(RELEASE);

  }

  else      // This code is just to catch any logical errors come up
  {
    ml -> run(RELEASE);
    mr -> run(RELEASE);
    while(true)
    {}
  }
    
}



bool object_detection()     // Function that detects if the object is in front of the robot using the photoelectric sensor, and returns a boolean value
{
  sensor_value = digitalRead(pe_sensor_pin);

  if (sensor_value == HIGH)
  {
    return true;
  }

  else if (sensor_value == LOW)
  {
    return false;
  }

  delay(50);
}
*/


int first_step = 0;     // Variable to help the robot see if its inside the starting box or not


void loop()
{

  if (current_path == 0 && turning_counter == 0 && first_step==0)     // This is just to get the robot outside the starting box and get onto the line intially.
  {
    chassis_forward();

    while ((svm == LOW) || (svr == LOW) ||(svl==LOW))
    {
      svr=digitalRead(sr); 
      svl=digitalRead(sl);
      svm =digitalRead(sm);
    }

    first_step+=1;      // This is so the code only runs at the start of the robots movement and never again
  }

  svr = digitalRead(sr);      // Reading all the sensors
  svl = digitalRead(sl);
  svm = digitalRead(sm);
  svr1 = digitalRead(sr1);
  svl1 = digitalRead(sl1);

  Serial.print(svl);      // Printing the sensor values to help debug
  Serial.print(svm);
  Serial.print(svr);
  Serial.print(svr1);

  // Only using the bottom 3 line sensors (svr svm and svl) to detect the line and the line following
  // DOES THE SECOND LOGIC OF HIGH HIGH HIGH MAKE SENSE TO GO FORWARD? []
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


  if (svl == LOW && svm == LOW && svr == LOW)     // Spin right as it is lost
  {
    mr->run(BACKWARD);
    mr->setSpeed(forward_speedR);
    ml->run(FORWARD);
    ml->setSpeed(forward_speedL);
  }


  // Only using the top 2 sensors (svr1 and svl1) to detect junctions
  if ((svl1 == HIGH) || (svr1 == HIGH) )
  {
    if (array_of_paths[current_path][turning_counter] == 0)     //If current variable inside the path list = 0 then go forward
    {

      unsigned long startTime=millis();     // Variable to store the start time
      unsigned long runDuration = 2500 ;      // Time we want the program to run for (in milliseconds)

      while(millis() - startTime < runDuration)
      {
      chassis_forward();
      }
      
      turning_counter+=1;     // To go onto the next instruction in the path
    }

    else if (array_of_paths[current_path][turning_counter] == 1)     // If current variable inside the path list = 1 then turn left 90 degrees
    {
       if (current_path == 0 && turning_counter == 0 )
       {
         delay(300);     // We heuristically found that this works for the first left turn - to end up alligned nicely on the line once it completes the turn
       }

      chassis_turn_left90();
      turning_counter+=1; 
    }

    else if (array_of_paths[current_path][turning_counter] == 2)      // If current variable inside the path list = 2 then turn right 90 degrees
    {
      chassis_turn_right90();
      turning_counter+=1;
    }
  
    
    /*
    else if (array_of_paths[current_path][turning_counter] == 3)      // If current variable inside the path list = 3 then do the pathing from junction 7 that drops off the waste
    {
      chassis_path_from7();     // This route has to end at the same point as chassis_path_from8()
      current_path+=1;      // To go to the next path route
      turning_counter=0;      // So it starts at the first instruction on the new path route
    }

    else if (array_of_paths[current_path][turning_counter] == 4)      // If current variable inside the path list = 4 then do the pathing from junction 8 that drops off the waste
    {
      chassis_path_from8();
      current_path+=1;      // To go to the next path route
      turning_counter=0;      // So it starts at the first instruction on the new path route
    }
    
    else if (array_of_paths[current_path][turning_counter] == 5)      // Picking up stationary object of known placement    \\ for this picking up of known placement , we know they are both on a junction so if it detects junction -detects object - picks it up- and then reverses a bit so its able to detect the junction again and do the path stuff [simple :)]
    { 
      while(object_detection() == false)
      {
        chassis_backward();
      }

      ml -> run(RELEASE);
      mr -> run(RELEASE);

      grab_object();

      delay(15);

      while((svl1==LOW) || (svr1 == LOW))
      {
        chassis_forward();
        svr1 = digitalRead(sr1);
        svl1 = digitalRead(sl1);
      }

     // Just to check that the object is there (there is no point of having an if statement tbh - but i think this needs to be changed as this is most likely to not work from what is expected to what happens in reality ygm)
        
      turning_counter+=1;
    }
    
  */
  }
  /*
  // maybe this is code would be used too much so if the code slows down then :/   - Also if the robot is moving slow its probably becuase there is soo much code it has to go through before it loops
  // I  think this can work   [!!!!]// This is outside - if the front line sensors are detected - as this is to take place between the junctions
  if (array_of_paths[current_path][turning_counter] == 6)      // Picking up object with unknown placement        ITll work, i think->// how would this work logically as there is no junction before hand to detect to do work cos by then it would have bumped into the object so :/ what to do about this :/
    {
      forward_speed = 180;    // Slows down so it doesnt miss/ hit the waste or something (COULD REMOVE THIS LINE ALSO HOPEFULLY IT WORKS LIKE THIS)
      while((svl1==LOW) || (svr1 == LOW))
      {
        chassis_forward();
        if (object_detection()== true)      // If the object is detected
        {
          ml -> run(RELEASE);
          mr -> run(RELEASE);

          grab_object();

          ml -> run(forward);
          mr -> run(forward);

          forward_speed = 225;

        }

      }
      forward_speed = 225;
      turning_counter+=1;
    }
  */

    

}


