#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "textureManager.h"
using std::vector;

class Tile {
public:

	Tile();

	sf::Sprite backgroundSprite;
	sf::Sprite foregroundSprite;
	sf::Sprite containedSprite;
	sf::Vector2i tilePosition;

	bool hasMine;
	bool foregroundUnrevealedTile;
	bool foregroundFlag;
	bool containedSpriteNumber;
	bool containedSpriteRevealed;
	bool containedFlag;
	bool mineRevealed;
	bool activateRecursiveReveal;
	bool revealedByRecursivReveal;
	int adjacentBombNumber;
	vector<Tile*> adjacentTilePointers;

	void updateTileSprites(sf::Event& mouseEvent, bool debugModeStatus);


};

