#include "Route_of_Chassis_Final.h"

// Arrays for storing paths that pick up the object and end at the same spot
int object1[] = {6, 1, 2, 0, 2, 8};
int object2[] = {6, 2, 2, 2, 8};
int object3[] = {1, 6, 1, 1, 0, 10, 8};
int object4[] = {1, 2, 2, 6, 0, 2, 0, 2, 8};
int home[] = {2,1,1,2};         // Gets back just before the starting area


// Arrays for the drop off section (magnetic and non-magnetic detections)
int node7_magnetic[] = {2, 4, 1};
int node7_nonmagnetic[] = {0, 4, 2, 1, 0};

