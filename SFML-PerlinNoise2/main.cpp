#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#define GRID_S 10
#define SCREEN_H 1000
#define SCREEN_W 1000
#define PI 3.14159265

int lerp(int A,int B,float t){
    return A+t*(B-A);
}
int slerp(int A,int B,float t){
    return A+((1+sin(t*PI-PI/2))/2)*(B-A);
}

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(SCREEN_W, SCREEN_H), "SFML window");
    sf::RectangleShape pix(sf::Vector2f(1,1));
    sf::VertexArray lines(sf::LinesStrip,2);
    lines[0].color = sf::Color(255,20,20);
    lines[1].color = sf::Color(255,20,20);

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


            float VectorGUL[2] = {cos(map[x/GRID_S][y/GRID_S] * PI / 180),sin(map[x/GRID_S][y/GRID_S] * PI / 180)};
            float VectorGUR[2] = {cos(map[x/GRID_S+1][y/GRID_S] * PI / 180),sin(map[x/GRID_S+1][y/GRID_S] * PI / 180)};
            float VectorGDL[2] = {cos(map[x/GRID_S][y/GRID_S+1] * PI / 180),sin(map[x/GRID_S][y/GRID_S+1] * PI / 180)};
            float VectorGDR[2] = {cos(map[x/GRID_S+1][y/GRID_S+1] * PI / 180),sin(map[x/GRID_S+1][y/GRID_S+1] * PI / 180)};

            float VectorPX = (x-(x/GRID_S*GRID_S))/(GRID_S/2*sqrt(2));
            float VectorPY = (y-(y/GRID_S*GRID_S))/(GRID_S/2*sqrt(2));

            float dotProductUL = (VectorGUL[0] * VectorPX + VectorGUL[1] * VectorPY)*64+127;
            float dotProductDL = (VectorGDL[0] * VectorPX + VectorGDL[1] * VectorPY)*64+127;
            float dotProductUR = (VectorGUR[0] * VectorPX + VectorGUR[1] * VectorPY)*64+127;
            float dotProductDR = (VectorGDR[0] * VectorPX + VectorGDR[1] * VectorPY)*64+127;

            //lerp(dotProductUL,dotProductUR,static_cast<float>(x-(x/GRID_S*GRID_S))/GRID_S);


            int PixColor = dotProductUL + dotProductDL + dotProductUR + dotProductDR;

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
