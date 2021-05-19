#include "Tile.h"



//constructor that sets all bools to default value and sets background and foreground to be completely unaffected tiles
Tile::Tile() {
	hasMine = false;
	foregroundFlag = false;
	foregroundUnrevealedTile = true;
	containedSpriteNumber = false;
	containedSpriteRevealed = false;
	containedFlag = false;
	adjacentBombNumber = 0;

	mineRevealed = false;
	activateRecursiveReveal = false;
	revealedByRecursivReveal = false;

	backgroundSprite.setTexture(textureManager::GetTexture("tile_revealed"));
	foregroundSprite.setTexture(textureManager::GetTexture("tile_hidden"));
	
}

//function called in board class to updata a tile if a mouse event occurs within it
void Tile::updateTileSprites(sf::Event& mouseEvent, bool debugModeStatus) {

	//for left clicks
	//if has mine, then lose, if empty tile then activate recursive reveal, if nothing then reveal the contained sprite
	if (foregroundUnrevealedTile && mouseEvent.mouseButton.button == sf::Mouse::Left) {

		if (hasMine) {
			mineRevealed = true;
			foregroundSprite.setTexture(textureManager::GetTexture("mine"));
			foregroundUnrevealedTile = false;
		}
		else if (containedSpriteRevealed) {
			foregroundSprite = containedSprite;
			foregroundUnrevealedTile = false;
			activateRecursiveReveal = true;
		}
		else {
			foregroundSprite = containedSprite;
			foregroundUnrevealedTile = false;
		}
	}
	//for right clicks
	//appropriately changes the tile to and from flags on foreground depending on the state of the debug mode
	else if (foregroundUnrevealedTile && mouseEvent.mouseButton.button == sf::Mouse::Right) {
		foregroundSprite.setTexture(textureManager::GetTexture("flag"));
		backgroundSprite.setTexture(textureManager::GetTexture("tile_hidden"));
		foregroundUnrevealedTile = false;
		foregroundFlag = true;
	}
	else if (debugModeStatus && containedFlag && mouseEvent.mouseButton.button == sf::Mouse::Right) {
		foregroundSprite.setTexture(textureManager::GetTexture("flag"));
		backgroundSprite.setTexture(textureManager::GetTexture("tile_revealed"));
	}
	else if (foregroundFlag && mouseEvent.mouseButton.button == sf::Mouse::Right) {
		if (!debugModeStatus) {
			foregroundSprite.setTexture(textureManager::GetTexture("tile_hidden"));
			backgroundSprite.setTexture(textureManager::GetTexture("tile_revealed"));
			foregroundFlag = false;
			foregroundUnrevealedTile = true;
		}
		else if (debugModeStatus && hasMine) {
			foregroundSprite.setTexture(textureManager::GetTexture("mine"));
			backgroundSprite.setTexture(textureManager::GetTexture("tile_hidden"));
			foregroundFlag = false;
			foregroundUnrevealedTile = true;
		}
		else {
			foregroundSprite.setTexture(textureManager::GetTexture("tile_hidden"));
			backgroundSprite.setTexture(textureManager::GetTexture("tile_revealed"));
			foregroundFlag = false;
			foregroundUnrevealedTile = true;
		}
	}
}
