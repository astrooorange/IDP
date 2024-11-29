#include <Adafruit_MotorShield.h>


#include "Line_Following_Final.h"

int button_pin = 3; // Pin for Button 

int sr = 4;  // Pin for right sensor  (of the three in a row)
int sl = 5;    // Pin for left sensor  (of the three in a row)
int sm = 6;   // Pin for middle sensor  (of the three)
int sr1 = 7 ; // Pin for  top right sensor
int sl1 = 8;  // Pin for  top left sensor




int svr = 0;   // Default values of sensors
int svr1 = 0;
int svl = 0;
int svl1 = 0;
int svm = 0;


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
  pinMode(button_pin, INPUT);      //Setting up Button


  Serial.begin(9600);           // Set up Serial library at 9600 bps

  if (!AFMS.begin()) // Setting up Motor Shield
  {         
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");


  while (digitalRead(button_pin) == LOW) // Code only starts once the button is pressed
  {}

}



void loop() {
 
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

  // Debugging
  Serial.print("L:");
  Serial.print(digitalRead(sl));
  Serial.print("    M:");
  Serial.print(digitalRead(sm));
  Serial.print("    R:");
  Serial.println(digitalRead(sr));
}
