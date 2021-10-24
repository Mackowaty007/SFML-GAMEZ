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
    sf::Vector2f pointB(10,SCREEN_H-10);
    sf::Vector2f pointA2(SCREEN_W-10,10);
    sf::Vector2f pointB2(SCREEN_W-10,SCREEN_H-10);
    sf::Vector2f pointAB(0,0);
    sf::Vector2f pointA2B2(0,0);
    sf::Vector2f pointAA2(0,0);
    sf::Vector2f pointABAA2(0,0);
    sf::Vector2f pointAA2A2B2(0,0);
    float envelopeQuality = 0.01f;
    sf::Vector2f lastPoint(0,0);

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
        line[0].color = sf::Color(255,20,20);
        line[1].color = sf::Color(255,20,20);

        line[0].position = pointA;
        line[1].position = pointB;
        app.draw(line);
        line[0].position = pointA2;
        line[1].position = pointB2;
        app.draw(line);
        line[0].position = pointA;
        line[1].position = pointA2;
        app.draw(line);

        line[0].color = sf::Color(0,200,20);
        line[1].color = sf::Color(0,200,20);

        for(float i=0;i<1;i+=envelopeQuality){
            pointAB = sf::Vector2f(lerp (pointB.x, pointA.x,i),lerp (pointB.y, pointA.y, i));
            pointAA2 = sf::Vector2f(lerp (pointA.x, pointA2.x, i),lerp (pointA.y, pointA2.y, i));
            pointA2B2 = sf::Vector2f(lerp (pointA2.x, pointB2.x,i),lerp (pointA2.y, pointB2.y, i));
            /*
            line[0].position = pointAB;
            line[1].position = pointAA2;
            app.draw(line);
            line[0].position = pointA2B2;
            line[1].position = pointAA2;
            app.draw(line);

            line[0].color = sf::Color(0,20,200);
            line[1].color = sf::Color(0,20,200);
            */
            pointABAA2 = sf::Vector2f(lerp (pointAB.x, pointAA2.x,i),lerp (pointAB.y, pointAA2.y, i));
            pointAA2A2B2 = sf::Vector2f(lerp (pointAA2.x, pointA2B2.x, i),lerp (pointAA2.y, pointA2B2.y, i));
            /*
            line[0].position = pointABAA2;
            line[1].position = pointAA2A2B2;
            app.draw(line);
            */
            line[0].color = sf::Color(200,200,200);
            line[1].color = sf::Color(200,200,200);

            line[0].position = sf::Vector2f(lerp(pointABAA2.x,pointAA2A2B2.x,i),lerp(pointABAA2.y,pointAA2A2B2.y,i));
            line[1].position = lastPoint;
            lastPoint = line[0].position;
            app.draw(line);
        }
        lastPoint = pointB;
        app.display();
    }
    return EXIT_SUCCESS;
}
