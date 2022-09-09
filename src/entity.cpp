#include "../include/entity.h"

Cloth::Cloth() {}

Cloth::~Cloth() {}

// Initializes all particles as well as the links of first, second and third order
void Cloth::initParticlesAndLinks(bool firstNeighbor, bool secondNeighbor, bool thirdNeighbor)
{

    if (!firstNeighbor)
    {
        return;
    }

    PointMass *grid[this->width][this->height];

    for (int widthIndex = 0; widthIndex < this->width; widthIndex++)
    {
        for (int heightIndex = 0; heightIndex < this->height; heightIndex++)
        {
            PointMass *p = new PointMass();
            p->position = *new Vec2(topLeftX + widthIndex * this->restingDistance, topLeftY + heightIndex * this->restingDistance);
            p->velocity = *new Vec2(0, 0);
            p->acceleration = *new Vec2(0, 0);
            grid[widthIndex][heightIndex] = p;
            this->particles.push_back(*p);
        }
    }

    for (int widthIndex = 0; widthIndex < this->width - 1; widthIndex++)
    {
        for (int heightIndex = 0; heightIndex < this->height - 1; heightIndex++)
        {
            PointMass &currP = *grid[widthIndex][heightIndex];
            PointMass &rightP = *grid[widthIndex + 1][heightIndex];
            PointMass &lowerP = *grid[widthIndex][heightIndex + 1];
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

    for (int widthIndex = 0; widthIndex < this->width - 2; widthIndex += 2)
    {
        for (int heightIndex = 0; heightIndex < this->height - 2; heightIndex += 2)
        {
            PointMass &currP = *grid[widthIndex][heightIndex];
            PointMass &rightP = *grid[widthIndex + 2][heightIndex];
            PointMass &lowerP = *grid[widthIndex][heightIndex + 2];
            LinkConstraint rightLink1 = *new LinkConstraint(currP, rightP, this->restingDistance*2, this->linkStrengthSecondNeighbor);
            LinkConstraint lowerLink1 = *new LinkConstraint(currP, lowerP, this->restingDistance*2, this->linkStrengthSecondNeighbor);
            this->links.push_back(lowerLink1);
            this->links.push_back(rightLink1);
        }
    }

    if (!thirdNeighbor)
    {
        return;
    }

    for (int widthIndex = 0; widthIndex < this->width - 3; widthIndex += 3)
    {
        for (int heightIndex = 0; heightIndex < this->height - 3; heightIndex += 3)
        {
            PointMass &currP = *grid[widthIndex][heightIndex];
            PointMass &rightP = *grid[widthIndex + 3][heightIndex];
            PointMass &lowerP = *grid[widthIndex][heightIndex + 3];
            LinkConstraint rightLink1 = *new LinkConstraint(currP, rightP, this->restingDistance*3, this->linkStrengthThirdNeighbor);
            LinkConstraint lowerLink1 = *new LinkConstraint(currP, lowerP, this->restingDistance*3, this->linkStrengthThirdNeighbor);
            this->links.push_back(lowerLink1);
            this->links.push_back(rightLink1);
        }
    }
}