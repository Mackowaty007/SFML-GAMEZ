#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    //sf::VertexArray lines(sf::LineStrip,4);
    //setup
    int screenWidth = 1000; int screenHeight = 500; int pixSize = 50; int arraySize = 10; sf::Vector2f playerPos(300,300); int playerSize = 20;
    int map[arraySize][arraySize] =
    {//10 per 10 array
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,1,0,1,0,1},
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
    player.setFillColor(sf::Color(100,200,10));

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
            player.move(0.0f,-0.1f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            player.move(0.0f,0.1f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            player.move(-0.1f,0.0f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            player.move(0.1f,0.0f);
        }

        //frame rendering
        app.clear();
        //drawing the map
        for(int x=0;x<arraySize;x++){
            for(int y=0;y<arraySize;y++){
                if(map[y][x]){
                    pix.setPosition(x*pixSize,y*pixSize);
                    app.draw(pix);
                }
            }
        }
        //drawing the player
        app.draw(player);
        /*
        lines[0].position = sf::Vector2f(10, 0);
        lines[1].position = sf::Vector2f(20, 0);
        lines[2].position = sf::Vector2f(30, 5);
        lines[3].position = sf::Vector2f(40, 2);
        app.draw(lines);
        */
        app.display();
    }
    return EXIT_SUCCESS;
}
