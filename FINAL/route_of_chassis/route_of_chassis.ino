//NO TURNING 180 DEGREES

//the car begins at node 1 facing north, and ends up at node 7 facing east
int object1 [] = {0,6,1,2,0,2};

//the car begins at node 8 facing south, ends up at node7 facing east
int object3 [] = {1,6,1,1,1};

//the car begins at node 7 facing east, ends up at node 7 facing east 
int object4 [] = {2,0,1,2,2,6,0,2,0,2,2}

//the car begins at node 7 facing east
int home []= {1,1,1,2,0,7}


//the car begins at node 7 facing east, and ends up at node 8 facing south; next one: object2 detection (node8)
int node7_magnetic[] = {2,0,2,5,1,0};
int node7_nonmagnetic[] = {0,2,2,4,2,1,0};

//the car begins at node 8 facing north, and ends up at node 8 facing south
int node8_magnetic[] = {1,4,1,1};
int node8_nonmagnetic[] = {0,2,2,4,2,1,0};

//need an object detection: before the sensor senses the white line, detection is opened. when it detects the object, it stops and pick up. it then move forward until it detects the white line.
