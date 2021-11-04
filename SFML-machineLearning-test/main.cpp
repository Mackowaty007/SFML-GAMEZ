#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#import <string>

#define HEIGHT 900
#define WIDTH 300
#define WINDOW_H 400
#define WINDOW_W 400
#define NEURON_SIZE 30
#define WEB_HEIGHT 3
#define WEB_WIDHT 3

float obstacle1 = HEIGHT;
float obstacle2 = HEIGHT;
float obstacle3 = HEIGHT;
float carPos = 0.5f;
float neuron[WEB_WIDHT][WEB_HEIGHT];
float neuronOutput[WEB_WIDHT][WEB_HEIGHT];
float bias[WEB_WIDHT][WEB_HEIGHT];
float multiplyer[WEB_WIDHT][WEB_HEIGHT];
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
    sf::CircleShape Neuron;
    sf::VertexArray line(sf::LineStrip,2);
    sf::Font font;
    font.loadFromFile("Arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Green);
    text.setPosition(WIDTH-20,0);

    Neuron.setOrigin(NEURON_SIZE/2,NEURON_SIZE/2);
    Neuron.setRadius(NEURON_SIZE/2);
    Neuron.setOutlineThickness(-2);

    car.setFillColor(sf::Color(200,10,20));
    obstacle.setFillColor((sf::Color(20,110,50)));

    sf::Clock deltaClock;

    //generate random weights and biases
    bias[0][0] = 0;//(float(rand())/float((RAND_MAX)) * 0.5f);
    bias[0][1] = 0;//(float(rand())/float((RAND_MAX)) * 0.5f);
    bias[0][2] = 0;//(float(rand())/float((RAND_MAX)) * 0.5f);
    multiplyer[0][0] = (float(rand())/float((RAND_MAX)) * 1);
    multiplyer[0][1] = (float(rand())/float((RAND_MAX)) * 1);
    multiplyer[0][2] = (float(rand())/float((RAND_MAX)) * 1);

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
        //set output
        neuron[2][0] = neuronOutput[0][0] + neuronOutput[0][1] + neuronOutput[0][2];

        carPos = neuron[2][0];
        if (carPos < 0.3f){
            carPos = 0;
        }
        else if (carPos > 0.7){
            carPos = 1;
        }

        else if (carPos > 0.3 && carPos < 0.7){
            carPos = 0.5f;
        }

        //check collisions
        if(obstacle1 > HEIGHT && obstacle2 > HEIGHT && obstacle3 > HEIGHT){
            spawnObstacles();
        }
        if(obstacle1 + 100 > HEIGHT - 100 && obstacle1 < HEIGHT && carPos == 0 || obstacle2 + 100 > HEIGHT - 100 && obstacle2 < HEIGHT && carPos == 0.5f || obstacle3 + 100 > HEIGHT - 100 && obstacle3 < HEIGHT && carPos == 1){
            score ++;
        }

        neuron[0][0] = obstacle1/HEIGHT;
        neuron[0][1] = obstacle2/HEIGHT;
        neuron[0][2] = obstacle3/HEIGHT;

        neuron[0][0] = clamp(neuron[0][0],0,1);
        neuron[0][1] = clamp(neuron[0][1],0,1);
        neuron[0][2] = clamp(neuron[0][2],0,1);

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

        for(int y = 0;y<WEB_HEIGHT;y++){
            //input neurons
            Neuron.setPosition(NEURON_SIZE + 10,NEURON_SIZE);
            Neuron.setFillColor(sf::Color(neuron[0][0]*255,neuron[0][0]*255,neuron[0][0]*255));
            Neuron.setOutlineColor(sf::Color(bias[0][0] * 255,bias[0][0] * 255,bias[0][0] * 255));
            window.draw(Neuron);

            Neuron.setPosition(NEURON_SIZE + 10,2*NEURON_SIZE);
            Neuron.setFillColor(sf::Color(neuron[0][1]*255,neuron[0][1]*255,neuron[0][1]*255));
            Neuron.setOutlineColor(sf::Color(bias[0][1] * 255,bias[0][1] * 255,bias[0][1] * 255));
            window.draw(Neuron);

            Neuron.setPosition(NEURON_SIZE + 10,3*NEURON_SIZE);
            Neuron.setFillColor(sf::Color(neuron[0][2]*255,neuron[0][2]*255,neuron[0][2]*255));
            Neuron.setOutlineColor(sf::Color(bias[0][2] * 255,bias[0][2] * 255,bias[0][2] * 255));
            window.draw(Neuron);

            //output neurons
            Neuron.setPosition(6*NEURON_SIZE + 10,NEURON_SIZE*2);
            Neuron.setFillColor(sf::Color(neuron[2][0]*255,neuron[2][0]*255,neuron[2][0]*255));
            Neuron.setOutlineColor(sf::Color(bias[2][0] * 255,bias[2][0] * 255,bias[2][0] * 255));
            window.draw(Neuron);
        }

        //draw connections
        line[0].position = sf::Vector2f(NEURON_SIZE + 10,NEURON_SIZE);
        line[1].position = sf::Vector2f(6*NEURON_SIZE + 10,NEURON_SIZE*2);
        neuronOutput[0][0] = neuron[0][0]*multiplyer[0][0]+bias[0][0];
        neuronOutput[0][0] = clamp(neuronOutput[0][0],0,1);
        line[0].color = sf::Color(neuronOutput[0][0]*255,neuronOutput[0][0]*255,neuronOutput[0][0]*255);
        line[1].color = sf::Color(neuronOutput[0][0]*255,neuronOutput[0][0]*255,neuronOutput[0][0]*255);
        window.draw(line);

        line[0].position = sf::Vector2f(NEURON_SIZE + 10,2*NEURON_SIZE);
        line[1].position = sf::Vector2f(6*NEURON_SIZE + 10,NEURON_SIZE*2);
        neuronOutput[0][1] = neuron[0][1]*multiplyer[0][1]+bias[0][1];
        neuronOutput[0][1] = clamp(neuronOutput[0][1],0,1);
        line[0].color = sf::Color(neuronOutput[0][1]*255,neuronOutput[0][1]*255,neuronOutput[0][1]*255);
        line[1].color = sf::Color(neuronOutput[0][1]*255,neuronOutput[0][1]*255,neuronOutput[0][1]*255);
        window.draw(line);

        line[0].position = sf::Vector2f(NEURON_SIZE + 10,3*NEURON_SIZE);
        line[1].position = sf::Vector2f(6*NEURON_SIZE + 10,NEURON_SIZE*2);
        neuronOutput[0][2] = neuron[0][2]*multiplyer[0][2]+bias[0][2];
        neuronOutput[0][2] = clamp(neuronOutput[0][2],0,1);
        line[0].color = sf::Color(neuronOutput[0][2]*255,neuronOutput[0][2]*255,neuronOutput[0][2]*255);
        line[1].color = sf::Color(neuronOutput[0][2]*255,neuronOutput[0][2]*255,neuronOutput[0][2]*255);
        window.draw(line);

        window.draw(text);

        window.display();
    }

    return EXIT_SUCCESS;
}
