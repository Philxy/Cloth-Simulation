#pragma once
#include "pointmass.h"

enum LinkOrder {First, Second, Third};

class LinkConstraint
{
public:
    PointMass *partA_ptr, *partB_ptr;
    double strength;
    double restingDistance;
    bool broken = false;
    LinkOrder linkOrder;
    LinkConstraint(PointMass *pA, PointMass *pB, double restingDistance, double strength);
    ~LinkConstraint();
};