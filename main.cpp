#include "include/util.h"
#include <SFML/Graphics.hpp>
#include "include/entity.h"
#include <algorithm>
#include "include/constants.h"

int main()
{
    // init cloth
    Cloth cloth;
    cloth.width = CLOTH_WIDTH;
    cloth.height = CLOTH_HEIGHT;
    cloth.restingDistance = RESTING_DISTANCE;
    const double scaling = 0.7 * std::min(((double)windowSizeX) / cloth.width, ((double)windowSizeY) / cloth.height);
    cloth.topLeftX = (1 - cloth.width * scaling / (double)windowSizeX) / 2.0 * windowSizeX / (double)scaling;
    cloth.topLeftY = 0;
    cloth.linkStrengthFirstNeighbor = LINK_STRENGTH_FIRST_NEIGHBOR;
    cloth.linkStrengthSecondNeighbor = LINK_STRENGTH_SECOND_NEIGHBOR;
    cloth.linkStrengthThirdNeighbor = LINK_STRENGTH_THIRD_NEIGHBOR;
    cloth.initParticlesAndLinks();
    cloth.initLinksForEachPointMass();
    cloth.applyForces(GRAVITY, FRICTION, WIND_FORCE);
    cloth.firstIntegration(FIRST_TIME_STEP);

    double dt;

    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "SFML window");
    sf::Clock clock;

    sf::Clock simulationTimer;
    simulationTimer.restart();

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        dt = elapsed.asSeconds();
        std::cout << "FPS: " << 1 / dt << std::endl;

        dt = FIRST_TIME_STEP;

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                while (event.type != sf::Event::MouseButtonReleased)
                {
                    window.pollEvent(event);
                    int mouseX = sf::Mouse::getPosition(window).x;
                    int mouseY = sf::Mouse::getPosition(window).y;
                    breakClosestLink(cloth, Vec2{(double)mouseX / (double)scaling, (double)mouseY / (double)scaling});
                    cloth.applyForces(GRAVITY, FRICTION, WIND_FORCE);
                    cloth.update(dt);

                    window.clear(sf::Color(0, 0, 0));
                    drawCloth(window, cloth, scaling);
                    window.display();
                }
                break;
            default:
                break;
            }
        }

        if ((int)simulationTimer.getElapsedTime().asSeconds() > WIND_FREQUENCY)
        {
            cloth.applyForces(GRAVITY, FRICTION, WIND_FORCE);
            if ((int)simulationTimer.getElapsedTime().asSeconds() > WIND_FREQUENCY + WIND_DURATION)
            {
                simulationTimer.restart();
            }
        }
        else
        {
            cloth.applyForces(GRAVITY, FRICTION, 0);
        }

        cloth.update(dt);
        window.clear(sf::Color(0, 0, 0));
        drawCloth(window, cloth, scaling);
        window.display();
    }

    return 0;
}