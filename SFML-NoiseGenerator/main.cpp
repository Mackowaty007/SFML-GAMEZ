#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>

int main()
{
    //world map
    int map[80][80];



    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 800), "SFML window");
    sf::RectangleShape pixel(sf::Vector2f(10.0f,10.0f));
    pixel.setFillColor(sf::Color(10,200,10));
	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        for (int x = 0;x<80;x++){
            for (int y = 0;y<80;y++){
                map[x][y] = rand()%255;
            }
        }
        //draw
        app.clear();
        for (int i = 0;i < 80;i++){
            for (int y = 0;y<80;y++){
                pixel.setPosition(y * 10,i * 10);
                pixel.setFillColor(sf::Color(map[i][y],map[i][y],map[i][y]));
                app.draw(pixel);
            }
        }
        app.display();
    }

    return EXIT_SUCCESS;
}
