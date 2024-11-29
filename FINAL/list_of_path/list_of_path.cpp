#include <Arduino.h>
#include "list_of_path.h"
#include "Line_Following_Final.h"  // For functions1; chassis_forward(),chassis_turn_left90(),chassis_turn_right90()
#include "Servo_Final.h"           // For functions: pick_up(), drop_off()

//this is the function that intakes a list of path
void execute_list(int list) 
{
  int counter = 0;
  int listSize = sizeof(list);

  while (((svl1 == HIGH) || (svr1 == HIGH)) && counter <= listSize){

    if (list[counter] == 0) 
    { 
      chassis_forward();
    } 
    
    else if (list[counter] == 1) 
    {
      chassis_turn_left90();
    } 
    
    else if (list[counter] == 2) 
    {
      chassis_turn_right90();
    } 
    
    else if (list[counter] == 3) 
    {
      pick_up();
    } 
    
    else if (list[counter] == 4) 
    {
      drop_off();
    } 
      
    else if (list[counter] == 6) 
    {
      object_detection();
    } 
    
    else if (list[counter] == 7) 
    {
      chassis_stop();

    else if (list[counter] == 8) 
    {
      int magneticOutput = digitalRead(magneticPin);
      
      if (magneticOutput = HIGH){
      execute_list(node7_magnetic) ;
      else{
      execute_list(node7_nonmagnetic);
    }
      counter += 1;
  }
  }
}



