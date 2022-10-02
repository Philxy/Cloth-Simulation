#include "../include/util.h"

void applyGravity(PointMass &p, const double gravStrength)
{
    p.acceleration.y += gravStrength;
}

double distance(PointMass *p1, PointMass *p2)
{
    return sqrt((p1->position.x - p2->position.x) * (p1->position.x - p2->position.x) + (p1->position.y - p2->position.y) * (p1->position.y - p2->position.y));
}

double distance(const Vec2 &vecA, const Vec2 &vecB)
{
    return sqrt((vecA.x - vecB.x) * (vecA.x - vecB.x) + (vecA.y - vecB.y) * (vecA.y - vecB.y));
}

void applyDamping(LinkConstraint &link)
{
    PointMass *partA = (link.partA_ptr);
    PointMass *partB = (link.partB_ptr);
    double d = distance(partA, partB);
    
    
    if ( link.restingDistance * 10 < d)
    {
        link.broken = true;
        return;
    }
    

    partA->acceleration.x -= (partA->position.x - partB->position.x) * (link.strength * (d - link.restingDistance) / d);
    partA->acceleration.y -= (partA->position.y - partB->position.y) * (link.strength * (d - link.restingDistance) / d);
    partB->acceleration.x -= (partB->position.x - partA->position.x) * (link.strength * (d - link.restingDistance) / d);
    partB->acceleration.y -= (partB->position.y - partA->position.y) * (link.strength * (d - link.restingDistance) / d);
}

bool approaching(const PointMass &p1, const PointMass &p2)
{
    Vec2 r21 = p2.position - p1.position;
    Vec2 v12 = p1.velocity - p2.velocity;
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
    double d = distance(&p1, &p2);
    if (d < .001)
    {
        return;
    }
    d *= d;
    Vec2 r12 = p1.position - p2.position;
    Vec2 v12 = p1.velocity - p2.velocity;
    Vec2 r21 = -r12;
    Vec2 v21 = -v12;
    double temp1 = -(2 * m2 / (m1 + m2) * (v12 * r12)) / d;
    double temp2 = -(2 * m1 / (m1 + m2) * (v21 * r21)) / d;
    p1.velocity = p1.velocity + (p1.position - p2.position) * temp1;
    p2.velocity = p2.velocity + (p2.position - p1.position) * temp2;
}

void applyAirFriction(PointMass &p, const double friction)
{
    p.acceleration.x -= p.velocity.x * friction;
    p.acceleration.y -= p.velocity.y * friction;
}

double distanceOfPointToLine(Vec2 lineStart, Vec2 lineEnd, Vec2 point)
{
    return abs((lineEnd.x - lineStart.x) * (lineStart.y - point.y) - (lineStart.x - point.x) * (lineEnd.y - lineStart.y)) / distance(lineEnd, lineStart);
}

PointMass *closestParticleToPoint(const Entity &entity, const Vec2 &point)
{
    // find closest point to mouse pointer
    double currMinDistance = 999999;
    PointMass *currClosestPoint = nullptr;
    for (PointMass *p : entity.particles)
    {
        double currDistance = distance(p->position, point);
        if (currDistance < currMinDistance)
        {
            currMinDistance = currDistance;
            currClosestPoint = p;
        }
    }
    return currClosestPoint;
}

void breakClosestLink(Entity &entity, const Vec2 &point)
{

    PointMass *closestPart = closestParticleToPoint(entity, point);
    LinkConstraint *currClosestLink = nullptr;
    double currMinLinkDistance = 9999999;

    for (LinkConstraint *link : entity.linksForEachPointMass[closestPart])
    {
    
        
        double currLinkDistance = distanceOfPointToLine(link->partA_ptr->position, link->partB_ptr->position, point);
        if (currMinLinkDistance > currLinkDistance)
        {
            currMinLinkDistance = currLinkDistance;
            currClosestLink = link;
        }
    }
    if (currClosestLink != nullptr)
    {
        currClosestLink->broken = true;
    }
}

void drawCloth(sf::RenderWindow &window, Cloth &cloth, const double scaling)
{
    /*
    for (PointMass *p : cloth.particles)
    {
        sf::CircleShape circle;
        circle.setFillColor(sf::Color::White);
        circle.setRadius(.1 * scaling);
        circle.setPosition(p->position.x * scaling, p->position.y * scaling);
        window.draw(circle);
    }
    */

    for (LinkConstraint *link : cloth.links)
    {

        if (link->broken)
        {
            continue;
        }
        
        PointMass *p1 = link->partA_ptr;
        PointMass *p2 = link->partB_ptr;
        sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(p1->position.x * scaling, p1->position.y * scaling)),
                sf::Vertex(sf::Vector2f(p2->position.x * scaling, p2->position.y * scaling))};
        line[0].color = (sf::Color(255, 255, 255));
        line[1].color = (sf::Color(255, 255, 255));

        window.draw(line, 2, sf::Lines);
    }
}