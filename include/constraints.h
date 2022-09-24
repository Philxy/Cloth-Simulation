#pragma once
#include "pointmass.h"

class LinkConstraint
{
public:
    PointMass partA, partB;
    double strength;
    double restingDistance;
    bool broken = false;
    LinkConstraint(PointMass pA, PointMass pB, double restingDistance, double strength);
    LinkConstraint();
    ~LinkConstraint();
};