#include "../include/util.h"

void applyGravity(PointMass &p, const float gravStrength)
{
    const Vec2 gravity(0.0f, gravStrength);
    p.acceleration += gravity;
}

float distance(const PointMass &p1, const PointMass &p2)
{
    return sqrt((p1.position - p2.position) * (p1.position - p2.position) + (p1.position - p2.position) * (p1.position - p2.position));
}

void applyDamping(LinkConstraint &link, float dampintCoef)
{
    PointMass &partA = link.partA;
    PointMass &partB = link.partB;
    double d = distance(partA, partB);
    partA.acceleration = partA.acceleration - (partA.position - partB.position) * (link.strength * (d - link.restingDistance) / d);
    partB.acceleration -= partA.acceleration;
}


bool approaching(const PointMass &p1, const PointMass &p2)
{
    Vec2 r21 = p2.position -  p1.position;
    Vec2 v12 = p1.velocity -  p2.velocity;
    return r21 * v12 > 0;
}

void resolveCollision(PointMass &p1, PointMass &p2)
{
    if (!approaching(p1, p2))
    {
        return;
    }
    double m1 = p1.m;
    double m2 = p2.m;
    double d = distance(p1, p2);
    if (d < .001)
    {
        return;
    }
    d *= d;
    Vec2 r12 = p1.position - p2.position;
    Vec2 v12 = p1.velocity - p2.velocity;
    Vec2 r21 = - r12;
    Vec2 v21 = - v12;
    double temp1 = -(2 * m2 / (m1 + m2) * (v12 * r12)) / d;
    double temp2 = -(2 * m1 / (m1 + m2) * (v21 * r21)) / d;
    p1.velocity = p1.velocity + (p1.position - p2.position) * temp1;
    p2.velocity = p2.velocity + (p2.position - p1.position) * temp2;
}