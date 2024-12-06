#include <Servo.h>
#include "Line_Following_Final.h"
#include "Route_of_Chassis_Final.h"
#include "Servo_Final.h"
#include "List_of_Path_Final.h"
#include "Light_State_Final.h"
#include <Adafruit_MotorShield.h>

//#include <TimerOne.h>
#include <avr/interrupt.h>      // For interrupts for light


Servo myservo;  // Create servo object to control a servo

// Defining Pins
int running_led = 2;      // Pin for the flashing blue light        
int magnetic_led = 3;     // Pin for the red light to show that a magnetic object was picked up         
int not_magnetic_led = 4;     // Pin for the green light that activates when a non magnetic object is picked up 
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

int forward_speedL = 220;     // Default values of motor //might want to change this back up if time to complete the path is a problem and reduce this value if line following is really bad
int forward_speedR = 211;
int backward_speed = 160;

int timer_counter=0;

void setup()
{ 
  pinMode(running_led,OUTPUT);      // Just setting up all the pins
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
  
  
  Serial.begin(9600);     // Set up Serial library at 9600 bps



  if (!AFMS.begin())      // Setting up Motor Shield
  {         
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  myservo.write(80);      // Adjust the intial position of the Servo to be at this amount

  while (digitalRead(button_pin) == LOW) // Code only starts once the button is pressed
  {}
     

  
  TCCR2A = 0;     // Timer2 configuration                     
  TCCR2B = 0;                     
  TCNT2 = 0;                      
  OCR2A = 124;          
  TCCR2A |= (1 << WGM21);         
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); 
  TIMSK2 |= (1 << OCIE2A);        
  sei(); 


}


ISR(TIMER2_COMPA_vect)      // To toggle_led() function to run for every interrupt
 {
    timer_counter += 1;

    if (timer_counter > 30)     // Just after some interrupt happen as so that light flashes with 2Hz
    {
      toggle_led();     // Call the function from Light_State_Final.cpp
      timer_counter = 0;
    }
  }


void loop() {
   

  bool pick_up_two_objects = true;
  bool pick_up_four_objects = false;

  unsigned long startTime=millis();     // Variable to store the start time
  unsigned long runDuration = 2000 ;      // Time we want the program to run for (in milliseconds)
  while((millis() - startTime < runDuration))     // This is some back up code so we can choose what path the robot take by how many times the button is pressed
  {
    if (digitalRead(button_pin) == LOW)
    {
      pick_up_four_objects = true;
      pick_up_two_objects = false;
    }

    if (digitalRead(button_pin) == HIGH)
    {
      pick_up_four_objects = false;
      pick_up_two_objects = true;
      break;
    }
  }

  get_me_out_of_the_starting_box();

  if (pick_up_four_objects == true)
  {
    execute_list(object1,6);
    execute_list(object2,5);
    execute_list(object3,7);
    execute_list(object4,9);

  }

  else if (pick_up_two_objects == true)
  {
    execute_list(object1,6);
    execute_list(object2,5);
  }

  else
  {
    delay(1000000);
  }

  execute_list(home,4);
  
  get_me_into_the_starting_box();
}
