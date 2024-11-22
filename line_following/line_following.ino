#include <Adafruit_MotorShield.h>
//#include <List.hpp>

int sr = 4;  // pin for sensor right (of the three in a row)
int sr1 = 7 ; // pin for sensor top right
int sl = 5;    // pin for sensor left (of the three in a row)
int sl1 = 8;  // pin for sensor top left
int sm = 6;   // pin for sensor middle (of the three)
int pe_sensor_pin = 9; // pin for photo electric sensor
int button_pin = 3; // pin for button 

//int magneticSensor = 3; 

int svr = 0;   //default values of sensors
int svr1 = 0;
int svl = 0;
int svl1 = 0;
int svm = 0;
int pe_sensor_value = 0;

int vspeed= 225;  //default values of motor //might want to change this back up if time is a problem and reduce this value if line following is really bad
int tspeed = 0;
int spinspeed = 255;


Adafruit_MotorShield AFMS = Adafruit_MotorShield();     //setting up MotorShield
Adafruit_DCMotor *mr = AFMS.getMotor(3);  // setting up motors M3, M4
Adafruit_DCMotor *ml = AFMS.getMotor(4);

//counters t
int current_Path = 0;
int Turning_counter = 0;
//List<int> Node0to1 {0,0,1,2,0,2,2,2};

int path0[] = {1,2,0,2,99,3}; // once we finish the picking up object code the path should be {5,1,2,0,2,3}
int path1[] = {5,2,2,2,3};
int path2[] = {1,6,1,1,4};
int path3[] = {1,2,2,6,0,2,0,2,3};
int path4[] = {2,1,1,2}; // this just code returning the AGV back to the start box // we need to add some extra code to make it go into that final finish box maybe something like we did at the start to get it back in the boxxx

int* arrayofPaths[] = {path0,path1,path2,path3,path4};

//so you want it to go on arrayofPaths[currentPath][Turning_counter]


void setup()
{
 pinMode(sr,INPUT);         // Setting up each line sensor
 pinMode(sl,INPUT);
 pinMode(sm,INPUT);
 pinMode(sl1,INPUT);
 pinMode(sr1,INPUT);

 pinMode(pe_sensor_pin,INPUT);      //Setting up Photo Electric Sensor
 //pinMode(magneticOutput,INPUT)        //Setting up Magnetic Sensor

 pinMode(button_pin, INPUT);      //Setting up button

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
 /*mr->setSpeed(150); //just testing that the motor shield is connected and that the motor can move
 mr->run(FORWARD);
 mr->run(RELEASE);
 ml->setSpeed(150);
 ml->run(FORWARD);
 ml->run(RELEASE);*/

 while (digitalRead(button_pin) == LOW) // so code only starts once the button is pressed [most likely get rid of this in the final code]
 {}

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
  ml->setSpeed(vspeed-70);
  mr->run(FORWARD);
  ml->run(FORWARD);
} 

void chassis_turn_right (){
  /*for (int i=FORWARD; i>FORWARD-25 ; i-=5){ //slowly decreases speed down so its smoother
    mr->setSpeed(i);
    if (==)
    
    }*/

  ml->setSpeed(vspeed);
  mr->setSpeed(vspeed-25);
  mr->run(FORWARD);
  ml->run(FORWARD);
}

// only problem i find off about this is if it goes from turn right to super turn right the itll reset the speed from like forward-25 back to forward then decrease back down to forward-50 so yeah needs to be solved. I think can have like a variable just to know current speed
// actually the code will always finish the for loop so we could just start from -25

void chassis_turn_super_right(){
  ml->setSpeed(vspeed);
  mr->setSpeed(vspeed-70);
  mr->run(FORWARD);
  ml->run(FORWARD);
} 

void chassis_turn_left90(){
  mr->setSpeed(210); // Sets inner wheel to a lower speed
  ml->setSpeed(20); // Sets outer wheel to a greater speed
  mr->run(FORWARD); // starts the wheels to spinnnnn
  ml->run(FORWARD);

  unsigned long startTime=millis(); // Variable to store the start time
  unsigned long runDuration = 1950 ; // time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration){
    }

  ml->run(RELEASE);
  mr->run(RELEASE);
  

}

void chassis_turn_right90(){
  delay(35);
  mr->setSpeed(30); // Sets inner wheel to a lower speed
  ml->setSpeed(210); // Sets outer wheel to a greater speed
  mr->run(FORWARD); // starts the wheels to spinnnnn
  ml->run(FORWARD);

  unsigned long startTime=millis(); // Variable to store the start time
  unsigned long runDuration = 1920 ; // time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration){
    }

  ml->run(RELEASE);
  mr->run(RELEASE);
}

/*
void dropoff_()


void chassis_dropoff_fromL(){
  //so put like code here on what to do when it reaches junction 8 / bit where it needs to consider drop off of the waste
  
  if (digitalRead(magneticSensor)==HIGH){ // i dont need to pass in svl1 into this function as parameters,right?
    
    chassis_turn_right90()
    delay(10)
    while (svr1==LOW){
      svr1 = digitalRead(sr1);
      chassis_forward()
    }
    chassis_turn_right90()
    dropoff() // this should just go forward drop off item then reverse back to the junction
    chassis_turn_left90()
    while((svl1==LOW) || (svr1 == LOW)){
      chassis_forward()
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    ml->run(RELEASE);
    mr->run(RELEASE);
    

  }
  else if (digitalRead(magneticSensor) == LOW){

    while((svl1==LOW) || (svr1 == LOW)){
      chassis_forward()
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    chassis_turn_right90()
    dropoff() // this should just go forward drop off item then reverse back to the junction
    chassis_turn_right90()

    while((svl1==LOW) || (svr1 == LOW)){
      chassis_forward()
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    chassis_turn_left90()
    while((svl1==LOW) || (svr1 == LOW)){
      chassis_forward()
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    //this below is so it can drive past the junction (as we cant use the sensors as they are already ontop of the junction so it needs to just get past the junction to continue driving onto the next)
    unsigned long startTime=millis(); // Variable to store the start time
    unsigned long runDuration = 1000 ; // time we want the program to run for (in milliseconds)
    while(millis() - startTime < runDuration)
    {
    chassis_forward();
    }

    while((svl1==LOW) || (svr1 == LOW)){
      chassis_forward()
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    ml->run(RELEASE);
    mr->run(RELEASE);

  }

  else  // this code is just to catch any logical errors come up
  {
    ml -> run(RELEASE);
    mr -> run(RELEASE);
    while(true)
    {}
  }


}

void chassis_dropoff_fromR(){

  if (digitalRead(magneticSensor)==HIGH){

    //this below is so it can drive past the junction (as we cant use the sensors as they are already ontop of the junction so it needs to just get past the junction to continue driving onto the next)
      
    unsigned long startTime=millis(); // Variable to store the start time
    unsigned long runDuration = 1000 ; // time we want the program to run for (in milliseconds)
    while(millis() - startTime < runDuration)
    {
      chassis_forward();
    }

    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward()
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    chassis_turn_left90()
    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward()
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    chassis_turn_right90()
    dropoff()~
    chassist_turn_left90()
    while((svl1==LOW) || (svr1 == LOW))
    {
      chassis_forward()
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }
    
  }
  else if (digitalRead(magneticSensor) == LOW)
  {
    chassis_turn_left90()
    dropoff()
    chassis_turn_right90()

    while((svl1==LOW) || (svr1 == LOW)){
      chassis_forward()
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    chassis_turn_left90()
    while((svl1==LOW) || (svr1 == LOW)){
      chassis_forward()
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    //this below is so it can drive past the junction (as we cant use the sensors as they are already ontop of the junction so it needs to just get past the junction to continue driving onto the next)
    unsigned long startTime=millis(); // Variable to store the start time
    unsigned long runDuration = 1000 ; // time we want the program to run for (in milliseconds)
    while(millis() - startTime < runDuration)
    {
    chassis_forward();
    }

    while((svl1==LOW) || (svr1 == LOW)){
      chassis_forward()
      svr1 = digitalRead(sr1);
      svl1 = digitalRead(sl1);
    }

    ml->run(RELEASE);
    mr->run(RELEASE);

  }

  else  // this code is just to catch any logical errors come up
  {
    ml -> run(RELEASE);
    mr -> run(RELEASE);
    while(true)
    {}
  }
    
}
*/


/*bool object_detection(){
  sensorValue = digitalRead(pe_sensor_pin);
  if (sensorValue == HIGH)
  {
    Serial.println("nothing"); //need to add 
    return true;
  }
  if (sensorValue == LOW)
  {
    Serial.println("detected");
    return false;
  }
  delay(50);
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
  if ((svr1 == HIGH) || (svl1 == HIGH) ){

    if (arrayofPaths[current_Path][Turning_counter] == 1){
      if (current_Path == 0 && Turning_counter == 0 ){
        delay(300); // we heuristically found that this works for it to turn and end up alligned nicely on the line at the end of the left turn
      }
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
    //picking up stationary object of known placement    \\ for this picking up of known placement , we know they are both on a junction so if it detects junction -detects object - picks it up- and then reverses a bit so its able to detect the junction again and do the path stuff [simple :)]
    else if (arrayofPaths[current_Path][Turning_counter] == 5){}

    //picking up object with unkown placement       // how would this work logically as there is no junction before hand to detect to do work cos by then it would have bumped into the object so :/ what to do about this :/
    else if (arrayofPaths[current_Path][Turning_counter] == 6)
    */

    else if (arrayofPaths[current_Path][Turning_counter] == 0){

      unsigned long startTime=millis(); // Variable to store the start time
      unsigned long runDuration = 1000 ; // time we want the program to run for (in milliseconds)

      while(millis() - startTime < runDuration)
      {
      chassis_forward();
      }
      
      Turning_counter+=1;
    }

    else{// this code is just to catch any logical errors come up
      //mr->setSpeed(0); 
      //ml->setSpeed(0);
      ml -> run(RELEASE);
      mr -> run(RELEASE);
      while(true){  
      }

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

