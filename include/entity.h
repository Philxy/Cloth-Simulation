#pragma once
#include <vector>
#include "pointmass.h"
#include "constraints.h"
#include "util.h"
#include <map>


class Entity
{
public:
    std::vector<PointMass *> particles;
    std::vector<LinkConstraint *> links;
    std::map<PointMass *, std::vector<LinkConstraint *>> linksForEachPointMass;

    Entity();
    ~Entity();

    void update(double dt);
    void firstIntegration(double dt);
    void initLinksForEachPointMass();
};

class Cloth : public Entity
{
public:
    int width, height;

    double topLeftX, topLeftY;
    double restingDistance;
    double linkStrengthFirstNeighbor;
    double linkStrengthSecondNeighbor;
    double linkStrengthThirdNeighbor;

    Cloth();
    ~Cloth();

    void initParticlesAndLinks();
    void applyForces( double gravity,  double friction, double windForce);
};
