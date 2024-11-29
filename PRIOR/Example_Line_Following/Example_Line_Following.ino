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

  Serial.println("Go Forward");
  delay(15);

}

void chassis_backward ()      // Function to move backwards in a straight line
{ 
  ml->setSpeed(backward_speed);
  mr->setSpeed(backward_speed-7);

  ml->run(BACKWARD);      //  The wheels start to spin
  mr->run(BACKWARD);

  delay(5);
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

  delay(5);
}

void chassis_turn_super_right()     // Function to read just the robot by a large amount to get back onto the line
{
  ml->setSpeed(forward_speedL);
  mr->setSpeed(forward_speedR - 60);

  ml->run(FORWARD);
  mr->run(FORWARD);

  delay(5);

}

void chassis_turn_left90()      // Rotates the robot 90 degress to the left
{ 
  // Single Turn

  /*
  while(digitalRead(sm)== HIGH)     // To allign the robot to be ontop of the junction
  {
    chassis_forward()
  }

  chassis_backward()      // So that the back sensors are on top of the line
  chassis_backward()
  chassis_backward()
  chassis_backward()
  chassis_backward()

  ml->setSpeed(250);
  mr->setSpeed(250);

  ml->run(BACKWARD);
  mr->run(FORWARD);

  // This is so it starts to turn just in case there is like a '+' junction so it gets past the line infront of itand then starts doing the time measuring for the correct turning amount
  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 600 ;      // Time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration)
  {}  

  // time taken for the top left sensor to hit then find the time taken for it to turn between each top sensor.

  while(digitalRead(sr1) == LOW)
  {
    if (digitalRead(sl1) == HIGH)
    {
      unsigned long just_before_line_time = millis();
    }
  }
  unsigned long just_after_line_time = millis();

  ml->run(FORWARD);
  mr->run(BACKWARD);

  while(millis() - just_after_line_time < (just_after_line_time - just_before_line_time)/2)
  {}

  ml->run(RELEASE);
  mr->run(RELEASE);
  */

  // Double Turn

  /*
  ml->setSpeed(250);
  mr->setSpeed(250);

  ml->run(BACKWARD);
  mr->run(FORWARD);

  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 800 ;      // Time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration)
  {}  

  int prior_state = digitalRead(sl);

  // This loop moves the chassis_forward until the back left sensor goes from low to high (which means its onto the next line)
  while(true)
  {
    chassis_forward();

    int current_state = digitalRead(sl);

    if (prior_state == LOW && current_state == HIGH)
      {
        break;
      }

    prior_state = current_state;

    delay(5);
  }

  // This is the second turn and it should turn itself off after its detected the next line

  mr->run(FORWARD);     // To start the second turn
  ml->run(BACKWARD);

  while(digitalRead(sr1) == LOW)      // To measure the time it takes for the two top sensors to touch/pass over the line
  {
    if (digitalRead(sl1) == HIGH)
    {
      unsigned long just_before_line_time = millis();
    }
  }
  unsigned long just_after_line_time = millis();

  ml->run(FORWARD);
  mr->run(BACKWARD);

  // Telling it to reverse and line up back onto the line
  while(millis() - just_after_line_time < (just_after_line_time - just_before_line_time)/2)
  {}

  ml->run(RELEASE);
  mr->run(RELEASE);


  delay(5);*/
  

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
  mr->setSpeed(0);     // Sets inner wheel to a lower speed
  ml->setSpeed(250);      // Sets outer wheel to a greater speed
  mr->run(FORWARD);     // Starts the wheels to spinnnnn
  ml->run(FORWARD);

  startTime=millis();     // Variable to store the start time
  runDuration = 500 ;      // Time we want the program to run for (in milliseconds)



  while(millis() - startTime < runDuration)
  {}

  ml->run(RELEASE);
  mr->run(RELEASE);

  delay(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  svr = digitalRead(sr);      // Reading all the sensors
  svl = digitalRead(sl);
  svm = digitalRead(sm);
  svr1 = digitalRead(sr1);
  svl1 = digitalRead(sl1);
  


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
 
  if (svl == HIGH && svm == LOW && svr == LOW)      // Turn strongly left
  {
    chassis_turn_super_left();
  }

  if (svl == LOW && svm == LOW && svr == HIGH)      // Turn strongly right
  {
    chassis_turn_super_right();
  }
/*
  if (svl1 == HIGH && svr1 == LOW){
    chassis_turn_left90();
  }*/

 if (svl1 == LOW && svr1 == HIGH){
    chassis_turn_right90();
  }


  Serial.print("L:");
  Serial.print(digitalRead(sl));
  Serial.print("    M:");
  Serial.print(digitalRead(sm));
  Serial.print("    R:");
  Serial.println(digitalRead(sr));
}