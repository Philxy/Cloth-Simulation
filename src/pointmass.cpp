#include "../include/pointmass.h"

PointMass::PointMass(Vec2 position, Vec2 velocity, Vec2 acceleration)
{
    this->position = position;
    this->velocity = velocity;
    this->acceleration = acceleration;
    this->positionOld.x = position.x;
    this->positionOld.y = position.y;
}

PointMass::PointMass() {}
PointMass::~PointMass() {}

void PointMass::update(double dt)
{
    this->position.x += this->velocity.x * dt;
    this->position.y += this->velocity.y * dt;
    this->velocity.x += this->acceleration.x * dt;
    this->velocity.y += this->acceleration.y * dt;
    return;

    Vec2 temp = *(new Vec2(this->position)); // r_n
    this->position = ((this->position * 2.0) - this->positionOld) + (this->acceleration * (dt * dt)); // r_n+1
    this->velocity = (this->position - this->positionOld) * (1.0 / (2.0 * dt));
    //std::cout << this->acceleration.y;
    this->positionOld = *(new Vec2(temp)); // r_n-1 -> r_n
}