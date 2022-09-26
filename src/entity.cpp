#include "../include/entity.h"
#include <iostream>

Cloth::Cloth() {}
Cloth::~Cloth() {}
Entity::Entity() {}
Entity::~Entity() {}

void Entity::update(double dt)
{
    for (PointMass &p : this->particles)
    {
        if (!p.fixed)
        {
            p.update(dt);
        }
    }
}

void Cloth::applyForces(const double gravity, const double friction)
{
    for (PointMass &p : this->particles)
    {
        p.acceleration.x = 0;
        p.acceleration.y = 0;
        applyGravity(p, gravity);
        applyAirFriction(p, friction);
    }

    for (LinkConstraint &link : this->links)
    {
        std::cout << (*link.partA_ptr).velocity.y << std::endl;
        applyDamping(link);
    }
}

// Initializes all particles as well as the links of first, second and third order
void Cloth::initParticlesAndLinks(bool firstNeighbor, bool secondNeighbor, bool thirdNeighbor)
{

    if (!firstNeighbor)
    {
        return;
    }

    std::vector<std::vector<PointMass>> grid_vec(this->width, std::vector<PointMass>(this->height));

    for (int widthIndex = 0; widthIndex < this->width; widthIndex++)
    {
        for (int heightIndex = 0; heightIndex < this->height; heightIndex++)
        {

            PointMass &p = grid_vec.at(heightIndex).at(widthIndex);

            // hold top of the cloth in place
            if (heightIndex == 0)
            {
                p.fixed = true;
            }
            p.position.x = topLeftX + widthIndex * this->restingDistance;
            p.position.y = topLeftY + heightIndex * this->restingDistance;
            p.velocity.x = 0;
            p.velocity.y = 0;
            p.acceleration.x = 0;
            p.acceleration.y = 0;
            this->particles.push_back(p);
        }
    }

    // init 1st order links
    for (int widthIndex = 0; widthIndex < this->width - 1; widthIndex++)
    {
        for (int heightIndex = 0; heightIndex < this->height - 1; heightIndex++)
        {
            PointMass *currP = &grid_vec.at(heightIndex).at(widthIndex);
            PointMass *rightP = &grid_vec.at(heightIndex).at(widthIndex + 1);
            PointMass *lowerP = &grid_vec.at(heightIndex + 1).at(widthIndex);
            LinkConstraint rightLink1 = *new LinkConstraint(currP, rightP, this->restingDistance, this->linkStrengthFirstNeighbor);
            LinkConstraint lowerLink1 = *new LinkConstraint(currP, lowerP, this->restingDistance, this->linkStrengthFirstNeighbor);
            this->links.push_back(lowerLink1);
            this->links.push_back(rightLink1);
        }
    }

    if (!secondNeighbor)
    {
        return;
    }

    /*
    // init 2nd order links
    for (int widthIndex = 0; widthIndex < this->width - 2; widthIndex += 2)
    {
        for (int heightIndex = 0; heightIndex < this->height - 2; heightIndex += 2)
        {
            PointMass &currP = grid_vec.at(heightIndex).at(widthIndex);
            PointMass &rightP = grid_vec.at(heightIndex).at(widthIndex + 2);
            PointMass &lowerP = grid_vec.at(heightIndex + 2).at(widthIndex);
            LinkConstraint rightLink1 = *new LinkConstraint(currP, rightP, this->restingDistance * 2, this->linkStrengthSecondNeighbor);
            LinkConstraint lowerLink1 = *new LinkConstraint(currP, lowerP, this->restingDistance * 2, this->linkStrengthSecondNeighbor);
            this->links.push_back(lowerLink1);
            this->links.push_back(rightLink1);
        }
    }

    if (!thirdNeighbor)
    {
        return;
    }

    // init 3rd order links
    for (int widthIndex = 0; widthIndex < this->width - 3; widthIndex += 3)
    {
        for (int heightIndex = 0; heightIndex < this->height - 3; heightIndex += 3)
        {
            PointMass &currP = grid_vec.at(heightIndex).at(widthIndex);
            PointMass &rightP = grid_vec.at(heightIndex).at(widthIndex + 3);
            PointMass &lowerP = grid_vec.at(heightIndex + 3).at(widthIndex);
            LinkConstraint rightLink1 = *new LinkConstraint(currP, rightP, this->restingDistance * 3, this->linkStrengthThirdNeighbor);
            LinkConstraint lowerLink1 = *new LinkConstraint(currP, lowerP, this->restingDistance * 3, this->linkStrengthThirdNeighbor);
            this->links.push_back(lowerLink1);
            this->links.push_back(rightLink1);
        }
    }
    */
}