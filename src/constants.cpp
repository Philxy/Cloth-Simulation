#include "../include/constants.h"

// window
const int windowSizeX = 2560;
const int windowSizeY = 1440;

// general simulation parameters
const double GRAVITY = 1000;
const double FRICTION = 3;
const double FIRST_TIME_STEP = 0.001;
const double WIND_FORCE = 150;
const double WIND_FREQUENCY = 3;
const double WIND_DURATION = 1;

// cloth parameters
const int CLOTH_WIDTH = 150;
const int CLOTH_HEIGHT = 70;
const double RESTING_DISTANCE = 1;
const double LINK_STRENGTH_FIRST_NEIGHBOR = 200000;
const double LINK_STRENGTH_SECOND_NEIGHBOR = 100;
const double LINK_STRENGTH_THIRD_NEIGHBOR = 0;
const double BREAKING_THRESHOLD = 4;
