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
  delay(50);   
  mr->setSpeed(240);      // Sets inner wheel to a lower speed
  ml->setSpeed(20);     // Sets outer wheel to a greater speed
  mr->run(FORWARD);     // The wheels start to spin
  ml->run(FORWARD);
  //delay(120);
  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 2270 ;      // Time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration)
  {}

  ml->run(RELEASE);     // Turns of the motors to prevent any over shoot and to start from a baseline amount for the next piece of code the robot runs.
  mr->run(RELEASE);

  delay(5);
  

}

void chassis_turn_right90()     // Turns the robot 90 degress to the right
{
  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 500 ;      // Time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration)
  {
    chassis_backward();
  }
  
 // delay(70);      // We found that this small delay helps the turn be a large enough of a turning circle to line up onto the line after the turn has completed
  mr->setSpeed(20);     // Sets inner wheel to a lower speed
  ml->setSpeed(250);      // Sets outer wheel to a greater speed
  mr->run(FORWARD);     // Starts the wheels to spinnnnn
  ml->run(FORWARD);

  startTime=millis();     // Variable to store the start time
  runDuration = 2600 ;      // Time we want the program to run for (in milliseconds)

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

  if (svl1 == HIGH && svr1 == LOW){
    chassis_turn_left90();
  }

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
