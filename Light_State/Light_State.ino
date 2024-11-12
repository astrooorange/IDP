

int runningLed =2; //Light to show robot is running
int magneticLed =3; //Light to show waste is magnetic
int notmagneticLed = 4; //Light to show waste is not magnetic
int magneticPin = 10; //Pin to detect magenetic


void setup() {
  pinMode(runningLed, OUTPUT); //Set Pin2 as output  
  pinMode(magneticLed, OUTPUT); //Set Pin3 as output
  pinMode(notmagneticLed, OUTPUT); //Set Pin4 as output
  pinMode(magneticPin, INPUT); // Set Pin10 as input
}

// create a function that turns off several leds 0.0 - like turnoff(runningLed,magneticLed,notmagneticLed) . Ngl this is kinda extra .......
template <typename T>  
void turnoffLed(T firstLedname){
  digitalWrite(firstLedname, HIGH);
}

template <typename T,typename... Args>
void turnoffLed(T firstLedname,Args... args) {
  digitalWrite(firstLedname, HIGH);
  turnoffLed(args...);
}


void loop() {
  
  //while (true){

    int magneticOutput = digitalRead(magneticPin); //to read if the magnetic sensors has an output

    Serial.print(magneticOutput);


    // ALSO need to add a parameter like if the pickup / servo is going then to start detecting magnetic output as if the servo hasnt picked up anything this doesnt need to run (ngl so what)

    if (magneticOutput == HIGH) {
      digitalWrite(notmagneticLed, HIGH); 
      digitalWrite(magneticLed, LOW); // Turn on magnetic waste LED
    } 
    else {
      digitalWrite(magneticLed, HIGH); 
      digitalWrite(notmagneticLed, LOW); // Turn on non-magnetic waste LED
    }
    
    //this makes the runningLed flash :) while the others dont
    digitalWrite(runningLed, LOW); 
    delay(700);
    digitalWrite(runningLed, HIGH); 
    delay(300);

    //Turning off all the led .... trust the fuction will be worth making :)
    //turnoffLed(magneticLed,notmagneticLed,runningLed);
    digitalWrite(runningLed, HIGH); 


  //}
}
