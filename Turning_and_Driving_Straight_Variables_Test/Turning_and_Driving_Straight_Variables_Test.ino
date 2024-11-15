#include <Adafruit_MotorShield.h>


Adafruit_MotorShield AFMS = Adafruit_MotorShield(); // Create the motor shield object with the default I2C address

Adafruit_DCMotor *myMotorLeft = AFMS.getMotor(3); // Motor on port M1
Adafruit_DCMotor *myMotorRight = AFMS.getMotor(4); // Another motor on port M2


int buttonPin = 8; //Pin 8 for button


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Driving Striaght and Turning test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  
  pinMode(buttonPin, INPUT); // putting button as input

}

//Reminder - Let vehicle be stationary before using this function, thanks :)
// ALSO NEED to tweak the values so they are all correct like the speed and the tie taken to turn. If we find the speed for a the different values of rotation then we can find the and calculate all the values :), if it doesnt slip we can do this. (We could test this by attaching a marker onto the wheel and just have it stuck and just count rpm?)
void turningLeftCorner(){ 

  myMotorLeft->setSpeed(50); // Sets inner wheel to a lower speed
  myMotorRight->setSpeed(175); // Sets outer wheel to a greater speed
  myMotorLeft->run(FORWARD); // starts the wheels to spinnnnn
  myMotorRight->run(FORWARD);

  unsigned long startTime=millis(); // Variable to store the start time
  unsigned long runDuration = 1000 ; // time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration){
    }

  myMotorLeft->run(RELEASE);
  myMotorRight->run(RELEASE);
}

void turningRightCorner(){ 

  myMotorLeft->setSpeed(255); // Sets inner wheel to a lower speed
  myMotorRight->setSpeed(0); // Sets outer wheel to a greater speed
  myMotorLeft->run(FORWARD); // starts the wheels to spinnnnn
  myMotorRight->run(FORWARD);

  unsigned long startTime=millis(); // Variable to store the start time
  unsigned long runDuration = 1710 ; // time we want the program to run for (in milliseconds)

  while(millis() - startTime < runDuration){
    }

  myMotorLeft->run(RELEASE);
  myMotorRight->run(RELEASE);
}


void loop() {
  uint8_t i;

  while (digitalRead(buttonPin) == LOW) {
  }
  /*
  //while digitalRead(butonPin) == LOW;
    myMotorLeft->run(FORWARD);
    myMotorRight->run(FORWARD);
    myMotorLeft->setSpeed(200);
    myMotorRight->setSpeed(200);
    //for (i=0; i<255; i++) {
    //  myMotorLeft->setSpeed(i);
    //  myMotorRight->setSpeed(i);
      
    //}
  
    delay(2000);

    //myMotorLeft->run(FORWARD); // maybe practice with just releasing instead of slowing down and what the difference is? ->run(RELEASE)
    //myMotorRight->run(FORWARD);
    //for (i=255; i!=0; i--) {
    //  myMotorLeft->setSpeed(i);
    //  myMotorRight->setSpeed(i);
    //}
    delay(10);
    myMotorLeft->run(RELEASE); 
    myMotorRight->run(RELEASE);
    */
    //turningLeftCorner();  //Test the functions to alter/find the variables to get an accurate 90 degrees turn
    turningRightCorner(); 


    //}

// Doesnt matter the like loop up , only keep it for turning /line following . Also just keep general speed like 200. (225 is max but it seems like fast enough)
// Seems like biggest problem will just be weight distribution :)
// Also to stop just do -> run(RELEASE) cos it just works, dont overthink it.
// this turning values/variable change with weight distribution so need to pay attention to that
}