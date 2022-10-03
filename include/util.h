#pragma once
#include "pointmass.h"
#include <math.h>
#include "constraints.h"
#include "entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"

double distance( PointMass *p1,  PointMass *p2);
double distance( const Vec2 &v1, const Vec2 &v2);
void applyGravity(PointMass &p, const double gravStrength);
void applyAirFriction(PointMass &p, const double frictionCoef);
void applyDamping(LinkConstraint &link);
bool approaching(const PointMass &p1, const PointMass &p2);
void resolveCollision(PointMass &p1, PointMass &p2);

class Entity;
class Cloth;
void drawCloth(sf::RenderWindow &window, Cloth &cloth, const double scaling);
double distanceOfPointToLine(Vec2 lineStart, Vec2 lineEnd, Vec2 point);
void breakClosestLink(Entity &entity, const Vec2 &point);
PointMass* closestParticleToPoint(const Entity &entity, const Vec2 &point);