#pragma once

// window
extern const int windowSizeX;
extern const int windowSizeY;

// general simulation parameters
extern const double GRAVITY;
extern const double FRICTION;
extern const double FIRST_TIME_STEP;
extern const double WIND_FORCE;
extern const double WIND_DURATION;
extern const double WIND_FREQUENCY;

// cloth parameters
extern const int CLOTH_WIDTH;
extern const int CLOTH_HEIGHT;
extern const double RESTING_DISTANCE;
extern const double LINK_STRENGTH_FIRST_NEIGHBOR;
extern const double LINK_STRENGTH_SECOND_NEIGHBOR;
extern const double LINK_STRENGTH_THIRD_NEIGHBOR;
extern const double BREAKING_THRESHOLD;