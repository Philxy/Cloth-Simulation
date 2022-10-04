#include "../include/entity.h"
#include <iostream>

Cloth::Cloth() {}
Cloth::~Cloth() {}
Entity::Entity() {}
Entity::~Entity() {}

void Entity::update(double dt)
{
    for (PointMass *p : this->particles)
    {
        if (!p->fixed)
        {
            p->update(dt);
        }
    }
}

void Entity::firstIntegration(double dt)
{
    for (PointMass *p : this->particles)
    {
        p->firstIntegration(dt);
    }
}

void Cloth::applyForces( double gravity,  double friction, double windForce)
{
    for (PointMass *p : this->particles)
    {
        p->acceleration.x = 0;
        p->acceleration.y = 0;
        applyGravity(*p, gravity);
        applyAirFriction(*p, friction);
        applyWindForce(*p, windForce);

    }

    for (LinkConstraint *link : this->links)
    {
        if (!link->broken)
        {
            applyDamping(*link);
        }
    }
}

// Initializes all particles as well as the links of first, second and third order
void Cloth::initParticlesAndLinks()
{

    PointMass *grid[width][height];

    for (int widthIndex = 0; widthIndex < this->width; widthIndex++)
    {
        for (int heightIndex = 0; heightIndex < this->height; heightIndex++)
        {
            PointMass *p = new PointMass();
            grid[widthIndex][heightIndex] = p;

            // hold top of the cloth in place
            if (heightIndex == 0)
            {
                p->fixed = true;
            }
            p->position.x = topLeftX + widthIndex * this->restingDistance;
            p->position.y = topLeftY + heightIndex * this->restingDistance;
            p->velocity.x = 0;
            p->velocity.y = 0;
            p->acceleration.x = 0;
            p->acceleration.y = 0;
            this->particles.push_back(p);
        }
    }

    // init 1st order links
    for (int widthIndex = 0; widthIndex < this->width - 1; widthIndex++)
    {
        for (int heightIndex = 0; heightIndex < this->height - 1; heightIndex++)
        {
            // 1st order links
            PointMass *currP = grid[widthIndex][heightIndex];
            PointMass *rightP1 = grid[widthIndex + 1][heightIndex];
            PointMass *lowerP1 = grid[widthIndex][heightIndex + 1];
            LinkConstraint *rightLink1 = new LinkConstraint(currP, rightP1, this->restingDistance, this->linkStrengthFirstNeighbor);
            LinkConstraint *lowerLink1 = new LinkConstraint(currP, lowerP1, this->restingDistance, this->linkStrengthFirstNeighbor);
            lowerLink1->linkOrder = First;
            rightLink1->linkOrder = First;
            this->links.push_back(lowerLink1);
            this->links.push_back(rightLink1);
        }
    }
    // 1st order edges
    for (int heightIndex = 0; heightIndex < this->height - 1; heightIndex++)
    {
        PointMass *currP = grid[this->width - 1][heightIndex];
        PointMass *lowerP1 = grid[this->width - 1][heightIndex + 1];
        LinkConstraint *lowerLink1 = new LinkConstraint(currP, lowerP1, this->restingDistance, this->linkStrengthFirstNeighbor);
        lowerLink1->linkOrder = First;
        this->links.push_back(lowerLink1);
    }
    for (int widthIndex = 0; widthIndex < this->width - 1; widthIndex++)
    {
        PointMass *currP = grid[widthIndex][this->height - 1];
        PointMass *rightP1 = grid[widthIndex + 1][this->height - 1];
        LinkConstraint *lowerLink1 = new LinkConstraint(currP, rightP1, this->restingDistance, this->linkStrengthFirstNeighbor);
        lowerLink1->linkOrder = First;
        this->links.push_back(lowerLink1);
    }

    // 2nd order links
    for (int widthIndex = 0; widthIndex < this->width - 1; widthIndex++)
    {
        for (int heightIndex = 0; heightIndex < this->height - 1; heightIndex++)
        {
            PointMass *currP = grid[widthIndex][heightIndex];
            PointMass *lowerRightP2 = grid[widthIndex + 1][heightIndex + 1];
            LinkConstraint *lowerRightLink2 = new LinkConstraint(currP, lowerRightP2, this->restingDistance * 1.41, this->linkStrengthSecondNeighbor);
            lowerRightLink2->linkOrder = Second;
            this->links.push_back(lowerRightLink2);
        }
    }
    for (int widthIndex = 0; widthIndex < this->width - 1; widthIndex++)
    {
        for (int heightIndex = this->height - 1; heightIndex > 0; heightIndex--)
        {
            PointMass *currP = grid[widthIndex][heightIndex];
            PointMass *upperRightP2 = grid[widthIndex + 1][heightIndex - 1];
            LinkConstraint *upperRightLink2 = new LinkConstraint(currP, upperRightP2, this->restingDistance * 1.41, this->linkStrengthSecondNeighbor);
            upperRightLink2->linkOrder = Second;
            this->links.push_back(upperRightLink2);
        }
    }
}

// Initializes a map storing the point masses as keys and their links as data
void Entity::initLinksForEachPointMass()
{
    for (LinkConstraint *link : links)
    {
        (this->linksForEachPointMass[link->partA_ptr]).push_back(link);
        (this->linksForEachPointMass[link->partB_ptr]).push_back(link);
    }
}