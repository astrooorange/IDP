//this is the function that intakes a list of path
void execute_list(int list) 
{
  int counter = 0;
  int listSize = sizeof(list);

  while (counter < listSize)
  { 

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
    
    else if (list[counter] == 5) 
    {
      unsigned long startTime = millis();
      unsigned long runDuration = 1000; 
      while (millis() - startTime < runDuration) 
      {
        chassis_forward();
      }
    } 
    
    else if (list[counter] == 6) 
    {
      object_detection();
      //Is this the object detection you want?
      /*
      {
      forward_speedL = forward_speedL - 80;    // Slows down so it doesnt miss/ hit the waste or something (COULD REMOVE THIS LINE ALSO HOPEFULLY IT WORKS LIKE THIS)
      forward_speedR = forward_speedR - 80;

      while((svl1==LOW) || (svr1 == LOW))
      {
        chassis_forward();
        if (object_detection()== true)      // If the object is detected
        {
          ml -> run(RELEASE);
          mr -> run(RELEASE);

          grab_object();

          ml -> run(forward);
          mr -> run(forward);

          forward_speedL = forward_speedL + 80;
          forward_speedR = forward_speedR + 80;

        }

      }

      forward_speedL = forward_speedL + 80;     //Just in case it doesnt detect anything to put the speed back to normal
      forward_speedR = forward_speedR + 80;   

      turning_counter+=1;
      */
    } 
    
    else if (list[counter] == 7) 
    {
      chassis_stop();
    }
    counter += 1; // 修正增量语法
  }
}

// is this a useful function?
void get_me_out_of_the_starting_box()
{
  chassis_forward();

    while ((svm == LOW) || (svr == LOW) ||(svl==LOW))
    {
      svr=digitalRead(sr); 
      svl=digitalRead(sl);
      svm =digitalRead(sm);
    }
}
