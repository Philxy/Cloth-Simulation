#include "include/util.h"
#include <SFML/Graphics.hpp>
#include "include/entity.h"
#include <algorithm>

int main()
{
    // window size and rendering
    const int windowSizeX = 1300;
    const int windowSizeY = 1000;
    // cloth parameters
    Cloth cloth;
    cloth.width = 20;
    cloth.height = 50;
    cloth.restingDistance = 1;
    const double scaling = std::max(windowSizeX, windowSizeY) / std::max(cloth.width, cloth.height) * 0.8;
    cloth.topLeftX =  cloth.width* 0.15;
    cloth.topLeftY = 0;
    cloth.linkStrengthFirstNeighbor = 200;
    cloth.linkStrengthSecondNeighbor = 1;
    cloth.linkStrengthThirdNeighbor = 1;



    // simulatopn parameters
    const double gravity = 10;
    const double friction = .5;
    double dt = 0.01;

    

    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "SFML window");
    sf::Clock clock;

    cloth.initParticlesAndLinks();
    cloth.initLinksForEachPointMass();
    cloth.applyForces(gravity, friction);
    cloth.firstIntegration(dt);

    while (window.isOpen())
    {

        sf::Time elapsed = clock.restart();
        dt = elapsed.asSeconds();
        // std::cout << "FPS: " << 1 / dt << std::endl;
        dt = 0.01;

        sf::Event event;
        while (window.pollEvent(event))
        {

            switch (event.type)
            {

            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                break;

            case sf::Event::MouseButtonPressed:
                breakClosestLink(cloth, Vec2{(double)event.mouseButton.x / scaling, (double)event.mouseButton.y / scaling});
                break;

            case sf::Event::MouseWheelScrolled:
                int mouseX;
                int mouseY;
                mouseX = sf::Mouse::getPosition(window).x;
                mouseY = sf::Mouse::getPosition(window).y;
                breakClosestLink(cloth, Vec2{(double)mouseX / scaling, (double)mouseY / scaling});

                break;

            default:
                break;
            }
        }

        cloth.applyForces(gravity, friction);
        cloth.update(dt);

        window.clear();
        drawCloth(window, cloth, scaling);
        window.display();
    }

    return 0;
}