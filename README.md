# MineSweeper
This repository houses code that utilizes the Simple and Fast Multimedia Library (SFML) that creates a fully functioning minesweeper game from scratch.

File explanations (structure):
-random number generator is used to randomly distribute mines on the game board.
-texture manager loads in textures images from the images file.
-tiles are the pieces that comprise the the gameboard. creating separate objects from the board and UI itself make them much easier to work with. This is where the images are applied to the tiles and where image switching during the game occurs on a functional level.
-UI is the next level of abstraction where the tiles are put together to comprise the UI in the size of the gamebaord.
-Board utilizes the UI and functionally is where all user events are processed when the user is playing the game. The board utilizes recursion to efficiently reveal numerous tiles at once (effectively) for if a large chunk of tiles (greater than 1) must be revealed from a particular click by the user. The board files creates a fully functioning minesweeper game that has all of the features and functionality of the original minesweeper game.
-main is the loop that keeps the game running as long as the user keeps the window open.

To run this game, all one has to do is have all included files and images and then run the main in their IDE of choice and the minesweeper window will pop up and be ready for play.

There are also included test boards used to test and check functionality of the program during development.
There is also an additional feature in this minesweeper game, the eye button, which when clicked allows the user to see all of the mines, which significantly aided during development and can allow the user to test and see the full functionality of the program with ease.
