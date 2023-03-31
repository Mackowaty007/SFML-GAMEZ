#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

int screenHeight = 1000;
int screenWidth = 1000;
float cursorSpeed = 0.1;
float circle1Radious = 700;
float circle2Radious = 700;

int penPosition[2] = {screenWidth/2,screenHeight/2};

int main()
{
    sf::RenderWindow app(sf::VideoMode(screenWidth, screenHeight), "SFML window");
    sf::RectangleShape cursor(sf::Vector2f(10,10));
    cursor.setPosition(500,500);
    sf::View view(sf::Vector2f(screenWidth/2,screenHeight/2), sf::Vector2f(screenWidth,screenHeight));
    sf::Vertex line1[] =
    {
        sf::Vertex(sf::Vector2f(0.f, 0.f)),
        sf::Vertex(sf::Vector2f(cursor.getPosition().x, cursor.getPosition().y))
    };
    sf::Vertex line2[] =
    {
        sf::Vertex(sf::Vector2f(screenWidth, 0.f)),
        sf::Vertex(sf::Vector2f(cursor.getPosition().x, cursor.getPosition().y))
    }; 
    sf::CircleShape circle1(circle1Radious);
    circle1.setFillColor(sf::Color(150, 50, 250,0));
    circle1.setOutlineThickness(1);
    circle1.setOutlineColor(sf::Color(250, 150, 100));

    sf::CircleShape circle2(circle2Radious);
    circle2.setFillColor(sf::Color(150, 50, 250,0));
    circle2.setOutlineThickness(1);
    circle2.setOutlineColor(sf::Color(250, 150, 100));

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            cursor.move(0,-cursorSpeed);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            cursor.move(0,cursorSpeed);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            cursor.move(-cursorSpeed,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            cursor.move(cursorSpeed,0);
        }
        /*
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
            circle1Radious ++;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
            circle2Radious ++;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
            circle1Radious --;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
            circle2Radious --;
        }*/

        sf::Vertex line1[] =
        {
            sf::Vertex(sf::Vector2f(0.f, 0.f)),
            sf::Vertex(sf::Vector2f(cursor.getPosition().x, cursor.getPosition().y))
        };
        sf::Vertex line2[] =
        {
            sf::Vertex(sf::Vector2f(screenWidth, 0.f)),
            sf::Vertex(sf::Vector2f(cursor.getPosition().x, cursor.getPosition().y))
        };

        circle1Radious=sqrt(pow(cursor.getPosition().x,2)+pow(cursor.getPosition().y,2));
        circle2Radious=sqrt(pow(screenWidth - cursor.getPosition().x,2)+pow(cursor.getPosition().y,2));

        circle1.setRadius(circle1Radious);
        circle2.setRadius(circle2Radious);
        circle1.setPosition(-circle1Radious,-circle1Radious);
        circle2.setPosition(-circle2Radious+screenWidth,-circle2Radious);

        app.setView(view);
        //drawing the mandlebrot
        app.clear();
        cursor.setFillColor(sf::Color(100,10,100));
        app.draw(cursor);
        app.draw(line1, 2, sf::Lines);
        app.draw(line2, 2, sf::Lines);
        app.draw(circle1);
        app.draw(circle2);

        app.display();
    }
    return EXIT_SUCCESS;
}
