#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    //variables
    int screenWidth = 800;
    int screenHeight = 800;
    int pixSize = 1;
    int viewPosX = 0;
    int viewPosY = 0;
    int map[screenWidth][screenHeight][3];
    //random color generator
    int randomColor[255][3];
    for(int i=0;i<255;i++){
        randomColor[i][0] = rand() % 255;
        randomColor[i][1] = rand() % 255;
        randomColor[i][2] = rand() % 255;
    }
    //Mandlebrot Variables

    sf::RenderWindow app(sf::VideoMode(screenWidth, screenHeight), "SFML window");
    sf::RectangleShape pix(sf::Vector2f(pixSize,pixSize));
    sf::View view(sf::Vector2f(screenWidth/2,screenHeight/2), sf::Vector2f(screenWidth,screenHeight));
    sf::Clock clock;

//drawing the mandlebrot
    for(float x=0;x<screenWidth;x++)
        {
                for(float y=0;y<screenHeight;y++)
                {
                //declaring variables
                        int i=0;
                        //alignment
                        float cx=-2.15f+x/300;
                        float cy=-1.5f+y/300;
                        float zx=0;
                        float zy=0;
                        do
                        {
                            float xt=zx*zy;
                            zx=zx*zx-zy*zy+cx;
                            zy=2*xt+cy;
                            i++;
                        }
                        while(i<255&&(zx*zx+zy*zy)<4);

                        int convertedX = static_cast<int>(x);
                        int convertedY = static_cast<int>(y);
                        map[convertedX][convertedY][0] = randomColor[i][0];
                        map[convertedX][convertedY][1] = randomColor[i][1];
                        map[convertedX][convertedY][2] = randomColor[i][2];
                }
            }

        //rendering time
        sf::Time elapsed = clock.getElapsedTime();
        float sec = elapsed.asSeconds();
        std::cout << "Mandlebrot was made in " << sec <<std::endl;

    while (app.isOpen())
    {
        clock.restart();
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            viewPosX ++;
            view.setCenter(10,12);
        }
        app.setView(view);
        //drawing the mandlebrot
        app.clear();
        for(int x=0;x<screenWidth;x++){
            for(int y=0;y<screenHeight;y++){
                pix.setFillColor(sf::Color(map[x][y][0],map[x][y][1],map[x][y][2]));
                pix.setPosition(x,y);
                app.draw(pix);
            }
        }
        app.display();

        //measure draw time
        sf::Time elapsed = clock.getElapsedTime();
        float sec = elapsed.asSeconds();
        std::cout << "This frame took " << sec << " to render" <<std::endl;

    }
    return EXIT_SUCCESS;
}
