#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int phs = 10; // photoelectric pin
int phv = 0;  // photoelectric value
int i = 0;
void setup() {
  myservo.attach(9);
  pinMode(INPUT,phs);
  Serial.begin(9600); 
  myservo.write(80);
}

void loop() {
  i = 0;
  phv = digitalRead(phs);
  if (phv == LOW){
  Serial.println("pick up");
  while (i<6) // repeat collection for 5 times
  {
  myservo.write(80);
  delay(800);         // the angles are not corrrect
  myservo.write(20);
  delay(800);
  Serial.println(i);
  i += 1;
  }
  delay(1000);  //pick up for 1s
  myservo.write(-20); // pushout
  myservo.write(80);  // back to initial
  }
  else
  {
    Serial.println("nothing");
  }
  delay(15);   // waits for the servo to get there
}