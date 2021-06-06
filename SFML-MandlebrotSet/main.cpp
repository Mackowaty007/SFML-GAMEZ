#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    //variables
    int screenWidth = 800;
    int screenHeight = 800;
    int pixSize = 1;
    //Mandlebrot Variables

    sf::RenderWindow app(sf::VideoMode(screenWidth, screenHeight), "SFML window");
    sf::RectangleShape pix(sf::Vector2f(pixSize,pixSize));



    app.clear();

    for(float x=0;x<screenWidth;x++)
        {
                for(float y=0;y<screenHeight;y++)
                {
                        //declaring variables
                        float i=0;
                        float cx=-2+x/300;
                        float cy=-2+y/300;
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
                        pix.setFillColor(sf::Color(i,i,i));
                        pix.setPosition(x,y);
                        app.draw(pix);
                }
            }
    app.display();



    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }
    }
    return EXIT_SUCCESS;
}
