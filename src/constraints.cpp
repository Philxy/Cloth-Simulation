#include "../include/constraints.h"

LinkConstraint::LinkConstraint(PointMass pA, PointMass pB, double restingDistance, double strength)
{
    this->partA = pA;
    this->partB = pB;
    this->restingDistance = restingDistance;
    this->strength = strength;

}

LinkConstraint::LinkConstraint() {}
LinkConstraint::~LinkConstraint() {}