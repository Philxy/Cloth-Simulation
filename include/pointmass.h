#pragma once
#include "vec2.h"
#include <iostream>

class PointMass
{
public:
    Vec2 position, velocity, acceleration, positionOld;
    double m = 1;
    bool fixed = false;

    PointMass(Vec2 position, Vec2 velocity, Vec2 acceleration);
    PointMass();
    ~PointMass();
    void firstIntegration(double dt);
    void update(double dt);
};



