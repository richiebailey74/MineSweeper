#pragma once
#include <SFML/Graphics.hpp>
#include "textureManager.h"
#include <vector>


class UI {
public:
	UI();
	UI(int mineNum);
	sf::Sprite debugButtonSprite;
	sf::Sprite digitsDisplaySprite;
	sf::Sprite digitDisplaySprite1;
	sf::Sprite digitDisplaySprite2;
	sf::Sprite digitDisplaySprite3;
	sf::Sprite digitDisplaySprite4;
	sf::Sprite emptyDisplaySprite;
	sf::Sprite faceDisplaySprite;
	sf::Sprite testButton1Sprite;
	sf::Sprite testButton2Sprite;
	sf::Sprite testButton3Sprite;
	

	std::vector<sf::Sprite> digitDisplayVec;

	void drawUI(sf::RenderWindow& window);
	void setDigitDisplay();   //overload this for the test buttons
	void changeDigitDisplay(int displayedCount);
	void createSpriteTexture(int digitNum, sf::Sprite& referenceSprite);

};

