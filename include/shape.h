#pragma once
#include "pointmass.h"

class Shape
{
public:
    PointMass point;
    
};

class Circle : public Shape
{
public:
    double radius;
};

class Rectangle : public Shape
{
public:
    double width, height;
    double angle;
};