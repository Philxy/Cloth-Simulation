#include "../include/constraints.h"

LinkConstraint::LinkConstraint(PointMass *pA, PointMass *pB, double restingDistance, double strength)
{
    partA_ptr = pA;
    partB_ptr = pB;
    this->restingDistance = restingDistance;
    this->strength = strength;
}

LinkConstraint::~LinkConstraint() {}