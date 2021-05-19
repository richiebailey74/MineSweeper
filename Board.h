#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "Tile.h"
#include "RandomNumGen.h"
#include "textureManager.h"
#include "UI.h"
#include <iostream>
#include <sstream>
#include <fstream>



class Board : private UI {
private:
	
public:
	Tile tileArray2D[16][25];
	Board();
	//cut stack usage
	//find a way to store the state of the game with events (playing, won, lost)
	bool gameWon;
	bool gameLost;
	bool gamePlaying;
	bool debugOn;

	void drawBoard(sf::RenderWindow& window);
	void revealAllMines();
	void checkUITiles(sf::Vector2i& mousePos, Board& BoardObj);
	void checkMineTiles(sf::Vector2i& mousePos, sf::Event& mouseEvent, Board& BoardObj);
	void turnDebugOn(Board& BoardObj);
	void turnDebugOff(Board& BoardObj);
	void setTilesAndMines();
	void setNonMineContainedSprites(int adjacentBombCount, int i, int j);
	void setContainedSpritesAndVectors();
	int setMinePointerVectors(int adjacentBombCount, int i, int j);
	void setBinaryMineArray(Board& BoardObj, std::ifstream& fileObj);
	void setFileInputMines(Board& BoardObj);
	void resetBoard(Board& BoardObj);
	void changeBoard(Board& BoardObj, std::ifstream& fileObj);
	void randomMineAssignment();
	void tilesToDefault(Board& BoardObj);
	void reassignMines(Board& BoardObj);
	void reassignContainedSprites(Board& BoardObj, int adjacentBombCount, int i, int j);
	int resetTilePointerVectors(Board& BoardObj, int adjacentBombCount, int i, int j);
	void recursiveReveal(Tile& currentTile);
	void checkVictory(Board& BoardObj);
	void victory(Board& BoardObj);

	
	int mineCount;
	int flagCount;
	int displayedCount;
	string stringArrBoard[16][25];
	vector<string> stringLines;
	std::ifstream fileObj;
};

