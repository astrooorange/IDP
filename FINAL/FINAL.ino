#include "Line_Following_Final.h"
#include "Route_of_Chassis_Final.h"
#include "Servo_Final.h"
#include "List_of_Path_Final.h"
#include "Light_State_Final.h"
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include <TimerOne.h>

Servo myservo;  // Create servo object to control a servo

int running_led = 2;      // Defining Pins       
int magnetic_led = 3;         
int not_magnetic_led = 4; 
int sl1 = 5;  // Pin for  top left sensor
int sl = 6;    // Pin for left sensor  (of the three in a row)
int sm = 7;   // Pin for middle sensor  (of the three)
int sr = 8;  // Pin for right sensor  (of the three in a row)
int sr1 = 9 ; // Pin for  top right sensor
int button_pin = 10; // Pin for Button 

int pe_sensor_pin = 12; // Pin for Photoelectric sensor
int magnetic_sensor_pin = 13;     // Pin for Magnetic sensor



int svr = 0;   // Default values of sensors
int svr1 = 0;
int svl = 0;
int svl1 = 0;
int svm = 0;
int pe_sensor_value = 0;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();     // Setting up MotorShield
Adafruit_DCMotor *mr = AFMS.getMotor(3);      // Setting up motors M3, M4
Adafruit_DCMotor *ml = AFMS.getMotor(4);

int forward_speedL = 220;  // Default values of motor //might want to change this back up if time to complete the path is a problem and reduce this value if line following is really bad
int forward_speedR = 215;
int backward_speed = 150;



void setup()
{ 
  pinMode(running_led,OUTPUT);     // Forgot to intialise the lights 0.0
  pinMode(magnetic_led,OUTPUT);
  pinMode(not_magnetic_led,OUTPUT);
  pinMode(sl1,INPUT);
  pinMode(sl,INPUT);
  pinMode(sm,INPUT);
  pinMode(sr,INPUT);         // Setting up each line sensor
  pinMode(sr1,INPUT);
  pinMode(button_pin, INPUT);      //Setting up Button
  myservo.attach(11);         // Setting up Pin for the Servo
  pinMode(pe_sensor_pin,INPUT);      //Setting up PhotoElectric Sensor
  pinMode(magnetic_sensor_pin,INPUT);        //Setting up Magnetic Sensor
  
  
  Serial.begin(9600);           // Set up Serial library at 9600 bps



  if (!AFMS.begin()) // Setting up Motor Shield
  {         
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");



  while (digitalRead(button_pin) == LOW) // Code only starts once the button is pressed
  {}

  myservo.write(80);      // Adjust the intial position of the Servo to be at this amount

  // Interrupts stuff for the flashing light
  Timer1.initialize(500000); // Set timer to overflow every 0.5 seconds
  Timer1.attachInterrupt(toggle_led);  // Attach the interrupt function to Timer1

}

void loop() {
   get_me_out_of_the_starting_box();
   execute_list(object1,6);
   execute_list(object2,5);
   execute_list(object3,7);
   execute_list(object4,9);
   execute_list(home,4);
   get_me_into_the_starting_box();
}
