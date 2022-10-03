#include "../include/constants.h"


// general simulation parameters 
const double GRAVITY = 500;
const double FRICTION = 10;
const double FIRST_TIME_STEP = 0.001;

// cloth parameters
const int CLOTH_WIDTH = 100;
const int CLOTH_HEIGHT = 50;
const double RESTING_DISTANCE = 1;
const double LINK_STRENGTH_FIRST_NEIGHBOR = 20000;
const double LINK_STRENGTH_SECOND_NEIGHBOR = 100;
const double LINK_STRENGTH_THIRD_NEIGHBOR = 0;
const double BREAKING_THRESHOLD = 10;
