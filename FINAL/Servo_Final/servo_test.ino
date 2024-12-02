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
    while (i<3) // repeat collection for 5 times
    {
      while(val < 80)
      {
        val += 1;
        myservo.write(val);
        delay(15);
        Serial.println(val);
      }
      delay(800);  
      while (val > 65)
      {
        val -= 1;
        myservo.write(val);
        delay(15);
        Serial.println(val);
      }
      
      delay(800);
      //Serial.println(i);
      i += 1;
    }
  }

  if (state == HIGH)
  {
    while (val < 105)
    {
      val += 1;
      myservo.write(val);
      delay(15);
      Serial.println(val);
    }
    delay(700); // pushout
    while (val > 80)
    {
      val -= 1;
      myservo.write(val);
      delay(15);
      Serial.println(val);
    }

  }  // back to initial
  
  else
  {
    Serial.println("nothing");
  }
  delay(15);   // waits for the servo to get there
}