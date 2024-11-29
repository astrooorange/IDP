//set up the photoeletric sensor
int pe = 12;
void setup(){
  pinMode(pe, OUTPUT); 
}

//function of object detection: when it reaches the line where the object lies on, object_detection is triggered. 
object_detection();
{
  //while the chassis is on the line
  while((svl1==LOW) || (svr1 == LOW))
  {
    // if the object is detected
    if (digitalRead(pe) == true){  
      unsigned long startTime=millis();     
      unsigned long runDuration = 1000 ;    

    //reduce speed of the chassis and make it move for a certain amount of time and then stop -- need to change runDuration and speed after object detected
      while(millis() - startTime < runDuration){
        forward_speedL = forward_speedL - 80;   
        forward_speedR = forward_speedR - 80;
        ml -> run(FORWARD);
        mr -> run(FORWARD);
        ml -> run(RELEASE);
        mr -> run(RELEASE);
      }
    }
    
  //if no object is detected, it moves forward with the same speed  
    else{
      chassis_forward();
    }
  }
}
