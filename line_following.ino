int sr=4; 
int sr1= 7 ; //sensor right

int sl=5;
int sl1 = 8;  //sensor left

int sm=6;   //sensor middle

int svr=0;
int svr1 = 0;
int svl=0;
int svl1 = 0;
int svm=0;

int vspeed= 255; 
int tspeed = 0;
int spinspeed = 255;

#include <Adafruit_MotorShield.h>
#include <List.hpp>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *mr = AFMS.getMotor(3);
Adafruit_DCMotor *ml = AFMS.getMotor(4);
int i = 0;
List<int> num;
void setup()
{
 pinMode(sr,INPUT);
 pinMode(sl,INPUT);
 pinMode(sm,INPUT);
 pinMode(sl1,INPUT);
 pinMode(sr1,INPUT);
 Serial.begin(9600);           // set up Serial library at 9600 bps
 Serial.println("Adafruit Motorshield v2 - DC Motor test!");
 num.add(0);
 num.add(0);
 num.add(1);
 num.add(2);
 num.add(0);
 num.add(2);
 num.add(2);
 num.add(2);

 // 0, 1（左）, 2（右） 转向
 // 碰到junction就判断是否要转向
 //转到左边的垃圾场

 if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
  Serial.println("Could not find Motor Shield. Check wiring.");
  while (1);
  }
 Serial.println("Motor Shield found.");
 mr->setSpeed(150);
 mr->run(FORWARD);
 mr->run(RELEASE);
 ml->setSpeed(150);
 ml->run(FORWARD);
 ml->run(RELEASE);
}

void loop()
{
 svr=digitalRead(sr);
 svl=digitalRead(sl);
 svm =digitalRead(sm);
 svr1 = digitalRead(sr1);
  Serial.print(svl);
 Serial.print(svm);
 Serial.print(svr);
 Serial.println(svr1);


  // forward
 if ((svr == LOW && svm == HIGH && svl == LOW) || (svr == HIGH && svm == HIGH && svl == HIGH))
 {
  chassis_forward();

 }

 //turn left
 if (svr == LOW && svm == HIGH && svl == HIGH)
 {
  chassis_turn_left();
 }

 // super left
 if (svr == LOW && svm == LOW && svl == HIGH)
 {
   chassis_turn_super_left();
   }

 //turn right
  if (svr == HIGH && svm == HIGH && svl == LOW)
 {
  chassis_turn_right();
 }

 // super right
 if (svr == HIGH && svm == LOW && svl == LOW)
 {
   chassis_turn_super_right();
   }

 //spin right
  if (svr == LOW && svm == LOW && svl == LOW)
 {
  mr->run(BACKWARD);
  mr->setSpeed(spinspeed);
  ml->run(FORWARD);
  ml->setSpeed(spinspeed);
  
 }

 
// turn left 90
  if (svr1 == HIGH or svl1 == HIGH )
 {
  i+=1;
  if (num.get(i) == 1)
   {
    chassis_turn_left90();
  }
   else if (num.get(i) == 2)
   {
    chassis_turn_right90();
  }
  else{
    chassis_forward();
  }
}

 if (svr1 == HIGH and svl1 == HIGH )
 {
  i+=1;
  if (num.get(i) == 1 )
  {
    chassis_turn_left90();
  }
  else if (num.get(i) ==2) 
  {
    chassis_turn_right90();
  }
  else{
    chassis_forward();
  }
}
}

void chassis_forward ()
{
  mr->run(FORWARD);
  mr->setSpeed(vspeed);
  ml->run(FORWARD);
  ml->setSpeed(vspeed);
}

void chassis_backward (){
  ml->setSpeed(150); // Sets inner wheel to a lower speed
  mr->setSpeed(150); // Sets outer wheel to a greater speed

  ml->run(BACKWARD); // starts the wheels to spinnnnn
  mr->run(BACKWARD);
}

void chassis_turn_left (){
  mr->run(FORWARD);
  mr->setSpeed(vspeed);
  ml->run(FORWARD);
  ml->setSpeed(vspeed-25);
}

void chassis_turn_super_left(){
  mr->run(FORWARD);
  mr->setSpeed(vspeed);
  ml->run(FORWARD);
  ml->setSpeed(vspeed-50);
} 

void chassis_turn_right (){
  mr->run(FORWARD);
  mr->setSpeed(vspeed-25);
  ml->run(FORWARD);
  ml->setSpeed(vspeed);
}

void chassis_turn_super_right(){
  mr->run(FORWARD);
  mr->setSpeed(vspeed-50);
  ml->run(FORWARD);
  ml->setSpeed(vspeed);
} 

void chassis_turn_left90(){
  mr->setSpeed(75); // Sets inner wheel to a lower speed
  ml->setSpeed(200); // Sets outer wheel to a greater speed
  mr->run(FORWARD); // starts the wheels to spinnnnn
  ml->run(FORWARD);

  unsigned long startTime=millis(); // Variable to store the start time
  unsigned long runDuration = 3200 ; // time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration){
    }

  ml->run(RELEASE);
  mr->run(RELEASE);
  

}

void chassis_turn_right90(){
  mr->setSpeed(200); // Sets inner wheel to a lower speed
  ml->setSpeed(75); // Sets outer wheel to a greater speed
  mr->run(FORWARD); // starts the wheels to spinnnnn
  ml->run(FORWARD);

  unsigned long startTime=millis(); // Variable to store the start time
  unsigned long runDuration = 3200 ; // time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration){
  }
  ml->run(RELEASE);
  mr->run(RELEASE);
  
}







