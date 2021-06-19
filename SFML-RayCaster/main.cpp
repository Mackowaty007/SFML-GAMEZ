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
    sf::VertexArray Slines(sf::LineStrip,2);
    lines[0].color = sf::Color(255,20,20);
    lines[1].color = sf::Color(255,20,20);
    Hlines[0].color = sf::Color(20,200,210);
    Hlines[1].color = sf::Color(20,200,210);

    //setup
    int screenWidth = 1000; int screenHeight = 500; int pixSize = 20; int arraySize = 20; int playerSize = 10; float playerDirection = 0;float rayDirection; int FOV = 90/2;int DOF = 20;int sprintSpeed;
    float NumberOfRaySteps = 1; float Hlength,Vlength,Slength; int screenBarWidth = screenWidth/4/FOV; int WallColor[3]={200,200,200};int DoorColor[3]={100,200,100}; int CellingColor[3]={30,70,100};int FloorColor[3]={100,100,100};
    int map[arraySize][arraySize] =
    {//10 per 10 array (this is basically the game map)
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//1
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,0,1},
        {1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,2,0,2,0,2,0,2,0,2,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    sf::RenderWindow app(sf::VideoMode(screenWidth, screenHeight), "SFML window");
    sf::RectangleShape pix(sf::Vector2f(pixSize-1,pixSize-1));
    sf::RectangleShape player(sf::Vector2f(playerSize,playerSize));
    sf::RectangleShape screenBar(sf::Vector2f(screenBarWidth-1,100));
    sf::RectangleShape CellingAndFloor(sf::Vector2f(screenWidth/2,screenHeight/2));
    player.setPosition(100,100);
    player.setOrigin(playerSize/2,playerSize/2);
    player.setFillColor(sf::Color(100,200,10));
    pix.setFillColor(sf::Color(10,100,50));
    screenBar.setFillColor(sf::Color(10,10,200));


    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        //input
        playerDirection = (sf::Mouse::getPosition(app).x/2)%360;//mouse sensivity
        //float HeadTilt = (sf::Mouse::getPosition(app).x/2)

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){//sprint if shift is pressed
            sprintSpeed = 3;
        }
        else{
            sprintSpeed = 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            player.move(ReturnCos(playerDirection)/10*sprintSpeed,ReturnSin(playerDirection)/10*sprintSpeed);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            player.move(-ReturnCos(playerDirection)/10*sprintSpeed,-ReturnSin(playerDirection)/10*sprintSpeed);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            player.move(ReturnSin(playerDirection)/10*sprintSpeed,-ReturnCos(playerDirection)/10*sprintSpeed);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            player.move(ReturnSin(-playerDirection)/10*sprintSpeed,ReturnCos(playerDirection)/10*sprintSpeed);
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
                    if(player.getPosition().x+playerSize/2 > x*pixSize && player.getPosition().x-playerSize/2 < x*pixSize+pixSize && player.getPosition().y+playerSize/2 > y*pixSize && player.getPosition().y-playerSize/2 < y*pixSize+pixSize){
                        if(player.getPosition().x+playerSize/2 < x*pixSize+pixSize/2){
                            player.move(-1,0);
                        }
                        if(player.getPosition().x-playerSize/2 > x*pixSize+pixSize/2){
                            player.move(1,0);
                        }
                        if(player.getPosition().y+playerSize/2 < y*pixSize+pixSize/2){
                            player.move(0,-1);
                        }
                        if(player.getPosition().y-playerSize/2 > y*pixSize+pixSize/2){
                            player.move(0,1);
                        }
                    }
                }
            }
        }
        //drawing the player, floor and celling
        app.draw(player);

        CellingAndFloor.setFillColor(sf::Color(CellingColor[0],CellingColor[1],CellingColor[2]));
        CellingAndFloor.setPosition(screenWidth/2,0);
        app.draw(CellingAndFloor);
        CellingAndFloor.setFillColor(sf::Color(FloorColor[0],FloorColor[1],FloorColor[2]));
        CellingAndFloor.setPosition(screenWidth/2,screenHeight/2);
        app.draw(CellingAndFloor);

        //drawing rays
        Slines[0] = player.getPosition();

        for(int i=-FOV;i<FOV;i++){
            rayDirection = playerDirection + i;
            //a hacky fix for the problem with having the player direction being too small
            if(rayDirection < 0){rayDirection = 360 + playerDirection + i;}

            //Vertical lines
            //checks if ray is directed to the left or the right
            if(rayDirection > 90 && rayDirection < 270){
                //casts a ray until it hits somehthin
                do{
                    lines[1].position = sf::Vector2f(player.getPosition().x - pixSize*NumberOfRaySteps-1-(static_cast<int>(player.getPosition().x)%pixSize),player.getPosition().y - tan(rayDirection*PI/180)*(pixSize*NumberOfRaySteps+(static_cast<int>(player.getPosition().x)%pixSize)));
                    NumberOfRaySteps++;
                    if(lines[1].position.y>screenHeight){//prevents lines from beeing infinitley long
                        break;
                    }
                }
                while(!map[static_cast<int>(lines[1].position.x)/pixSize][static_cast<int>(lines[1].position.y)/pixSize] && NumberOfRaySteps<DOF);
            }
            else{
                //casts a ray until it hits somehthin
                NumberOfRaySteps = 1;
                do{
                    lines[1].position = sf::Vector2f(player.getPosition().x + pixSize*NumberOfRaySteps -  (static_cast<int>(player.getPosition().x)%pixSize), player.getPosition().y + tan(rayDirection*PI/180)*(pixSize*NumberOfRaySteps-(static_cast<int>(player.getPosition().x)%pixSize)));
                    NumberOfRaySteps++;
                    if(lines[1].position.y>screenHeight){//prevents lines from beeing infinitley long
                        break;
                    }
                }
                while(!map[static_cast<int>(lines[1].position.x)/pixSize][static_cast<int>(lines[1].position.y)/pixSize] && NumberOfRaySteps<DOF);
            }
            //app.draw(lines);
            NumberOfRaySteps = 0;


            //Horizontal lines
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
                while(!map[static_cast<int>(Hlines[1].position.x)/pixSize][static_cast<int>(Hlines[1].position.y)/pixSize] && NumberOfRaySteps<DOF);
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
                while(!map[static_cast<int>(Hlines[1].position.x)/pixSize][static_cast<int>(Hlines[1].position.y)/pixSize] && NumberOfRaySteps<DOF);
            }
            //app.draw(Hlines);
            NumberOfRaySteps = 0;

            //get line lenght
            Vlength = sqrt(pow(player.getPosition().x - lines[1].position.x,2)+pow(player.getPosition().y - lines[1].position.y,2));
            Hlength = sqrt(pow(player.getPosition().x - Hlines[1].position.x,2)+pow(player.getPosition().y - Hlines[1].position.y,2));

            //check
            if (Vlength > Hlength){
                Slines[1].position = Hlines[1].position;
                Slength = Hlength;
                //set color based on the wall type (for example doors have one color and normal walls have other colors
                if(map[static_cast<int>(Slines[1].position.x)/pixSize][static_cast<int>(Slines[1].position.y)/pixSize] == 1){
                    screenBar.setFillColor(sf::Color(WallColor[0]-Slength/2,WallColor[1]-Slength/2,WallColor[2]-Slength/2));
                }
                else{
                    screenBar.setFillColor(sf::Color(DoorColor[0],DoorColor[1],DoorColor[2]));
                }
            }
            else {
                Slines[1].position = lines[1].position;
                Slength =Vlength;
                //set color based on the wall orientation
                if(map[static_cast<int>(Slines[1].position.x)/pixSize][static_cast<int>(Slines[1].position.y)/pixSize] == 1){
                    screenBar.setFillColor(sf::Color(WallColor[0]-Slength/2+30,WallColor[1]-Slength/2+30,WallColor[2]-Slength/2+30));
                }
                else{
                    screenBar.setFillColor(sf::Color(DoorColor[0]+30,DoorColor[1]+30,DoorColor[2]+30));
                }
            }
            app.draw(Slines);

            //drawing the 3d View


            //fixing the fish eye effect (got this from a cool tutorial, cuz i was too dumb to figure this out myself)
            //float DeltaAngle = playerDirection-rayDirection;
            //if(DeltaAngle<0){DeltaAngle+=2*PI/180;}if(DeltaAngle>2*PI/180){DeltaAngle-=2*PI/180;}
            //Slength = Slength * cos(DeltaAngle/180);

            //fix this for more screen space on the right
            screenBar.setPosition((screenWidth - screenWidth/4+screenBarWidth/2)+i*screenBarWidth,screenHeight/2-((pixSize*screenHeight)/Slength)/2);
            screenBar.setSize(sf::Vector2f(screenBarWidth,(pixSize*screenHeight)/Slength));
            app.draw(screenBar);
        }
        app.display();
    }
    return EXIT_SUCCESS;
}
