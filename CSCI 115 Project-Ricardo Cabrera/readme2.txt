//Ricardo Cabrera
//CSCI 115
//2D Game Project


//This project contains a 2D turn based game created using a MapMatrix class, Adjacency List Class, Prioirty Queue Class, and a Character class
//The project is split into 3 different files
//You will find the class definitions in the "CSCI 115 2D GameVer2.h" file.
//The class implementations are in the "CSCI 115 2D GameVer2.cpp" file.
//The main game can be found in the "CSCI 115 2D GameMain.cpp" file.

//I have included a ".docx" file that explains how the game works and the basic gameplay loop.

//I have also included 5 ".txt" files that represent the maps used in the game.
//The map names are: "2D Game Map1.txt", "2d Game Map2.txt", "2D Game Map3.txt", "2D Game TestingMap1.txt", and "2D Game Testing Map2.txt".

//Gameplay:
-The objective of the game is to survive
-If an enemy touches you, then the map restarts

//Controls:
-Use WASD to move your character (W is up, A is left, S is down, and D is right)
-Press and enter space to skip your turn
-Press and enter q to exit the game

//There are 2 character types in this game:
-Player
-Enemy

-The 3 enemies are called Grey, Sniper, and Hal
-Only thier names are special, and they do not differ in their movement

//Tile or Cell types:
' ' an empty space corresponds to an empty floor tile
'-' a dash represents a grass tile, it will cost enemies longer to move through these tiles
'#' this represents a wall, the player or enenemy cannot move throught them
'H' this is a hidden tile, the player can move on it to become hidden, the enemies cannot move or see through these tiles
'X' this represents an enemy
'O' this is you the player

//There are 3 status types that a player can have:
-Exposed: This means that the player is not hidden and can be spotted by an enemy 
-Spotted: This means that the player is spotted and an enemy is pursuing them
-Hidden: This means that the player is hidden and protected from enemies

//There are 2 status types that an enemy can have:
-Patrolling: This means that the enemy is not actively seeking the player and will perform a random action this turn
-Pursuing: This means that an enemy is actively going after the player
