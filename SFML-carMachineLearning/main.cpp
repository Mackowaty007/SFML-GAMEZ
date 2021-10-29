#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#define HEIGHT 500
#define WIDHT 500

#define CAR_HEIGHT 28
#define CAR_WIDTH 10

sf::Vector2f carPos(200,200);
float velocity = 0.0001f;

int main()
{
    sf::RenderWindow app(sf::VideoMode(WIDHT, HEIGHT), "SFML window");
    sf::RectangleShape car(sf::Vector2f(CAR_WIDTH,CAR_HEIGHT));

    sf::Clock deltaClock;

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        //input
        sf::Time dt = deltaClock.restart();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            carPos.y -= velocity * dt.asMicroseconds();
        }

        //render
        app.clear();

        car.setPosition(carPos);
        app.draw(car);

        app.display();
    }

    return EXIT_SUCCESS;
}
