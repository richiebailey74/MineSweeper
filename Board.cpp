#include "Board.h"

//default constructor that initializes the basic board with 50 random mines
//sets member variables that don't change between boards to their default values
Board::Board() : UI() {
	gameWon = false;
	gameLost = false;
	gamePlaying = true;
	debugOn = false;
	flagCount = 0;

	setTilesAndMines();
	setContainedSpritesAndVectors();
}

//resets the board for when the face is clicked
void Board::resetBoard(Board& BoardObj) {
	BoardObj.flagCount = 0;
	BoardObj.mineCount = 0;
	BoardObj.displayedCount = 0;
	BoardObj.gameWon = false;
	BoardObj.gameLost = false;
	BoardObj.gamePlaying = true;
	//turn debug mode off if on
	if (BoardObj.debugOn) {
		turnDebugOff(BoardObj);
		BoardObj.debugOn = false;
	}
	tilesToDefault(BoardObj);
	reassignMines(BoardObj);
	
	//loop assigns the pointer vectors to each tile depending on the surrounding mines
	//changes the contained sprite accordingly (1-8 or empty)
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			int adjacentBombCount = 0;
			adjacentBombCount = resetTilePointerVectors(BoardObj, adjacentBombCount, i, j);
			reassignContainedSprites(BoardObj, adjacentBombCount, i, j);
		}
	}
	//displays the proper number of mines
	BoardObj.displayedCount = BoardObj.mineCount - BoardObj.flagCount;
	BoardObj.faceDisplaySprite.setTexture(textureManager::GetTexture("face_happy"));
	BoardObj.changeDigitDisplay(BoardObj.displayedCount);
}

//same as reset board, except the assignment of mines differs
void Board::changeBoard(Board& BoardObj, std::ifstream& fileObj) {
	BoardObj.flagCount = 0;
	BoardObj.mineCount = 0;
	BoardObj.displayedCount = 0;
	BoardObj.gameWon = false;
	BoardObj.gameLost = false;
	BoardObj.gamePlaying = true;
	if (BoardObj.debugOn) {
		turnDebugOff(BoardObj);
		BoardObj.debugOn = false;
	}
	tilesToDefault(BoardObj);
	setBinaryMineArray(BoardObj, fileObj);
	setFileInputMines(BoardObj);

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			int adjacentBombCount = 0;
			adjacentBombCount = resetTilePointerVectors(BoardObj, adjacentBombCount, i, j);
			reassignContainedSprites(BoardObj, adjacentBombCount, i, j);
		}
	}
	BoardObj.displayedCount = BoardObj.mineCount - BoardObj.flagCount;
	BoardObj.faceDisplaySprite.setTexture(textureManager::GetTexture("face_happy"));
	BoardObj.changeDigitDisplay(BoardObj.displayedCount);
}

//takes in a file object to read and converts each char in the strings to its correlating space in the 2D string array
void Board::setBinaryMineArray(Board& BoardObj, std::ifstream& fileObj) {
	string str;
	BoardObj.stringLines.clear();

	while (std::getline(fileObj, str)) {
		BoardObj.stringLines.push_back(str);
	}

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
				string tempCharString = BoardObj.stringLines[i].substr(0, 1);
				BoardObj.stringLines[i] = BoardObj.stringLines[i].substr(1);
				BoardObj.stringArrBoard[i][j] = tempCharString;
		}
	}
}

//dependent on the 2D string array created from the file object, place mines into all tiles with "1" in its corresponding location
void Board::setFileInputMines(Board& BoardObj) {
	int counter = 0;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {

			if (BoardObj.stringArrBoard[i][j] == "1") {
				BoardObj.tileArray2D[i][j].hasMine = true;

				BoardObj.tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("mine"));
				counter++;
				BoardObj.mineCount = counter;
			}
		}
	}
}

//sets all tiles in the current board object to be completely default and empty
void Board::tilesToDefault(Board& BoardObj) {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {

			BoardObj.tileArray2D[i][j].backgroundSprite.setTexture(textureManager::GetTexture("tile_revealed"));
			BoardObj.tileArray2D[i][j].foregroundSprite.setTexture(textureManager::GetTexture("tile_hidden"));
			BoardObj.tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("tile_revealed"));
			BoardObj.tileArray2D[i][j].hasMine = false;
			BoardObj.tileArray2D[i][j].foregroundFlag = false;
			BoardObj.tileArray2D[i][j].foregroundUnrevealedTile = true;
			BoardObj.tileArray2D[i][j].containedSpriteNumber = false;
			BoardObj.tileArray2D[i][j].containedSpriteRevealed = false;
			BoardObj.tileArray2D[i][j].adjacentBombNumber = 0;
			BoardObj.tileArray2D[i][j].mineRevealed = false;
			BoardObj.tileArray2D[i][j].activateRecursiveReveal = false;
			BoardObj.tileArray2D[i][j].revealedByRecursivReveal = false;
		}
	}
}

//to re-randomize the mines for when the board is reset, this function gets the job done with the random num gen and a while loop
void Board::reassignMines(Board& BoardObj) {
	int counter = 0;
	while (counter < 50) {
		int randomY = RandomNumGen::RandomInt(0, 15);
		int randomX = RandomNumGen::RandomInt(0, 24);

		if (BoardObj.tileArray2D[randomY][randomX].hasMine == false) {
			BoardObj.tileArray2D[randomY][randomX].hasMine = true;
			BoardObj.tileArray2D[randomY][randomX].containedSprite.setTexture(textureManager::GetTexture("mine"));
			counter++;
			BoardObj.mineCount++;
		}
	}
}

//clears the tile pointer vectors so when the board is reset or changed, passed in parameter values can properly dictate the appropriate values to the tiles
int Board::resetTilePointerVectors(Board& BoardObj, int adjacentBombCount, int i, int j) {
	BoardObj.tileArray2D[i][j].adjacentTilePointers.clear();
	BoardObj.tileArray2D[i][j].adjacentBombNumber == 0;
	//if the tile can't point to a specific spot (goes out of bounds on the board) then the tile pointer is never even initialized for the spot (therefore nothing points to nothing)
	if (!BoardObj.tileArray2D[i][j].hasMine) {

		if (i == 0) {
		}
		else {
			Tile* tilePointer1;
			tilePointer1 = &BoardObj.tileArray2D[i - 1][j];
			BoardObj.tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer1);
			if ((*tilePointer1).hasMine) {
				adjacentBombCount++;
				BoardObj.tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (i == 0 || j == 24) {
		}
		else {
			Tile* tilePointer2;
			tilePointer2 = &BoardObj.tileArray2D[i - 1][j + 1];
			BoardObj.tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer2);
			if ((*tilePointer2).hasMine) {
				adjacentBombCount++;
				BoardObj.tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (j == 24) {
		}
		else {
			Tile* tilePointer3;
			tilePointer3 = &BoardObj.tileArray2D[i][j + 1];
			BoardObj.tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer3);
			if ((*tilePointer3).hasMine) {
				adjacentBombCount++;
				BoardObj.tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (i == 15 || j == 24) {
		}
		else {
			Tile* tilePointer4;
			tilePointer4 = &BoardObj.tileArray2D[i + 1][j + 1];
			BoardObj.tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer4);
			if ((*tilePointer4).hasMine) {
				adjacentBombCount++;
				BoardObj.tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (i == 15) {
		}
		else {
			Tile* tilePointer5;
			tilePointer5 = &BoardObj.tileArray2D[i + 1][j];
			BoardObj.tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer5);
			if ((*tilePointer5).hasMine) {
				adjacentBombCount++;
				BoardObj.tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (i == 15 || j == 0) {
		}
		else {
			Tile* tilePointer6;
			tilePointer6 = &BoardObj.tileArray2D[i + 1][j - 1];
			BoardObj.tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer6);
			if ((*tilePointer6).hasMine) {
				adjacentBombCount++;
				BoardObj.tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (j == 0) {
		}
		else {
			Tile* tilePointer7;
			tilePointer7 = &BoardObj.tileArray2D[i][j - 1];
			BoardObj.tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer7);
			if ((*tilePointer7).hasMine) {
				adjacentBombCount++;
				BoardObj.tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (i == 0 || j == 0) {
		}
		else {
			Tile* tilePointer8;
			tilePointer8 = &BoardObj.tileArray2D[i - 1][j - 1];
			BoardObj.tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer8);
			if ((*tilePointer8).hasMine) {
				adjacentBombCount++;
				BoardObj.tileArray2D[i][j].adjacentBombNumber++;
			}
		}

	}
	//returns the count for how many bombs are adjacent to that tile
	return adjacentBombCount;
}

//depending on the adjacent bomb number, appropriately assign contained sprites if no mine exists at the location
void Board::reassignContainedSprites(Board& BoardObj, int adjacentBombCount, int i, int j) {
	if (adjacentBombCount == 1) {
		BoardObj.tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_1"));
		BoardObj.tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 2) {
		BoardObj.tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_2"));
		BoardObj.tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 3) {
		BoardObj.tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_3"));
		BoardObj.tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 4) {
		BoardObj.tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_4"));
		BoardObj.tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 5) {
		BoardObj.tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_5"));
		BoardObj.tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 6) {
		BoardObj.tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_6"));
		BoardObj.tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 7) {
		BoardObj.tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_7"));
		BoardObj.tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 8) {
		BoardObj.tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_8"));
		BoardObj.tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 0 || BoardObj.tileArray2D[i][j].hasMine == false) {
		BoardObj.tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("tile_revealed"));
		BoardObj.tileArray2D[i][j].containedSpriteRevealed = true;
	}
}


//same as above but for default constructor
void Board::setTilesAndMines() {
	int positionX = 0;
	int positionY = 0;
	Tile tempTileObj;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			//moved the temoTileObj from here, no noticeable effects
			tileArray2D[i][j].tilePosition = sf::Vector2i(positionX, positionY);
			tempTileObj.backgroundSprite.setPosition(sf::Vector2f(positionX, positionY));
			tempTileObj.foregroundSprite.setPosition(sf::Vector2f(positionX, positionY));
			tileArray2D[i][j] = tempTileObj;
			positionX += textureManager::GetTexture("tile_hidden").getSize().x;
		}
		positionY += textureManager::GetTexture("tile_hidden").getSize().y;
		positionX = 0;
	}

	randomMineAssignment();
}


//same as above but for default constructor
void Board::randomMineAssignment() {
	int counter = 0;
	while (counter < 50) {
		int randomY = RandomNumGen::RandomInt(0, 15);
		int randomX = RandomNumGen::RandomInt(0, 24);

		if (!tileArray2D[randomY][randomX].hasMine) {
			tileArray2D[randomY][randomX].hasMine = true;
			tileArray2D[randomY][randomX].containedSprite.setTexture(textureManager::GetTexture("mine"));
			tileArray2D[randomY][randomX].containedSprite.setPosition(tileArray2D[randomY][randomX].backgroundSprite.getPosition());
			counter++;
			mineCount = counter;
		}
	}
}

//same as above but for default constructor
void Board::setContainedSpritesAndVectors() {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {

			int adjacentBombCount = 0;
			adjacentBombCount = setMinePointerVectors(adjacentBombCount, i, j);
			setNonMineContainedSprites(adjacentBombCount, i, j);	
		}
	}
	displayedCount = mineCount - flagCount;
}

//same as above but for default constructor
int Board::setMinePointerVectors(int adjacentBombCount, int i, int j) {
	tileArray2D[i][j].adjacentTilePointers.clear();
	tileArray2D[i][j].adjacentBombNumber == 0;
	if (!tileArray2D[i][j].hasMine) {

		if (i == 0) {
		}
		else {
			Tile* tilePointer1;
			tilePointer1 = &tileArray2D[i - 1][j];
			tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer1);
			if ((*tilePointer1).hasMine) {
				adjacentBombCount++;
				tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (i == 0 || j == 24) {
		}
		else {
			Tile* tilePointer2;
			tilePointer2 = &tileArray2D[i - 1][j + 1];
			tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer2);
			if ((*tilePointer2).hasMine) {
				adjacentBombCount++;
				tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (j == 24) {
		}
		else {
			Tile* tilePointer3;
			tilePointer3 = &tileArray2D[i][j + 1];
			tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer3);
			if ((*tilePointer3).hasMine) {
				adjacentBombCount++;
				tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (i == 15 || j == 24) {
		}
		else {
			Tile* tilePointer4;
			tilePointer4 = &tileArray2D[i + 1][j + 1];
			tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer4);
			if ((*tilePointer4).hasMine) {
				adjacentBombCount++;
				tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (i == 15) {
		}
		else {
			Tile* tilePointer5;
			tilePointer5 = &tileArray2D[i + 1][j];
			tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer5);
			if ((*tilePointer5).hasMine) {
				adjacentBombCount++;
				tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (i == 15 || j == 0) {
		}
		else {
			Tile* tilePointer6;
			tilePointer6 = &tileArray2D[i + 1][j - 1];
			tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer6);
			if ((*tilePointer6).hasMine) {
				adjacentBombCount++;
				tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (j == 0) {
		}
		else {
			Tile* tilePointer7;
			tilePointer7 = &tileArray2D[i][j - 1];
			tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer7);
			if ((*tilePointer7).hasMine) {
				adjacentBombCount++;
				tileArray2D[i][j].adjacentBombNumber++;
			}
		}

		if (i == 0 || j == 0) {
		}
		else {
			Tile* tilePointer8;
			tilePointer8 = &tileArray2D[i - 1][j - 1];
			tileArray2D[i][j].adjacentTilePointers.push_back(tilePointer8);
			if ((*tilePointer8).hasMine) {
				adjacentBombCount++;
				tileArray2D[i][j].adjacentBombNumber++;
			}
		}

	}
	return adjacentBombCount;
}

//same as above but for default constructor
void Board::setNonMineContainedSprites(int adjacentBombCount, int i, int j) {
	if (adjacentBombCount == 1) {
		tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_1"));
		tileArray2D[i][j].containedSprite.setPosition(tileArray2D[i][j].backgroundSprite.getPosition());
		tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 2) {
		tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_2"));
		tileArray2D[i][j].containedSprite.setPosition(tileArray2D[i][j].backgroundSprite.getPosition());
		tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 3) {
		tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_3"));
		tileArray2D[i][j].containedSprite.setPosition(tileArray2D[i][j].backgroundSprite.getPosition());
		tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 4) {
		tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_4"));
		tileArray2D[i][j].containedSprite.setPosition(tileArray2D[i][j].backgroundSprite.getPosition());
		tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 5) {
		tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_5"));
		tileArray2D[i][j].containedSprite.setPosition(tileArray2D[i][j].backgroundSprite.getPosition());
		tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 6) {
		tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_6"));
		tileArray2D[i][j].containedSprite.setPosition(tileArray2D[i][j].backgroundSprite.getPosition());
		tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 7) {
		tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_7"));
		tileArray2D[i][j].containedSprite.setPosition(tileArray2D[i][j].backgroundSprite.getPosition());
		tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 8) {
		tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("number_8"));
		tileArray2D[i][j].containedSprite.setPosition(tileArray2D[i][j].backgroundSprite.getPosition());
		tileArray2D[i][j].containedSpriteNumber = true;
	}
	else if (adjacentBombCount == 0 || tileArray2D[i][j].hasMine == false) {
		tileArray2D[i][j].containedSprite.setTexture(textureManager::GetTexture("tile_revealed"));
		tileArray2D[i][j].containedSprite.setPosition(tileArray2D[i][j].backgroundSprite.getPosition());
		tileArray2D[i][j].containedSpriteRevealed = true;
	}
}

//draws the board object that is passed in: all the tiles and it calls the draw UI function from the privately inherited UI object
void Board::drawBoard(sf::RenderWindow& window) {

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {

			window.draw(tileArray2D[i][j].backgroundSprite);
			window.draw(tileArray2D[i][j].foregroundSprite);
		}
	}
	UI::drawUI(window);
}

//called for when a mine is revealed; the rest of the mines surface and the game ends
//interaction with the tiles becomes impossible and only interaction with the UI is possible
void Board::revealAllMines() {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			if (tileArray2D[i][j].hasMine) {
				tileArray2D[i][j].foregroundSprite.setTexture(textureManager::GetTexture("mine"));
				tileArray2D[i][j].foregroundUnrevealedTile = false;
				tileArray2D[i][j].backgroundSprite.setTexture(textureManager::GetTexture("tile_revealed"));
				gamePlaying = false;
				gameLost = true;
			}
		}
	}
	UI::faceDisplaySprite.setTexture(textureManager::GetTexture("face_lose"));
}

//checks UI tiles if the mouse event happened within them
void Board::checkUITiles(sf::Vector2i& mousePos, Board& BoardObj) {

	//activates the complex debug mode: turns off if on and on if off
	if (UI::debugButtonSprite.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
		if (debugOn) {
			turnDebugOff(BoardObj);
			debugOn = false;
		}
		else if (!debugOn) {
			turnDebugOn(BoardObj);
			debugOn = true;
		}
	}
	//resets the board if the facec is clicked at any point
	else if (UI::faceDisplaySprite.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
		resetBoard(BoardObj);
	}
	//loads the first test board to the board object
	else if (UI::testButton1Sprite.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
		std::ifstream board1FileObj("boards/testboard1.brd");
		changeBoard(BoardObj, board1FileObj);
	}
	//loads the second test board to the board object
	else if (UI::testButton2Sprite.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) { 
		std::ifstream board2FileObj("boards/testboard2.brd");
		changeBoard(BoardObj, board2FileObj);
	}
	//loads the third test board to the board object
	else if (UI::testButton3Sprite.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
		std::ifstream board3FileObj("boards/testboard3.brd");
		changeBoard(BoardObj, board3FileObj);
	}
}

//checks the game tiles if the mouse interaction took place within it
void Board::checkMineTiles(sf::Vector2i& mousePos, sf::Event& mouseEvent, Board& BoardObj) {
	//loops through the entire tile board array
	for (int h = 0; h < 16; h++) {
		for (int c = 0; c < 25; c++) {
			if (BoardObj.tileArray2D[h][c].foregroundSprite.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {

				bool debugModeStatus = BoardObj.debugOn;
				//update the tiles sprites and pass in the event
				BoardObj.tileArray2D[h][c].updateTileSprites(mouseEvent, debugModeStatus);
				//call reveal all mines if a mine has been reveaed at all
				if (BoardObj.tileArray2D[h][c].mineRevealed) {
					revealAllMines();
				}
				//activate recursive reveal if an empty tile is revealed
				if (BoardObj.tileArray2D[h][c].activateRecursiveReveal) {
					recursiveReveal(tileArray2D[h][c]);
					BoardObj.tileArray2D[h][c].foregroundUnrevealedTile = false;
					BoardObj.tileArray2D[h][c].activateRecursiveReveal = false;
				}
				//if a contained flag is present then uncontain it (required for changing debug modes)
				if (BoardObj.tileArray2D[h][c].containedFlag == true && mouseEvent.mouseButton.button == sf::Mouse::Right) {
					BoardObj.tileArray2D[h][c].containedFlag = false;
				}
				//if a flag is present only remove it and increment the display count if it is a right click
				else if (BoardObj.tileArray2D[h][c].foregroundFlag == true && mouseEvent.mouseButton.button == sf::Mouse::Right) {
					BoardObj.flagCount++;
					BoardObj.displayedCount = BoardObj.mineCount - BoardObj.flagCount;
					BoardObj.changeDigitDisplay(BoardObj.displayedCount);
				}
				//same as directly above except decrement
				else if (BoardObj.tileArray2D[h][c].foregroundFlag == false && mouseEvent.mouseButton.button == sf::Mouse::Right && BoardObj.tileArray2D[h][c].foregroundUnrevealedTile == true) {
					BoardObj.flagCount--;
					BoardObj.displayedCount = BoardObj.mineCount - BoardObj.flagCount;
					BoardObj.changeDigitDisplay(BoardObj.displayedCount);
				}
			}

		}
	}

	//checks victory
	checkVictory(BoardObj);
	//if the game was won, call the victory function to change the face and make the game tiles un-interactible
	if (BoardObj.gameWon) {
		victory(BoardObj);
	}

}

//checks to see if the number of unrevealed tiles equals the number of mines (how the game is won)
void Board::checkVictory(Board& BoardObj) {
	int tempCount = 0;
		for (int a = 0; a < 16; a++) {
			for (int b = 0; b < 25; b++) {
				//only add to the tempCount if the tile is unrevealed or has a flag on the foreground (also unrevealed)
				if (BoardObj.tileArray2D[a][b].foregroundUnrevealedTile || BoardObj.tileArray2D[a][b].foregroundFlag) {
					
						tempCount++;
				}
			}
		}
	
	//if the number of unrevealed tile equals the number of mines, then the game has been won
	if (tempCount == BoardObj.mineCount) {
		BoardObj.gameWon = true;
	}
}

//sets the game being played to false and changes the face to the sunglasses
void Board::victory(Board& BoardObj) {
	BoardObj.gamePlaying = false;
	BoardObj.faceDisplaySprite.setTexture(textureManager::GetTexture("face_win"));
}

//turns debug mode on by making all the mines visible but the game is still playing
void Board::turnDebugOn(Board& BoardObj) {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			if (tileArray2D[i][j].hasMine && tileArray2D[i][j].foregroundFlag) {
				tileArray2D[i][j].foregroundSprite.setTexture(textureManager::GetTexture("mine"));
				tileArray2D[i][j].backgroundSprite.setTexture(textureManager::GetTexture("tile_hidden"));
				tileArray2D[i][j].containedFlag = true;
			}
			else if (tileArray2D[i][j].hasMine) {
				tileArray2D[i][j].foregroundSprite.setTexture(textureManager::GetTexture("mine"));
				tileArray2D[i][j].backgroundSprite.setTexture(textureManager::GetTexture("tile_hidden"));
			}
		}
	}
}

//takes all the mines and makes them hidden again
void Board::turnDebugOff(Board& BoardObj) {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			if (tileArray2D[i][j].hasMine && tileArray2D[i][j].foregroundFlag) {
				tileArray2D[i][j].foregroundSprite.setTexture(textureManager::GetTexture("flag"));
				tileArray2D[i][j].backgroundSprite.setTexture(textureManager::GetTexture("tile_revealed"));
				tileArray2D[i][j].foregroundFlag = true;
			}
			else if (tileArray2D[i][j].hasMine && tileArray2D[i][j].containedFlag) {
				tileArray2D[i][j].foregroundSprite.setTexture(textureManager::GetTexture("flag"));
				tileArray2D[i][j].backgroundSprite.setTexture(textureManager::GetTexture("tile_revealed"));
				tileArray2D[i][j].containedFlag = true;
			}
			else if (tileArray2D[i][j].hasMine) {
				tileArray2D[i][j].foregroundSprite.setTexture(textureManager::GetTexture("tile_hidden"));
				tileArray2D[i][j].backgroundSprite.setTexture(textureManager::GetTexture("tile_revealed"));
			}
		}
	}
}

//uses recursion to reveal any adjacent tile to the passed in one unless the passed in one has already been revealed by the recursion or there are mines adjacent to it
void Board::recursiveReveal(Tile& currentTile) {
	if (currentTile.adjacentBombNumber > 0 || currentTile.revealedByRecursivReveal == true) {
		
	}
	else {
		for (int k = 0; k < currentTile.adjacentTilePointers.size(); k ++) {
			//uses revealedByRecursiveReveal boolean to ensure there is no overlap in revealing and thus no stack overflow
			currentTile.revealedByRecursivReveal = true;
			if (!currentTile.adjacentTilePointers[k]->revealedByRecursivReveal && !currentTile.adjacentTilePointers[k]->foregroundFlag) {
				currentTile.adjacentTilePointers[k]->foregroundSprite = currentTile.adjacentTilePointers[k]->containedSprite;
				currentTile.adjacentTilePointers[k]->foregroundUnrevealedTile = false;
				recursiveReveal(*currentTile.adjacentTilePointers[k]);
			}
		}
	}
}





