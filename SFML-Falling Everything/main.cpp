#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
    int WindowWidth = 800;
    int WindowHeight = 600;
    int pixSize = 10;
    int map[WindowWidth/pixSize][WindowHeight/pixSize];
    int mapBuffer[WindowWidth/pixSize][WindowHeight/pixSize];
    for (int i = 0;i<WindowWidth/pixSize;i++){
        for (int t = 0;t<WindowHeight/pixSize;t++){
            map[i][t] = 0;
            mapBuffer[i][t] = 0;
        }
    }
    sf::RenderWindow app(sf::VideoMode(WindowWidth, WindowHeight), "SFML window");
    sf::RectangleShape pix (sf::Vector2f(pixSize,pixSize));
    while (app.isOpen())
    {
        //close the window
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }
        //mouse set
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
            sf::Vector2i mousePos = sf::Mouse::getPosition(app);
            mapBuffer[mousePos.x/pixSize][mousePos.y/pixSize] = 1;
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i mousePos = sf::Mouse::getPosition(app);
            mapBuffer[mousePos.x/pixSize][mousePos.y/pixSize] = 0;
        }

        //rendering
        app.clear();
        for(int x=0;x<WindowWidth/pixSize;x++){
            for(int y=0;y<WindowHeight/pixSize;y++){

                //gravity and checking surroundings
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    if(map[x][y] && !map[x][y+1] && y < WindowHeight/pixSize-1){
                        mapBuffer[x][y+1] = 1;
                        mapBuffer[x][y] = 0;
                    }
                    else if (map[x][y] && map[x-1][y+1] == 0 && y < WindowHeight/pixSize-1){
                        mapBuffer[x-1][y+1] = 1;
                        mapBuffer[x][y] = 0;
                    }
                    else if (map[x][y] && map[x+1][y+1] == 0 && y < WindowHeight/pixSize-1){
                        mapBuffer[x+1][y+1] = 1;
                        mapBuffer[x][y] = 0;
                    }
                }

                //swapping buffers
                map[x][y] = mapBuffer[x][y];

                //drawing the pixels
                if(map[x][y] == 1){
                    pix.setFillColor(sf::Color(200,170,10));
                    pix.setPosition(x*pixSize,y*pixSize);
                    app.draw(pix);
                }
                if(map[x][y] == 2){
                    pix.setFillColor(sf::Color(10,15,200));
                    pix.setPosition(x*pixSize,y*pixSize);
                    app.draw(pix);
                }
            }
        }
        app.display();
    }
    return EXIT_SUCCESS;
}
