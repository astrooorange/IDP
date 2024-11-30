#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int phs = 12; // photoelectric pin
int phv = 0;  // photoelectric value
int button = 10;
int state = 0;
int val = 0;
int i = 0;
void setup() {
  myservo.attach(11);
  pinMode(phs,INPUT);
  pinMode(button,INPUT);
  Serial.begin(9600); 
  myservo.write(80);
}

void loop() {
  i = 0;
  phv = digitalRead(phs);
  state = digitalRead(button);
  if (phv == LOW)
  {
    Serial.println("pick up");
    grab_object();
  }
  
  if (state == HIGH)
  {
    drop_off();
  }  // back to initial
  
  else
  {
    Serial.println("nothing");
  }
  delay(15);   // waits for the servo to get there
}