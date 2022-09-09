#include "../include/pointmass.h"

PointMass::PointMass(Vec2 position, Vec2 velocity, Vec2 acceleration)
{
    position = position;
    velocity = velocity;
    acceleration = acceleration;
    positionOld = position;
}

PointMass::PointMass() {}

void PointMass::update(double dt)
{
    Vec2 temp = position;
    position = ((position * 2.0) - positionOld) + (acceleration * (dt * dt * m));
    velocity = (position - positionOld) * (1.0 / (2.0 * dt));
    positionOld = temp;
}