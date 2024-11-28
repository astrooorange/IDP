//this is the function that intakes a list of path
void executeList(int list) {
  int counter = 0;
  int listSize = sizeof(list);

  while (counter < listSize) { 

    if (list[counter] == 0) { 
      chassis_forward();
    } 
    
    else if (list[counter] == 1) {
      chassis_turn_left90();
    } 
    
    else if (list[counter] == 2) {
      chassis_turn_right90();
    } 
    
    else if (list[counter] == 3) {
      pick_up();
    } 
    
    else if (list[counter] == 4) {
      drop_off();
    } 
    
    else if (list[counter] == 5) {
      unsigned long startTime = millis();
      unsigned long runDuration = 1000; 
      while (millis() - startTime < runDuration) {
        chassis_forward();
      }
    } 
    
    else if (list[counter] == 6) {
      object_detection();
    } 
    
    else if (list[counter] == 7) {
      chassis_stop();
    }
    counter += 1; // 修正增量语法
  }
}
