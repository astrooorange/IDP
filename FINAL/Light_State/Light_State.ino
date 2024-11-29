#include <TimerOne.h>     // To use internal timer

int running_led =2; //Light to show robot is running (blue)
int magnetic_led =3; //Light to show waste is magnetic (Red)
int not_magnetic_led = 4; //Light to show waste is not magnetic (Green)
int magneticPin = 13; //Pin to detect magenetic


void setup() {
  pinMode(running_led, OUTPUT); //Set Pin2 as output  
  pinMode(magnetic_led, OUTPUT); //Set Pin3 as output
  pinMode(not_magnetic_led, OUTPUT); //Set Pin4 as output
  pinMode(magneticPin, INPUT); // Set Pin13 as input

  // Interrupts stuff
  Timer1.initialize(500000); // Set timer to overflow every 0.5 seconds
  Timer1.attachInterrupt(toggle_led);  // Attach the interrupt function to Timer1
}
/*
void running_LED() { // this makes the LED flash on and off with a period of 700ms

    digitalWrite(running_led, LOW); 
    delay(700);
    digitalWrite(running_led, HIGH); 
    delay(700);
}*/

//this will be integrated into servo code
void magnetic_sensing(){

 int magneticOutput = digitalRead(magneticPin); //to read if the magnetic sensors has an output

  //Serial.print(magneticOutput);

  // ALSO need to add a parameter like if the pickup / servo is going then to start detecting magnetic output as if the servo hasnt picked up anything this doesnt need to run (ngl so what)

  if (magneticOutput == HIGH) 
  {
    digitalWrite(not_magnetic_led, HIGH); 
    digitalWrite(magnetic_led, LOW); // Turn on magnetic waste LED
  } 
  else 
  {
    digitalWrite(magnetic_led, HIGH); 
    digitalWrite(not_magnetic_led, LOW); // Turn on non-magnetic waste LED
  }
}

void toggle_led(){
  // i think put an if statement and check what value the motors are spinning at (if thats possible to then only change the led state when that happens)
  digitalWrite(running_led, !digitalRead(running_led));
  magnetic_sensing();
  Serial.print("Im am being toggled!!!");     // Debugging
}

void loop()
{
  delay(1000000000000);
  }


/*


*/
