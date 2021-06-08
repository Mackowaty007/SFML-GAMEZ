#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    //setting stuff up
    int pixSize = 10;
    int screenWidth = 1000;
    int screenHeight = 1000;
    int neighbourNumber = 0;
    int map[(screenWidth/pixSize)+1][(screenHeight/pixSize)+1];
    int mapBuffer[screenWidth/pixSize][screenHeight/pixSize];
    sf::RenderWindow app(sf::VideoMode(screenWidth, screenHeight), "SFML window");
    sf::RectangleShape pix (sf::Vector2f(pixSize,pixSize));

    //filling the screen buffer with blanks
    for (int x=0;x<(screenWidth/pixSize)+1;x ++){
        for (int y=0;y<(screenHeight/pixSize)+1;y ++){
            map[x][y] = 0;
            mapBuffer[x][y] = 0;
        }
    }

    while (app.isOpen())
    {
        //closing the window
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }
        //drawing cells using the cursor
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i mousePos = sf::Mouse::getPosition(app);
            mapBuffer[mousePos.x/pixSize][mousePos.y/pixSize] = 1;
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            sf::Vector2i mousePos = sf::Mouse::getPosition(app);
            mapBuffer[mousePos.x/pixSize][mousePos.y/pixSize] = 0;
        }
        //checking neighbour cells and drawing the alive cells
        app.clear();
        for (int x=1;x<(screenWidth-pixSize)/pixSize;x += 1){
            for (int y=1;y<(screenHeight-pixSize*14)/pixSize;y += 1){
                //check surroundings
                neighbourNumber = 0;
                //1
                if(map[x-1][y-1]){
                    neighbourNumber ++;
                }
                //2
                if(map[x][y-1]){
                    neighbourNumber ++;
                }
                //3
                if(map[x+1][y-1]){
                    neighbourNumber ++;
                }
                //4
                if(map[x-1][y]){
                    neighbourNumber ++;
                }
                //5
                if(map[x+1][y]){
                    neighbourNumber ++;
                }
                //6
                if(map[x-1][y+1]){
                    neighbourNumber ++;
                }
                //7
                if(map[x][y+1]){
                    neighbourNumber ++;
                }
                //8
                if(map[x+1][y+1]){
                    neighbourNumber ++;
                }

                //Reviwe or kill cells based on neighbour number
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    if(neighbourNumber < 2 || neighbourNumber > 3){
                        mapBuffer[x][y] = 0;
                    }
                    else if(neighbourNumber == 3){
                        mapBuffer[x][y] = 1;
                    }
                }
                //swap buffers
                map[x][y] = mapBuffer[x][y];
                //render the alive cells
                if (map[x][y]){
                    pix.setPosition(x*pixSize,y*pixSize);
                    app.draw(pix);
                }
            }
        }
        app.display();
    }
    return EXIT_SUCCESS;
}
