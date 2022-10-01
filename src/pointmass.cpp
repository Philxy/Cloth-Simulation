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
    //this->position.x += this->velocity.x * dt;
    //this->position.y += this->velocity.y * dt;
    //this->velocity.x += this->acceleration.x * dt;
    //this->velocity.y += this->acceleration.y * dt;
    //return;
    
    double x_n = this->position.x; // x_n
    double y_n = this->position.y; // y_n

    this->position.x = ((this->position.x * 2.0) - this->positionOld.x) + (this->acceleration.x * (dt * dt)); // r_n+1
    this->position.y = ((this->position.y * 2.0) - this->positionOld.y) + (this->acceleration.y * (dt * dt)); // r_n+1
    this->velocity.x = (this->position.x - this->positionOld.x) * (1.0 / (2.0 * dt));
    this->velocity.y = (this->position.y - this->positionOld.y) * (1.0 / (2.0 * dt));
    this->positionOld.x = x_n; // r_n-1 -> r_n
    this->positionOld.y = y_n; // r_n-1 -> r_n
}

void PointMass::firstIntegration(double dt)
{  
    this->positionOld.x = this->position.x;
    this->positionOld.y = this->position.y;
    this->position.x = this->position.x + this->velocity.x * dt + .5* dt * dt * this->acceleration.x;
    this->position.y = this->position.y + this->velocity.y * dt + .5* dt * dt * this->acceleration.y;
}