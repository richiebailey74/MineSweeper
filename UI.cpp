#include "UI.h"

//constructor sets textures and positions for the User Interface (UI)
UI::UI() {
	debugButtonSprite.setTexture(textureManager::GetTexture("debug"));
	digitsDisplaySprite.setTexture(textureManager::GetTexture("digits"));
	faceDisplaySprite.setTexture(textureManager::GetTexture("face_happy"));
	testButton1Sprite.setTexture(textureManager::GetTexture("test_1"));
	testButton2Sprite.setTexture(textureManager::GetTexture("test_2"));
	testButton3Sprite.setTexture(textureManager::GetTexture("test_3"));

	digitDisplaySprite1.setTexture(textureManager::GetTexture("digits"));
	digitDisplaySprite2.setTexture(textureManager::GetTexture("digits"));
	digitDisplaySprite3.setTexture(textureManager::GetTexture("digits"));
	digitDisplaySprite4.setTexture(textureManager::GetTexture("digits"));

	float tileSideLength = textureManager::GetTexture("tile_hidden").getSize().y;
	float bottomBoardLength = (16 * tileSideLength);

	digitsDisplaySprite.setPosition(sf::Vector2f(0, bottomBoardLength));
	faceDisplaySprite.setPosition(sf::Vector2f(((11.5 * tileSideLength)), bottomBoardLength));
	debugButtonSprite.setPosition(sf::Vector2f(((15.5 * tileSideLength)), bottomBoardLength));
	testButton1Sprite.setPosition(sf::Vector2f(((17.5 * tileSideLength)), bottomBoardLength));
	testButton2Sprite.setPosition(sf::Vector2f(((19.5 * tileSideLength)), bottomBoardLength));
	testButton3Sprite.setPosition(sf::Vector2f(((21.5 * tileSideLength)), bottomBoardLength));

	setDigitDisplay();
}

//default function called in the constructor
void UI::setDigitDisplay() {

	float tileSideLength = textureManager::GetTexture("tile_hidden").getSize().y;
	float bottomBoardLength = (16 * tileSideLength);

	digitDisplaySprite1.setTexture(textureManager::GetTexture("digit0"));
	digitDisplaySprite2.setTexture(textureManager::GetTexture("digit5"));
	digitDisplaySprite3.setTexture(textureManager::GetTexture("digit0"));

	digitDisplaySprite1.setPosition(sf::Vector2f(0, bottomBoardLength));
	digitDisplaySprite2.setPosition(sf::Vector2f(21, bottomBoardLength));
	digitDisplaySprite3.setPosition(sf::Vector2f(2 * 21, bottomBoardLength));
	digitDisplayVec.push_back(digitDisplaySprite1);
	digitDisplayVec.push_back(digitDisplaySprite2);
	digitDisplayVec.push_back(digitDisplaySprite3);

}

void UI::changeDigitDisplay(int displayedCount) {
	float tileSideLength = textureManager::GetTexture("tile_hidden").getSize().y;
	float bottomBoardLength = (16 * tileSideLength);

	//changes display depending on the value passed in
	//splits into three: if zero, positive, or negative
	//zero just assigns all zeros
	//positive and negative use integer divisions and modulos to get individual digits and to load appropriate texture to the sprite vector
	if (displayedCount == 0) {
		digitDisplaySprite1.setTexture(textureManager::GetTexture("digit0"));
		digitDisplaySprite2.setTexture(textureManager::GetTexture("digit0"));
		digitDisplaySprite3.setTexture(textureManager::GetTexture("digit0"));

		digitDisplaySprite1.setPosition(sf::Vector2f(0, bottomBoardLength));
		digitDisplaySprite2.setPosition(sf::Vector2f(21, bottomBoardLength));
		digitDisplaySprite3.setPosition(sf::Vector2f(2 * 21, bottomBoardLength));
		digitDisplayVec.push_back(digitDisplaySprite1);
		digitDisplayVec.push_back(digitDisplaySprite2);
		digitDisplayVec.push_back(digitDisplaySprite3);
	}
	else if (displayedCount > 0) {
		if (displayedCount / 10 == 0) {
			int firstDigit = displayedCount;
			string digitFirst = "digit";
			digitFirst += std::to_string(firstDigit);
			
			digitDisplaySprite1.setTexture(textureManager::GetTexture("digit0"));
			digitDisplaySprite2.setTexture(textureManager::GetTexture("digit0"));
			createSpriteTexture(firstDigit, digitDisplaySprite3);

			digitDisplaySprite1.setPosition(sf::Vector2f(0, bottomBoardLength));
			digitDisplaySprite2.setPosition(sf::Vector2f(21, bottomBoardLength));
			digitDisplaySprite3.setPosition(sf::Vector2f(2 * 21, bottomBoardLength));
			digitDisplayVec.push_back(digitDisplaySprite1);
			digitDisplayVec.push_back(digitDisplaySprite2);
			digitDisplayVec.push_back(digitDisplaySprite3);
		}
		else if (displayedCount / 100 == 0) {
			int firstDigit = displayedCount / 10;
			int secondDigit = displayedCount % 10;


			digitDisplaySprite1.setTexture(textureManager::GetTexture("digit0"));
			createSpriteTexture(firstDigit, digitDisplaySprite2);
			createSpriteTexture(secondDigit, digitDisplaySprite3);

			digitDisplaySprite1.setPosition(sf::Vector2f(0, bottomBoardLength));
			digitDisplaySprite2.setPosition(sf::Vector2f(21, bottomBoardLength));
			digitDisplaySprite3.setPosition(sf::Vector2f(2 * 21, bottomBoardLength));
			digitDisplayVec.push_back(digitDisplaySprite1);
			digitDisplayVec.push_back(digitDisplaySprite2);
			digitDisplayVec.push_back(digitDisplaySprite3);
		}
		else if (displayedCount / 1000 == 0) {
			int firstDigit = displayedCount / 100;
			int secondDigit = (displayedCount / 10) % 10;
			int thirdDigit = displayedCount % 10;

			createSpriteTexture(firstDigit, digitDisplaySprite1);
			createSpriteTexture(secondDigit, digitDisplaySprite2);
			createSpriteTexture(thirdDigit, digitDisplaySprite3);

			digitDisplaySprite1.setPosition(sf::Vector2f(0, bottomBoardLength));
			digitDisplaySprite2.setPosition(sf::Vector2f(21, bottomBoardLength));
			digitDisplaySprite3.setPosition(sf::Vector2f(2 * 21, bottomBoardLength));
			digitDisplayVec.push_back(digitDisplaySprite1);
			digitDisplayVec.push_back(digitDisplaySprite2);
			digitDisplayVec.push_back(digitDisplaySprite3);
		}
	}
	else if (displayedCount < 0) {
		displayedCount *= (-1);
		digitDisplaySprite1.setTexture(textureManager::GetTexture("digit-"));
		digitDisplaySprite1.setPosition(sf::Vector2f(0, bottomBoardLength));
		digitDisplayVec.push_back(digitDisplaySprite1);
		if (displayedCount / 10 == 0) {
			int firstDigit = displayedCount;
			string digitFirst = "digit";
			digitFirst += std::to_string(firstDigit);

			digitDisplaySprite2.setTexture(textureManager::GetTexture("digit0"));
			digitDisplaySprite3.setTexture(textureManager::GetTexture("digit0"));
			createSpriteTexture(firstDigit, digitDisplaySprite4);

			digitDisplaySprite2.setPosition(sf::Vector2f(21, bottomBoardLength));
			digitDisplaySprite3.setPosition(sf::Vector2f(2 * 21, bottomBoardLength));
			digitDisplaySprite4.setPosition(sf::Vector2f(3 * 21, bottomBoardLength));
			digitDisplayVec.push_back(digitDisplaySprite2);
			digitDisplayVec.push_back(digitDisplaySprite3);
			digitDisplayVec.push_back(digitDisplaySprite4);
		}
		else if (displayedCount / 100 == 0) {
			int firstDigit = displayedCount / 10;
			int secondDigit = displayedCount % 10;


			digitDisplaySprite2.setTexture(textureManager::GetTexture("digit0"));
			createSpriteTexture(firstDigit, digitDisplaySprite3);
			createSpriteTexture(secondDigit, digitDisplaySprite4);

			digitDisplaySprite2.setPosition(sf::Vector2f(21, bottomBoardLength));
			digitDisplaySprite3.setPosition(sf::Vector2f(2 * 21, bottomBoardLength));
			digitDisplaySprite4.setPosition(sf::Vector2f(3 * 21, bottomBoardLength));
			digitDisplayVec.push_back(digitDisplaySprite2);
			digitDisplayVec.push_back(digitDisplaySprite3);
			digitDisplayVec.push_back(digitDisplaySprite4);
		}
		else if (displayedCount / 1000 == 0) {
			int firstDigit = displayedCount / 100;
			int secondDigit = (displayedCount / 10) % 10;
			int thirdDigit = displayedCount % 10;

			createSpriteTexture(firstDigit, digitDisplaySprite2);
			createSpriteTexture(secondDigit, digitDisplaySprite3);
			createSpriteTexture(thirdDigit, digitDisplaySprite4);

			digitDisplaySprite2.setPosition(sf::Vector2f(21, bottomBoardLength));
			digitDisplaySprite3.setPosition(sf::Vector2f(2 * 21, bottomBoardLength));
			digitDisplaySprite4.setPosition(sf::Vector2f(3 * 21, bottomBoardLength));
			digitDisplayVec.push_back(digitDisplaySprite2);
			digitDisplayVec.push_back(digitDisplaySprite3);
			digitDisplayVec.push_back(digitDisplaySprite4);
		}
	}
}

//depending on the number passed in, set a particular texture to the sprite that was passed in (for digit display)
void UI::createSpriteTexture(int digitNum, sf::Sprite& referenceSprite) {

	if (digitNum == 0) {
		referenceSprite.setTexture(textureManager::GetTexture("digit0"));
	}
	else if (digitNum == 1) {
		referenceSprite.setTexture(textureManager::GetTexture("digit1"));
	}
	else if (digitNum == 2) {
		referenceSprite.setTexture(textureManager::GetTexture("digit2"));
	}
	else if (digitNum == 3) {
		referenceSprite.setTexture(textureManager::GetTexture("digit3"));
	}
	else if (digitNum == 4) {
		referenceSprite.setTexture(textureManager::GetTexture("digit4"));
	}
	else if (digitNum == 5) {
		referenceSprite.setTexture(textureManager::GetTexture("digit5"));
	}
	else if (digitNum == 6) {
		referenceSprite.setTexture(textureManager::GetTexture("digit6"));
	}
	else if (digitNum == 7) {
		referenceSprite.setTexture(textureManager::GetTexture("digit7"));
	}
	else if (digitNum == 8) {
		referenceSprite.setTexture(textureManager::GetTexture("digit8"));
	}
	else if (digitNum == 9) {
		referenceSprite.setTexture(textureManager::GetTexture("digit9"));
	}
}

//draws the number of display digit sprites in the vector (will be 3 or 4)
//draws the entire user interface as well as the white rectange that covers the excess parts of the digit display
void UI::drawUI(sf::RenderWindow& window) {
	
	for (unsigned int i = 0; i < digitDisplayVec.size(); i++) {
		window.draw(digitDisplayVec[i]);
	}
	window.draw(debugButtonSprite);
	window.draw(faceDisplaySprite);
	window.draw(testButton1Sprite);
	window.draw(testButton2Sprite);
	window.draw(testButton3Sprite);

	sf::RectangleShape rectangleWhite(sf::Vector2f((21 * 10), 32));
	rectangleWhite.setFillColor(sf::Color::White);
	rectangleWhite.setPosition(sf::Vector2f((4 * 21), textureManager::GetTexture("tile_hidden").getSize().y * 16));
	window.draw(rectangleWhite);
	
}
