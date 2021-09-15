#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#define GRID_S 100
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

    bool NormalizeVectors = true;

    int map[SCREEN_W][SCREEN_H] = {{0}};

    //generate an vector array
    for(int x=0;x<SCREEN_W/GRID_S;x++){
        for(int y=0;y<SCREEN_H/GRID_S;y++){
            map[x][y] = rand() % 360;
        }
    }

//draw
    app.clear();

    //draw the pixels
    for(int x=0;x<SCREEN_W;x++){
        for(int y=0;y<SCREEN_H;y++){
            pix.setPosition(x,y);

            float VectorGX = cos(map[x/GRID_S][y/GRID_S] * PI / 180);
            float VectorGY = sin(map[x/GRID_S][y/GRID_S] * PI / 180);
            float VectorPX = (x-(x/GRID_S*GRID_S))-GRID_S/2;
            float VectorPY = (y-(y/GRID_S*GRID_S))-GRID_S/2;
            //normalize P Vector
            if(NormalizeVectors){
                float VectorPLength = sqrt(pow(VectorPX,2)+pow(VectorPY,2));
                VectorPX = VectorPX/VectorPLength;
                VectorPY = VectorPY/VectorPLength;
            }
            else{
                VectorPX = VectorPX/(GRID_S/2*sqrt(2));
                VectorPY = VectorPY/(GRID_S/2*sqrt(2));
            }

            int PixColor = (VectorGX * VectorPX + VectorGY * VectorPY)*127+127;


            //std::cout << VectorPY << std::endl;

            pix.setFillColor(sf::Color(PixColor,PixColor,PixColor));
            app.draw(pix);
        }
    }

    //draw the lines
    for(int x=0;x<SCREEN_W/GRID_S;x++){
        for(int y=0;y<SCREEN_H/GRID_S;y++){
            lines[0].position = sf::Vector2f(x*GRID_S+GRID_S/2,y*GRID_S+GRID_S/2);
            lines[1].position = sf::Vector2f(x*GRID_S+GRID_S/2+cos(map[x][y] * PI / 180)*GRID_S/2,y*GRID_S+GRID_S/2+sin(map[x][y] * PI / 180)*GRID_S/2);
            app.draw(lines);
        }
    }

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
