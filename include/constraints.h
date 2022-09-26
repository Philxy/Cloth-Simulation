#pragma once
#include "pointmass.h"

class LinkConstraint
{
public:
    PointMass *partA_ptr, *partB_ptr;
    double strength;
    double restingDistance;
    bool broken = false;
    LinkConstraint(PointMass *pA, PointMass *pB, double restingDistance, double strength);
    ~LinkConstraint();
};