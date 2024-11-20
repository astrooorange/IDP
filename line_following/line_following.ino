#include <Adafruit_MotorShield.h>
//#include <List.hpp>

int sr=4;  // sensor right (of the three in a row)
int sr1= 7 ; //sensor top right
int sl=5;    //sensor left (of the three in a row)
int sl1 = 8;  //sensor top left
int sm=6;   //sensor middle (of the three)

//int magneticSensor = 3; 

int svr=0;   //default values of sensors
int svr1 = 0;
int svl=0;
int svl1 = 0;
int svm=0;

int vspeed= 255;  //default values of motor????
int tspeed = 0;
int spinspeed = 255;


Adafruit_MotorShield AFMS = Adafruit_MotorShield();     //setting up MotorShield
Adafruit_DCMotor *mr = AFMS.getMotor(3);  // setting up motors M3, M4
Adafruit_DCMotor *ml = AFMS.getMotor(4);

//counters t
int current_Path = 0;
int Turning_counter = 0;
//List<int> Node0to1 {0,0,1,2,0,2,2,2};

int path0[] = {1,2,0,2,2,2};
int path1[] = {0,0,0,0,0};

int* arrayofPaths[] = {path0,path1};

//so you want it to go on arrayofPaths[currentPath]


void setup()
{
 pinMode(sr,INPUT);         // Setting up each line sensor
 pinMode(sl,INPUT);
 pinMode(sm,INPUT);
 pinMode(sl1,INPUT);
 pinMode(sr1,INPUT);
 //pinMode(magneticOutput,INPUT)
 Serial.begin(9600);           // set up Serial library at 9600 bps
 //Serial.println("Adafruit Motorshield v2 - DC Motor test!");        //REMOVE?

 // 0, 1（左）, 2（右） 转向
 // 碰到junction就判断是否要转向
 //转到左边的垃圾场

 if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz {REMOVE?}
  Serial.println("Could not find Motor Shield. Check wiring.");
  while (1);
  }
 Serial.println("Motor Shield found.");
 mr->setSpeed(150); //just testing that the motor shield is connected and that the motor can move
 mr->run(FORWARD);
 mr->run(RELEASE);
 ml->setSpeed(150);
 ml->run(FORWARD);
 ml->run(RELEASE);
}

//

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

  mr->setSpeed(vspeed);
  ml->setSpeed(vspeed-25);
  mr->run(FORWARD);
  ml->run(FORWARD);

}

void chassis_turn_super_left(){
  
  mr->setSpeed(vspeed);
  ml->setSpeed(vspeed-50);
  mr->run(FORWARD);
  ml->run(FORWARD);
} 

void chassis_turn_right (){
  /*for (int i=FORWARD; i>FORWARD-25 ; i-=5){ //slowly decreases speed down so its smoother
    mr->setSpeed(i);}*/

  ml->setSpeed(vspeed);
  mr->setSpeed(vspeed-25);
  mr->run(FORWARD);
  ml->run(FORWARD);
}

// only problem i find off about this is if it goes from turn right to super turn right the itll reset the speed from like forward-25 back to forward then decrease back down to forward-50 so yeah needs to be solved. I think can have like a variable just to know current speed
// actually the code will always finish the for loop so we could just start from -25

void chassis_turn_super_right(){
  ml->setSpeed(vspeed);
  mr->setSpeed(vspeed-50);
  mr->run(FORWARD);
  ml->run(FORWARD);
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

/*
void dropoff_()


void chassis_dropoff_fromL(){
  //so put like code here on what to do when it reaches junction 8/ bit where it needs to consider drop off of the waste

  if (digitalRead(magneticSensor)==HIGH){
    
    chassis_turn_right90()
    delay(10)
    chassis_forward()
    while (sl1==LOW){
      svl1 = digitalRead(sl1);
    }
    chassis_turn_right90()
    dropoff() // this should just go forward drop off item then reverse back to the junction
    chassis_turn_left90()
    chassis_forward()
    while(sl1==LOW AND sr1 == LOW){
    }

    ml->run(RELEASE);
    mr->run(RELEASE);
    

  }
  else{

    ....

  }
}

void chassis_dropoff_fromR(){
}
*/

int getout = 0;

void loop()
{

  if (current_Path == 0 && Turning_counter == 0 && getout==0){
    chassis_forward();
    while ((svm == LOW) || (svr == LOW) ||(svl==LOW)){
      svr=digitalRead(sr); 
      svl=digitalRead(sl);
      svm =digitalRead(sm);
    }
    getout+=1;
  }

 svr=digitalRead(sr); // reading all the sensors
 svl=digitalRead(sl);
 svm =digitalRead(sm);
 svr1 = digitalRead(sr1);
 svl1 = digitalRead(sl1);
 Serial.print(svl); // printing the sensor values to help debug
 Serial.print(svm);
 Serial.print(svr);
 Serial.print(svr1);



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

 
// 
  if (svr1 == HIGH or svl1 == HIGH ){

    if (arrayofPaths[current_Path][Turning_counter] == 1){
      chassis_turn_left90();
      Turning_counter+=1;
    }
    else if (arrayofPaths[current_Path][Turning_counter] == 2){
      chassis_turn_right90();
      Turning_counter+=1;
    }

    
    /*
    else if (arrayofPaths[current_Path][Turning_counter] == 3){
      chassis_dropoff_fromL; // this route has to end at the same point as dropoff_fromR() !!!! so everything is the same for both :) (like in terms of reseting the path)
      current_Path+=1; //to go to the next path route
      Turning_counter=0;
    }

    else if (arrayofPaths[current_Path][Turning_counter] == 4){
      chassis_dropoff_fromR();
      current_Path+=1; //to go to the next path route
      Turning_counter=0;
    }
    //picking up stationary object of known placement
    else if (arrayofPaths[current_Path][Turning_counter] == 5){}

    //picking up object with unkown placement
    else if (arrayofPaths[current_Path][Turning_counter] == 6)
    */

    else{
      chassis_forward();
      Turning_counter+=1;
    }

  }

}

// this AND logic (below) is the same as the OR (above) so doesnt seem like there is any reason to run it twice (right?)

/*
 if (svr1 == HIGH and svl1 == HIGH )  
 {
  Turning_counter+=1;
  if (Node0to1.get(Turning_counter) == 1 )
  {
    chassis_turn_left90();
  }
  else if (Node0to1.get(Turning_counter) ==2) 
  {
    chassis_turn_right90();
  }
  else{
    chassis_forward();
  }
  */ 

