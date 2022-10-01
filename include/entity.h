#pragma once
#include <vector>
#include "pointmass.h"
#include "constraints.h"
#include "util.h"


class Entity
{
public:
    std::vector<PointMass*> particles;
    std::vector<LinkConstraint*> links;

    Entity();
    ~Entity();

    void update(double dt);
    void firstIntegration(double dt);
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

    void initParticlesAndLinks(bool firstNeighbor, bool secondNeighbor, bool thirdNeighbor);
    void applyForces(const double gravity, const double friction);
};

