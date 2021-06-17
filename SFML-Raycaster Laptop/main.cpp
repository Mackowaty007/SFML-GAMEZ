#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#define PI 3.14159265

//returns sin and cos of the angle you gave here
float ReturnCos(float angle){
    //calculate the ray position
    return cos(angle * PI / 180.0f);
}
float ReturnSin(float angle){
    return sin(angle * PI / 180.0f);
}
int main()
{
    sf::VertexArray lines(sf::LineStrip,2);
    sf::VertexArray Hlines(sf::LineStrip,2);
    lines[0].color = sf::Color(255,20,20);
    lines[1].color = sf::Color(255,20,20);
    Hlines[0].color = sf::Color(20,200,210);
    Hlines[1].color = sf::Color(20,200,210);

    //setup
    int screenWidth = 1000; int screenHeight = 500; int pixSize = 50; int arraySize = 10; int playerSize = 20; float playerDirection = 0;float rayDirection; int FOV = 20;
    float NumberOfRaySteps = 1;
    int map[arraySize][arraySize] =
    {//10 per 10 array
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,0,0,0,0,1,0,0,1},
        {1,0,0,0,0,0,1,0,0,1},
        {1,1,1,1,0,0,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };
    sf::RenderWindow app(sf::VideoMode(screenWidth, screenHeight), "SFML window");
    sf::RectangleShape pix(sf::Vector2f(pixSize-1,pixSize-1));
    sf::RectangleShape player(sf::Vector2f(playerSize,playerSize));
    player.setPosition(100,100);
    player.setOrigin(playerSize/2,playerSize/2);
    player.setFillColor(sf::Color(100,200,10));
    pix.setFillColor(sf::Color(10,100,50));
    //pix.setOrigin(pixSize/2,pixSize/2);

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        //input
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            player.move(ReturnCos(playerDirection)/10,ReturnSin(playerDirection)/10);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            player.move(-ReturnCos(playerDirection)/10,-ReturnSin(playerDirection)/10);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            playerDirection -= 0.1f;
            //i think this is disposable, the circle loops nicle without this
            if (playerDirection < 0){
                playerDirection = 360;
            }

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            playerDirection += 0.1f;
            //i think this is disposable, the circle loops nicle without this
            if (playerDirection > 360){
                playerDirection = 0;
            }
        }

        //frame rendering
        app.clear();
        //drawing the map
        for(int x=0;x<arraySize;x++){
            for(int y=0;y<arraySize;y++){
                if(map[x][y]){
                    //drawing the map
                    pix.setPosition(x*pixSize,y*pixSize);
                    app.draw(pix);
                    //colisions
                    if(player.getPosition().x+playerSize/2 > x*pixSize-pixSize/2 && player.getPosition().x-playerSize/2 < x*pixSize+pixSize/2 && player.getPosition().y+playerSize/2 > y*pixSize-pixSize/2 && player.getPosition().y-playerSize/2 < y*pixSize+pixSize/2){

                    }
                }
            }
        }
        //drawing the player
        app.draw(player);

        //drawing rays
        for(int i=-FOV;i<FOV;i++){
            rayDirection = playerDirection + i;
            //a hacky fix for the problem with having the player direction being too small
            if(rayDirection < 0){rayDirection = 360 + playerDirection + i;}

            //Vertical lines
            lines[0].position = sf::Vector2f(player.getPosition());
            //checks if ray is directed to the left or the right
            if(rayDirection > 90 && rayDirection < 270){
                //casts a ray until it hits somehthin
                do{
                    lines[1].position = sf::Vector2f(player.getPosition().x - pixSize*NumberOfRaySteps - 1 - (static_cast<int>(player.getPosition().x)%pixSize), player.getPosition().y - tan(rayDirection*PI/180)*(pixSize*NumberOfRaySteps+(static_cast<int>(player.getPosition().x)%pixSize)));
                    NumberOfRaySteps++;
                    if(lines[1].position.y>screenHeight){
                        break;
                    }
                }
                while(!map[static_cast<int>(lines[1].position.x)/pixSize][static_cast<int>(lines[1].position.y)/pixSize] && NumberOfRaySteps<10);
            }
            else{
                //casts a ray until it hits somehthin
                NumberOfRaySteps = 1;
                do{
                    lines[1].position = sf::Vector2f(player.getPosition().x + pixSize*NumberOfRaySteps -  (static_cast<int>(player.getPosition().x)%pixSize), player.getPosition().y + tan(rayDirection*PI/180)*(pixSize*NumberOfRaySteps-(static_cast<int>(player.getPosition().x)%pixSize)));
                    NumberOfRaySteps++;
                    if(lines[1].position.y>screenHeight){
                        break;
                    }
                }
                while(!map[static_cast<int>(lines[1].position.x)/pixSize][static_cast<int>(lines[1].position.y)/pixSize] && NumberOfRaySteps<10);
            }
            app.draw(lines);
            NumberOfRaySteps = 0;


            //Horizontal lines
            Hlines[0].position = sf::Vector2f(player.getPosition());
            //checks if ray is directed to the left or the right
            if(rayDirection > 180 && rayDirection < 360){
                //casts a ray until it hits somehthin
                do{
                    Hlines[1].position = sf::Vector2f(player.getPosition().x + tan((rayDirection-90)*PI/180)*(pixSize*NumberOfRaySteps-(static_cast<int>(-player.getPosition().y)%pixSize)), player.getPosition().y - 1 - pixSize*NumberOfRaySteps - (static_cast<int>(player.getPosition().y)%pixSize));
                    NumberOfRaySteps++;
                    if(Hlines[1].position.x>screenHeight || Hlines[1].position.x<0){
                        break;
                    }
                }
                //cast the ray again if this is true!!!
                while(!map[static_cast<int>(Hlines[1].position.x)/pixSize][static_cast<int>(Hlines[1].position.y)/pixSize] && NumberOfRaySteps<10);
            }
            else{
                //casts a ray until it hits somehthin
                NumberOfRaySteps = 0;
                do{
                    Hlines[1].position = sf::Vector2f(player.getPosition().x - tan((rayDirection-90)*PI/180)*(pixSize*NumberOfRaySteps+(pixSize-(static_cast<int>(player.getPosition().y)%pixSize))), player.getPosition().y + pixSize*NumberOfRaySteps + pixSize-(static_cast<int>(player.getPosition().y)%pixSize));
                    NumberOfRaySteps++;
                    if(Hlines[1].position.x>screenHeight || Hlines[1].position.x<0){
                        break;
                    }
                }
                while(!map[static_cast<int>(Hlines[1].position.x)/pixSize][static_cast<int>(Hlines[1].position.y)/pixSize] && NumberOfRaySteps<10);
            }
            app.draw(Hlines);
            NumberOfRaySteps = 0;

            //sum rays

        }
        app.display();
    }
    return EXIT_SUCCESS;
}
