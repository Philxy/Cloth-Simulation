#pragma once
#include <vector>
#include "pointmass.h"
#include "constraints.h"

class Entity
{
public:
    std::vector<PointMass> particles;
    std::vector<LinkConstraint> links;

    Entity();
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
};
