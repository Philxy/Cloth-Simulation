#include "../include/constants.h"


// general simulation parameters 
const double GRAVITY = 20;
const double FRICTION = 2;
const double FIRST_TIME_STEP = 0.001;

// cloth parameters
const int CLOTH_WIDTH = 50;
const int CLOTH_HEIGHT = 30;
const double RESTING_DISTANCE = 1;
const double LINK_STRENGTH_FIRST_NEIGHBOR = 1000;
const double LINK_STRENGTH_SECOND_NEIGHBOR = 10;
const double LINK_STRENGTH_THIRD_NEIGHBOR = 0;
const double BREAKING_THRESHOLD = 7;
