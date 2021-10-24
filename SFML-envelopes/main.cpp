#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

#define SCREEN_W 700
#define SCREEN_H 700

float lerp(int a,int b,float t){
    return a + t * (b - a);
}
int pythagoras(int a,int b){
    return sqrt(pow(a,2)+pow(b,2));
}

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(SCREEN_W, SCREEN_H), "SFML window");
    sf::VertexArray line(sf::Lines,2);
    line[0].position = sf::Vector2f(10,10);
    line[1].position = sf::Vector2f(112,200);
    sf::Vector2f pointA(10,10);
    sf::Vector2f pointB(250,400);
    sf::Vector2f pointA2(490,10);
    sf::Vector2f pointB2(300,400);
    float envelopeQuality = 0.01f;


    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        //input
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(pythagoras(sf::Mouse::getPosition(app).x-pointB.x,sf::Mouse::getPosition(app).y-pointB.y) < 20){
                pointB = sf::Vector2f(sf::Mouse::getPosition(app));
            }
            if(pythagoras(sf::Mouse::getPosition(app).x-pointB2.x,sf::Mouse::getPosition(app).y-pointB2.y) < 20){
                pointB2 = sf::Vector2f(sf::Mouse::getPosition(app));
            }
            if(pythagoras(sf::Mouse::getPosition(app).x-pointA.x,sf::Mouse::getPosition(app).y-pointA.y) < 20){
                pointA = sf::Vector2f(sf::Mouse::getPosition(app));
            }
            if(pythagoras(sf::Mouse::getPosition(app).x-pointA2.x,sf::Mouse::getPosition(app).y-pointA2.y) < 20){
                pointA2 = sf::Vector2f(sf::Mouse::getPosition(app));
            }
        }


        //render
        app.clear();
        //draw the leading lines
        line[0].position = pointA;
        line[1].position = pointB;
        app.draw(line);
        line[0].position = pointA2;
        line[1].position = pointB2;
        app.draw(line);

        for (float i=0;i<1;i+=envelopeQuality){
            line[0].position.x = lerp (pointA.x, pointB.x, i);
            line[0].position.y = lerp (pointA.y, pointB.y, i);
            line[1].position.x = lerp (pointB2.x, pointA2.x, i);
            line[1].position.y = lerp (pointB2.y, pointA2.y, i);
            app.draw(line);
        }


        app.display();
    }

    return EXIT_SUCCESS;
}
