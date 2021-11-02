#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#import <string>

#define HEIGHT 900
#define WIDTH 300
#define WINDOW_H 400
#define WINDOW_W 400
#define NEURON_SIZE 30

float obstacle1 = HEIGHT;
float obstacle2 = HEIGHT;
float obstacle3 = HEIGHT;
float carPos = 0.5f;
float neuron1, neuron2, neuron3;
float neuron4 = 0.4f;
int score = 0;
float velocity = 0.0005f;

float clamp(float variable, float min,float max){
    if (variable < min){
        variable = min;
    }
    if (variable > max){
        variable = max;
    }
    return variable;
}

void spawnObstacles(){
    //spawn obstacles
    switch (rand() % 6){
    case 1:
        obstacle1 = -400;
        obstacle2 = -400;
        obstacle3 = -100;
        break;
    case 2:
        obstacle1 = -400;
        obstacle2 = -100;
        obstacle3 = -400;
        break;
    case 3:
        obstacle1 = -100;
        obstacle2 = -400;
        obstacle3 = -400;
        break;
    case 4:
        obstacle1 = -100;
        obstacle2 = -100;
        obstacle3 = -400;
        break;
    case 5:
        obstacle1 = -100;
        obstacle2 = -400;
        obstacle3 = -100;
        break;
    case 6:
        obstacle1 = -400;
        obstacle2 = -100;
        obstacle3 = -100;
        break;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "neutral network window");
    sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT), "the car game");
    sf::RectangleShape car(sf::Vector2f(WIDTH/3,100));
    sf::RectangleShape obstacle(sf::Vector2f(WIDTH/3,100));
    sf::CircleShape neuron;
    sf::VertexArray line(sf::LineStrip,2);
    sf::Font font;
    font.loadFromFile("Arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Green);
    text.setPosition(WIDTH-20,0);

    neuron.setOrigin(NEURON_SIZE/2,NEURON_SIZE/2);
    neuron.setRadius(NEURON_SIZE/2);
    neuron.setOutlineThickness(-2);
    neuron.setOutlineColor(sf::Color(255,255,255));

    car.setFillColor(sf::Color(200,10,20));
    obstacle.setFillColor((sf::Color(20,110,50)));

    sf::Clock deltaClock;

    while (app.isOpen())
    {
        //move obstacles
        sf::Time dt = deltaClock.restart();
        obstacle1 += velocity * dt.asMicroseconds();
        obstacle2 += velocity * dt.asMicroseconds();
        obstacle3 += velocity * dt.asMicroseconds();

        //quiting the game
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }
        //input
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            neuron4 = 0;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            neuron4 = 1;
        }
        else{
            neuron4 = 0.5f;
        }

        carPos = neuron4;
        if (carPos < 0.3f){
            carPos = 0;
        }
        else if (carPos > 0.7){
            carPos = 1;
        }

        else if (carPos > 0.3 && carPos < 0.7){
            carPos = 0.5f;
        }
        std::cout << carPos << std::endl;

        //check collisions
        if(obstacle1 > HEIGHT && obstacle2 > HEIGHT && obstacle3 > HEIGHT){
            spawnObstacles();
        }
        if(obstacle1 + 100 > HEIGHT - 100 && obstacle1 < HEIGHT && carPos == 0 || obstacle2 + 100 > HEIGHT - 100 && obstacle2 < HEIGHT && carPos == 0.5f || obstacle3 + 100 > HEIGHT - 100 && obstacle3 < HEIGHT && carPos == 1){
            score ++;
        }

        //rendering
        app.clear();

        car.setPosition(carPos*WIDTH/3*2,HEIGHT - 100);
        obstacle.setPosition(0,obstacle1);

        app.draw(obstacle);
        obstacle.setPosition(WIDTH/3,obstacle2);
        app.draw(obstacle);
        obstacle.setPosition(WIDTH/3*2,obstacle3);
        app.draw(obstacle);

        app.draw(car);
        app.display();

        window.clear();

        text.setString("score = " + std::to_string(score));

        neuron1 = obstacle1/HEIGHT;
        neuron2 = obstacle2/HEIGHT;
        neuron3 = obstacle3/HEIGHT;

        neuron1 = clamp(neuron1,0,1);
        neuron2 = clamp(neuron2,0,1);
        neuron3 = clamp(neuron3,0,1);


        //input neurons
        neuron.setPosition(NEURON_SIZE + 10,NEURON_SIZE);
        neuron.setFillColor(sf::Color(neuron1*255,neuron1*255,neuron1*255));
        window.draw(neuron);
        neuron.setPosition(NEURON_SIZE + 10,2*NEURON_SIZE);
        neuron.setFillColor(sf::Color(neuron2*255,neuron2*255,neuron2*255));
        window.draw(neuron);
        neuron.setPosition(NEURON_SIZE + 10,3*NEURON_SIZE);
        neuron.setFillColor(sf::Color(neuron3*255,neuron3*255,neuron3*255));
        window.draw(neuron);
        //output neurons
        neuron.setPosition(6*NEURON_SIZE + 10,NEURON_SIZE*2);
        neuron.setFillColor(sf::Color(neuron4*255,neuron4*255,neuron4*255));
        window.draw(neuron);

        //draw connections
        line[0].position = sf::Vector2f(NEURON_SIZE + 10,NEURON_SIZE);
        line[1].position = sf::Vector2f(6*NEURON_SIZE + 10,NEURON_SIZE*2);
        window.draw(line);
        line[0].position = sf::Vector2f(NEURON_SIZE + 10,2*NEURON_SIZE);
        line[1].position = sf::Vector2f(6*NEURON_SIZE + 10,NEURON_SIZE*2);
        window.draw(line);
        line[0].position = sf::Vector2f(NEURON_SIZE + 10,3*NEURON_SIZE);
        line[1].position = sf::Vector2f(6*NEURON_SIZE + 10,NEURON_SIZE*2);
        window.draw(line);

        window.draw(text);

        window.display();
    }

    return EXIT_SUCCESS;
}
