#pragma once
#include "pointmass.h"
#include <math.h>
#include "constraints.h"
#include "entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>

double distance( PointMass *p1,  PointMass *p2);
void applyGravity(PointMass &p, const double gravStrength);
void applyAirFriction(PointMass &p, const double frictionCoef);
void applyDamping(LinkConstraint &link);
bool approaching(const PointMass &p1, const PointMass &p2);
void resolveCollision(PointMass &p1, PointMass &p2);

class Entity;
class Cloth;
void drawCloth(sf::RenderWindow &window, Cloth &cloth, const double scaling);
double convertPositionToScreen(const double pos);
