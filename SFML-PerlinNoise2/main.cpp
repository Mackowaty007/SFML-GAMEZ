#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#define GRID_S 5
#define SCREEN_H 500
#define SCREEN_W 500
#define PI 3.14159265

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(SCREEN_W, SCREEN_H), "SFML window");
    sf::RectangleShape pix(sf::Vector2f(1,1));
    sf::VertexArray lines(sf::LinesStrip,2);
    lines[0].color = sf::Color(255,20,20);
    lines[1].color = sf::Color(255,20,20);

    bool NormalizeVectors = false;

    int map[SCREEN_W][SCREEN_H] = {{0}};

    //generate an vector array
    for(int x=0;x<SCREEN_W/GRID_S+1;x++){
        for(int y=0;y<SCREEN_H/GRID_S+1;y++){
            map[x][y] = rand() % 360;
        }
    }

//draw
    app.clear();

    //draw the pixels
    for(int x=0;x<SCREEN_W;x++){
        for(int y=0;y<SCREEN_H;y++){
            pix.setPosition(x,y);

            float VectorGX;
            float VectorGY;
            float VectorPX;
            float VectorPY;
            int PixColor = 0;

            for (int X0=0;X0<2;X0++){
                for (int Y0=0;Y0<2;Y0++){
                    VectorGX = cos(map[x/GRID_S+X0][y/GRID_S+Y0] * PI / 180);
                    VectorGY = sin(map[x/GRID_S+X0][y/GRID_S+Y0] * PI / 180);
                    VectorPX = x-(x/GRID_S*GRID_S);
                    VectorPY = y-(y/GRID_S*GRID_S);

                    //normalize P Vector
                    float VectorPLength = sqrt(pow(VectorPX,2)+pow(VectorPY,2));
                    if(NormalizeVectors){
                        VectorPX = VectorPX/VectorPLength;
                        VectorPY = VectorPY/VectorPLength;
                    }
                    else{
                        VectorPX = VectorPX/(GRID_S/2*sqrt(2));
                        VectorPY = VectorPY/(GRID_S/2*sqrt(2));
                    }

                    PixColor = PixColor + ((VectorGX * VectorPX + VectorGY * VectorPY)*63+127);
                }
            }

            PixColor = PixColor/4;

            pix.setFillColor(sf::Color(PixColor,PixColor,PixColor));
            app.draw(pix);
        }
    }
    /*
    //draw the lines
    for(int x=0;x<SCREEN_W/GRID_S+1;x++){
        for(int y=0;y<SCREEN_H/GRID_S+1;y++){
            lines[0].position = sf::Vector2f(x*GRID_S,y*GRID_S);
            lines[1].position = sf::Vector2f(x*GRID_S+cos(map[x][y] * PI / 180)*GRID_S/2,y*GRID_S+sin(map[x][y] * PI / 180)*GRID_S/2);
            app.draw(lines);
        }
    }*/

    app.display();

	// Start the game loop
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
