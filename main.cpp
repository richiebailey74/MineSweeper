#include <SFML/Graphics.hpp>
#include "RandomNumGen.h"
#include "textureManager.h"
#include "Tile.h"
#include "UI.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>

using namespace std;


//25x16 tiles so 400 total
//50 randomly generated mines

int main() {

    //========== INITIALIZATION STUFF ==========//
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    
    //     Load textures from files
    textureManager::LoadTexture("debug");
    textureManager::LoadTexture("tile_hidden");
    textureManager::LoadTexture("tile_revealed");
    textureManager::LoadTexture("test_1");
    textureManager::LoadTexture("test_2");
    textureManager::LoadTexture("test_3");
    textureManager::LoadTexture("face_happy");
    textureManager::LoadTexture("number_1");
    textureManager::LoadTexture("number_2");
    textureManager::LoadTexture("number_3");
    textureManager::LoadTexture("number_4");
    textureManager::LoadTexture("number_5");
    textureManager::LoadTexture("number_6");
    textureManager::LoadTexture("number_7");
    textureManager::LoadTexture("number_8");
    textureManager::LoadTexture("mine");
    textureManager::LoadTexture("flag");
    textureManager::MakeDigitTextures();

    int tileWidth = textureManager::GetTexture("tile_hidden").getSize().x;
    int tileHeight = textureManager::GetTexture("tile_hidden").getSize().y;
    

    //board object to be used for the duration of the game
    Board BoardObj;

    //continuously loops while window remains open, checking for events
    while (window.isOpen()) {

        //========== UPDATE ==========//

        //creates the event object
        sf::Event event;
        while (window.pollEvent(event)) {
            

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            //if the event is a mouse click enter here
            if (event.type == sf::Event::MouseButtonPressed) {
                
                //gets the mouse position
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                //if it is a left click check UI (right clicks don't affect UI)
                //can still click UI while the game isn't playing
                if (event.mouseButton.button == sf::Mouse::Left) {
                    BoardObj.checkUITiles(mousePos, BoardObj);
                }

                //only accessible while the game is playing
                //passes in left or right click to the function to check game tiles
                if (BoardObj.gamePlaying) {
                    BoardObj.checkMineTiles(mousePos, event, BoardObj);
                    
                }
            }
        }


        //========== DRAW STUFF ==========//

        
        //     clear window
        window.clear(sf::Color::White); //call only once

        //     draw all the stuff (can be a lot of shit)
        BoardObj.drawBoard(window);

        //     display all drawn things to the window
        window.display(); //call only once


    }


    //========== FINAL SHUT DOWN ==========//
    textureManager::Clear();
    return 0;
}
