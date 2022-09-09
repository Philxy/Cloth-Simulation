#pragma once
#include "pointmass.h"
#include <math.h>
#include "constraints.h"


float distance(const PointMass &p1, const PointMass &p2);
void applyGravity(PointMass &p, const float gravStrength);
void applyAirFriction(PointMass &p, const float frictionCoef);
void applyDamping(LinkConstraint &link, float campingCoeff);
bool approaching(const PointMass &p1, const PointMass &p2);
void resolveCollision(PointMass &p1, PointMass &p2);

