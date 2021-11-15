#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string.h>

#define HEIGHT 900
#define WIDTH 300
#define WINDOW_H 400
#define WINDOW_W 400
#define NEURON_SIZE 40
#define WEB_HEIGHT 3
#define WEB_WIDHT 2
#define GENERATION_TIME 5
#define GENERATION_HOP 0
#define VELOCITY 0.001f


float obstacle1 = HEIGHT , obstacle2 = HEIGHT , obstacle3 = HEIGHT;
int carPos = 2;

float neuron[WEB_WIDHT][WEB_HEIGHT];
float bias[WEB_WIDHT][WEB_HEIGHT];
float multiplyer[WEB_WIDHT][WEB_HEIGHT][WEB_HEIGHT];
//              ^x neuro   ^y neuro    ^y where the connection goes

float old_bias[WEB_WIDHT][WEB_HEIGHT];
float old_multiplyer[WEB_WIDHT][WEB_HEIGHT][WEB_HEIGHT];
//              ^x neuro   ^y neuro    ^y where the connection goes

int score = 0;
long int lastScore = 99999999999;
int currentGen = 0;

int obstacle_configuration_incrementer = 0;


float clamp(float variable){
    if (variable < -1){
        variable = -1;
    }
    if (variable > 1){
        variable = 1;
    }
    return variable;
}

//random spawn obstacles
/*
void spawnObstacles(){
    //spawn obstacles
    switch (rand() % 6){
    case 1:
        obstacle1 = -450;
        obstacle2 = -450;
        obstacle3 = -100;
        break;
    case 2:
        obstacle1 = -450;
        obstacle2 = -100;
        obstacle3 = -450;
        break;
    case 3:
        obstacle1 = -100;
        obstacle2 = -450;
        obstacle3 = -450;
        break;
    case 4:
        obstacle1 = -100;
        obstacle2 = -100;
        obstacle3 = -450;
        break;
    case 5:
        obstacle1 = -100;
        obstacle2 = -450;
        obstacle3 = -100;
        break;
    case 6:
        obstacle1 = -450;
        obstacle2 = -100;
        obstacle3 = -100;
        break;
    }
}
*/
// not random spawn obstacles
void spawnObstacles(){
    obstacle_configuration_incrementer ++;
    switch(obstacle_configuration_incrementer){
    case 1:
        obstacle1 = -450;
        obstacle2 = -450;
        obstacle3 = -100;
        break;
    case 2:
        obstacle1 = -450;
        obstacle2 = -100;
        obstacle3 = -450;
        break;
    case 3:
        obstacle1 = -100;
        obstacle2 = -450;
        obstacle3 = -450;
        break;
    case 4:
        obstacle1 = -100;
        obstacle2 = -100;
        obstacle3 = -450;
        break;
    case 5:
        obstacle1 = -100;
        obstacle2 = -450;
        obstacle3 = -100;
        break;
    case 6:
        obstacle1 = -450;
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
    text.setPosition(WIDTH-60,0);

    Neuron.setOrigin(NEURON_SIZE/2,NEURON_SIZE/2);
    Neuron.setRadius(NEURON_SIZE/2);
    Neuron.setOutlineThickness(-2);

    car.setFillColor(sf::Color(200,10,20));
    obstacle.setFillColor((sf::Color(20,110,50)));

    sf::Clock deltaClock;
    sf::Clock genClock;

    //generate random weights and biases
    for(int x=0;x<WEB_WIDHT;x++){
        for(int y=0;y<WEB_HEIGHT;y++){
            bias[x][y] = 0;//(float(rand())/float((RAND_MAX)) * GENERATION_HOP)-GENERATION_HOP;
            for(int yconnection=0;yconnection<WEB_HEIGHT;yconnection++){
               multiplyer[x][y][yconnection] = (float(rand())/float((RAND_MAX)) * GENERATION_HOP)-GENERATION_HOP/2;
            }
        }
    }

    //debug purpouses only!!
    multiplyer[0][0][0] = -1;
    multiplyer[0][1][1] = -1;
    multiplyer[0][2][2] = -1;

    while (app.isOpen())
    {
        //move obstacles
        sf::Time dt = deltaClock.restart();
        obstacle1 += VELOCITY * dt.asMicroseconds();
        obstacle2 += VELOCITY * dt.asMicroseconds();
        obstacle3 += VELOCITY * dt.asMicroseconds();

        //generate a random neutral network after a certain time
        sf::Time time1 = genClock.getElapsedTime();
        if(time1.asSeconds() > GENERATION_TIME){
            spawnObstacles();

            genClock.restart();
            if(score > lastScore){
                //delete this later!!!!!!!!!!!!!!!!!!!!!!!!
                obstacle_configuration_incrementer = 0;

                std::cout << "this gen was worse than the last one - score = " << score << " last score = " << lastScore << std::endl;
                score = 0;
                memcpy(bias, old_bias, sizeof(bias));
                memcpy(multiplyer, old_multiplyer, sizeof(multiplyer));
                //generate new multiplyers based on the old ones
                for(int x=0;x<WEB_WIDHT;x++){
                    for(int y=0;y<WEB_HEIGHT;y++){
                        bias[x][y] += (float(rand())/float((RAND_MAX)) * GENERATION_HOP)-GENERATION_HOP/2;
                        for(int yconnection=0;yconnection<WEB_HEIGHT;yconnection++){
                            multiplyer[x][y][yconnection] += (float(rand())/float((RAND_MAX)) * GENERATION_HOP)-GENERATION_HOP/2;
                            multiplyer[x][y][yconnection] = clamp(multiplyer[x][y][yconnection]);
                        }
                    }
                }
            }
            else{
                //delete this later!!!!!!!!!!!!!!!!!!!!!!!!
                obstacle_configuration_incrementer = 0;

                std::cout << "this gen was better than the last one - score = " << score << " last score = " << lastScore << std::endl;
                lastScore = score;
                score = 0;
                memcpy(old_bias, bias, sizeof(old_bias));
                memcpy(old_multiplyer, multiplyer, sizeof(old_multiplyer));
                //generate new multiplyers based on the new ones
                for(int x=0;x<WEB_WIDHT;x++){
                    for(int y=0;y<WEB_HEIGHT;y++){
                        bias[x][y] += (float(rand())/float((RAND_MAX)) * GENERATION_HOP)-GENERATION_HOP/2;
                        for(int yconnection=0;yconnection<WEB_HEIGHT;yconnection++){
                            multiplyer[x][y][yconnection] += (float(rand())/float((RAND_MAX)) * GENERATION_HOP)-GENERATION_HOP/2;
                            multiplyer[x][y][yconnection] = clamp(multiplyer[x][y][yconnection]);
                        }
                    }
                }
            }
        currentGen ++;
        }

        //quiting the game
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        //check which output neuron is the highest
        if(neuron[WEB_WIDHT-1][0]>=neuron[WEB_WIDHT-1][1] && neuron[WEB_WIDHT-1][0]>=neuron[WEB_WIDHT-1][2]){
            carPos = 1;
        }
        else if(neuron[WEB_WIDHT-1][1]>=neuron[WEB_WIDHT-1][0] && neuron[WEB_WIDHT-1][1]>=neuron[WEB_WIDHT-1][2]){
            carPos = 2;
        }
        else if(neuron[WEB_WIDHT-1][2]>=neuron[WEB_WIDHT-1][0] && neuron[WEB_WIDHT-1][2]>=neuron[WEB_WIDHT-1][1]){
            carPos = 3;
        }



        //check collisions
        if(obstacle1 > HEIGHT && obstacle2 > HEIGHT && obstacle3 > HEIGHT){
            spawnObstacles();
        }
        if(obstacle1 + 100 > HEIGHT - 100 && obstacle1 < HEIGHT && carPos == 1 || obstacle2 + 100 > HEIGHT - 100 && obstacle2 < HEIGHT && carPos == 2 || obstacle3 + 100 > HEIGHT - 100 && obstacle3 < HEIGHT && carPos == 3){
            score += dt.asMicroseconds();
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

        text.setString("score = " + std::to_string(score) + "gen = " + std::to_string(currentGen));


        for(int x = 0;x<WEB_WIDHT;x++){
            for(int y = 0;y<WEB_HEIGHT;y++){
                //input neurons
                Neuron.setPosition(2*x * NEURON_SIZE + NEURON_SIZE,y*NEURON_SIZE + NEURON_SIZE);
                neuron[x][y] = clamp(neuron[x][y] + bias[x][y]);
                if(neuron[x][y]>=0){
                    Neuron.setFillColor(sf::Color(0,neuron[x][y]*255,0));
                }
                if(neuron[x][y]<0){
                    Neuron.setFillColor(sf::Color(-neuron[x][y]*255,0,0));
                }
                if(bias[x][y]>=0){
                    Neuron.setOutlineColor(sf::Color(0,bias[x][y]*255,0));
                }
                if(bias[x][y]<0){
                    Neuron.setOutlineColor(sf::Color(-bias[x][y]*255,0,0));
                }
                window.draw(Neuron);

                neuron[x+1][y] = 0;

                //draw connections
                if(x!=WEB_WIDHT-1){
                    for(int allY = 0;allY<WEB_HEIGHT;allY++){
                        line[0].position = sf::Vector2f(2*x * NEURON_SIZE + NEURON_SIZE,y*NEURON_SIZE + NEURON_SIZE);
                        line[1].position = sf::Vector2f(2*(x+1) * NEURON_SIZE + NEURON_SIZE,allY*NEURON_SIZE + NEURON_SIZE);

                        if(multiplyer[1][1][allY] >= 0){
                            line[0].color = sf::Color(0,multiplyer[x][y][allY]*255,0);
                            line[1].color = sf::Color(0,multiplyer[x][y][allY]*255,0);
                        }
                        if(multiplyer[x][y][allY] < 0){
                            line[0].color = sf::Color(-multiplyer[x][y][allY]*255,0,0);
                            line[1].color = sf::Color(-multiplyer[x][y][allY]*255,0,0);
                        }

                        window.draw(line);

                        //set next web layer neuron values
                        neuron[x+1][y] += neuron[x][allY] * multiplyer[x][y][allY] + bias[x+1][y];
                    }
                }
            }
        }

        window.draw(text);

        window.display();
    }

    return EXIT_SUCCESS;
}
