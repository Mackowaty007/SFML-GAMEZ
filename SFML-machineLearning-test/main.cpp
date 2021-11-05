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
#define WEB_WIDHT 6

float obstacle1 = HEIGHT;
float obstacle2 = HEIGHT;
float obstacle3 = HEIGHT;
int carPos = 2;
float neuron[WEB_WIDHT][WEB_HEIGHT];
float neuronOutput[WEB_WIDHT][WEB_HEIGHT];
float bias[WEB_WIDHT][WEB_HEIGHT];
float multiplyer[WEB_WIDHT][WEB_HEIGHT][WEB_HEIGHT];
//              ^x neuro   ^y neuro    ^y where the connection goes
int score = 0;
float velocity = 0.0005f;



float clamp(float variable){
    if (variable < 0){
        variable = 0;
    }
    if (variable > 1){
        variable = 1;
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
    for(int x=0;x<WEB_WIDHT;x++){
        for(int y=0;y<WEB_HEIGHT;y++){
            bias[x][y] = 0;//(float(rand())/float((RAND_MAX)) * 0.5f);
            for(int yconnection=0;yconnection<WEB_HEIGHT;yconnection++){
               multiplyer[x][y][yconnection] = (float(rand())/float((RAND_MAX)) * 2)-1;
            }
        }
    }

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

        if(neuron[WEB_WIDHT-1][0]>neuron[WEB_WIDHT-1][1] && neuron[WEB_WIDHT-1][0]>neuron[WEB_WIDHT-1][2]){
            carPos = 1;
        }
        if(neuron[WEB_WIDHT-1][1]>neuron[WEB_WIDHT-1][0] && neuron[WEB_WIDHT-1][1]>neuron[WEB_WIDHT-1][2]){
            carPos = 2;
        }
        if(neuron[WEB_WIDHT-1][2]>neuron[WEB_WIDHT-1][0] && neuron[WEB_WIDHT-1][2]>neuron[WEB_WIDHT-1][1]){
            carPos = 3;
        }


        //check collisions
        if(obstacle1 > HEIGHT && obstacle2 > HEIGHT && obstacle3 > HEIGHT){
            spawnObstacles();
        }
        if(obstacle1 + 100 > HEIGHT - 100 && obstacle1 < HEIGHT && carPos == 1 || obstacle2 + 100 > HEIGHT - 100 && obstacle2 < HEIGHT && carPos == 2 || obstacle3 + 100 > HEIGHT - 100 && obstacle3 < HEIGHT && carPos == 3){
            score ++;
        }

        neuron[0][0] = obstacle1/HEIGHT;
        neuron[0][1] = obstacle2/HEIGHT;
        neuron[0][2] = obstacle3/HEIGHT;

        //rendering
        app.clear();

        car.setPosition(WIDTH/3*(carPos-1),HEIGHT - 100);

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

        for(int x = 0;x<WEB_WIDHT;x++){
            for(int y = 0;y<WEB_HEIGHT;y++){
                //input neurons
                Neuron.setPosition(2*x * NEURON_SIZE + NEURON_SIZE,y*NEURON_SIZE + NEURON_SIZE);
                neuron[x][y] = clamp(neuron[x][y]);
                Neuron.setFillColor(sf::Color(neuron[x][y]*255,neuron[x][y]*255,neuron[x][y]*255));
                Neuron.setOutlineColor(sf::Color(bias[x][y]*255,bias[x][y]*255,bias[x][y]*255));
                window.draw(Neuron);

                neuron[x+1][y] = 0;

                //draw connections
                if(x!=WEB_WIDHT-1){
                    for(int allY = 0;allY<WEB_HEIGHT;allY++){
                        line[0].position = sf::Vector2f(2*x * NEURON_SIZE + NEURON_SIZE,y*NEURON_SIZE + NEURON_SIZE);
                        line[1].position = sf::Vector2f(2*(x+1) * NEURON_SIZE + NEURON_SIZE,allY*NEURON_SIZE + NEURON_SIZE);
                        neuronOutput[x][y] = neuron[x][y]*multiplyer[x][y][allY]+bias[x][y];
                        neuronOutput[x][y] = clamp(neuronOutput[x][y]);
                        line[0].color = sf::Color(multiplyer[x][y][allY]*255,multiplyer[x][y][allY]*255,multiplyer[x][y][allY]*255);
                        line[1].color = sf::Color(multiplyer[x][y][allY]*255,multiplyer[x][y][allY]*255,multiplyer[x][y][allY]*255);
                        window.draw(line);

                        //set next web layer neuron values
                        for(int everyY=0;everyY<WEB_HEIGHT;everyY++){
                            neuron[x+1][y] += neuronOutput[x][allY] * multiplyer[x][allY][everyY] + bias[x][allY];
                        }
                    }
                }
            }
        }


        window.draw(text);

        window.display();
    }

    return EXIT_SUCCESS;
}
