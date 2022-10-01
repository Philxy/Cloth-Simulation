#include "include/util.h"
#include <SFML/Graphics.hpp>
#include "include/entity.h"

int main()
{
    // window size and rendering
    const int windowSizeX = 1000;
    const int windowSizeY = 1000;
    const double scaling = 50;

    // simulatopn parameters
    const double gravity = 1;
    const double friction = 1;
    double dt = 0.01;

    // cloth parameters
    Cloth cloth;
    cloth.width = 20;
    cloth.height = 10;
    cloth.topLeftX = 0;
    cloth.topLeftY = 0;
    cloth.restingDistance = 1;
    cloth.linkStrengthFirstNeighbor = 100;
    cloth.linkStrengthSecondNeighbor = 10;
    cloth.linkStrengthThirdNeighbor = 1;
    cloth.initParticlesAndLinks();
    cloth.applyForces(gravity, friction);
    cloth.firstIntegration(dt);


    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "SFML window");
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        sf::Time elapsed = clock.restart();
        dt = elapsed.asSeconds();
        std::cout << "FPS: " << 1/dt << std::endl;

        cloth.applyForces(gravity, friction);
        cloth.update(dt);

        
        window.clear();
        drawCloth(window, cloth, scaling);
        window.display();
    }
    
    return 0;
}