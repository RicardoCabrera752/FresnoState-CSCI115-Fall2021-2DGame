// Ricardo Cabrera
// CSCI 115
// Project
// 2D Game Using Shortest-Paths



#include<iostream>
#include<fstream>
#include<sstream>
#include<ctime>
#include<string>
#include<utility>
#include<vector>
#include<algorithm>
#include<queue>
#include "CSCI 115 2D GameVer2.h"

using namespace std;





//Main
int main(void) {

	srand(time(0));

	int userMapSelection;
	string userInput;
	bool gameOver;
	bool playerHasQuit;


	cout << "2D Turn Based Game using Dijkstra Shortest-Paths Algorithmn" << endl;
	cout << "**************************************************************************" << endl;
	cout << "The map choices are 1, 2, 3, 4, or 5" << endl;
	cout << "Select a map to play (Press and Enter a number from 1 through 5): ";
	cin >> userMapSelection;
	cin.ignore();
	cout << endl;

	//Creating the game map
	string mapName = getMapName(userMapSelection);

	MapMatrix* gameMap = new MapMatrix(mapName);

	int** vertexNumberArr;
	initializeVertexNumberArr(vertexNumberArr, gameMap);

	//Creating the game characters
	Character* player = new Character('O', "Player");
	Character* grey = new Character('X', "Grey");
	Character* sniper = new Character('X', "Sniper");
	Character* hal = new Character('X', "Hal");

	//Setting the starting positions of the characters
	initializeStartingPositions(userMapSelection, vertexNumberArr, player, grey, sniper, hal);
	player->setCharacterVertexPosition(vertexNumberArr[player->getCharacterPosition().first][player->getCharacterPosition().second]);
	grey->setCharacterVertexPosition(vertexNumberArr[grey->getCharacterPosition().first][grey->getCharacterPosition().second]);
	sniper->setCharacterVertexPosition(vertexNumberArr[sniper->getCharacterPosition().first][sniper->getCharacterPosition().second]);
	hal->setCharacterVertexPosition(vertexNumberArr[hal->getCharacterPosition().first][hal->getCharacterPosition().second]);

	int mapNumOfVerticies = gameMap->getNumOfRows() * gameMap->getNumOfColumns();

	//Creating the graph for the map
	GraphAL* gameMapAL = new GraphAL(mapNumOfVerticies);
	gameMapAL->createALGraphFromMap(gameMap, vertexNumberArr);

	//Starting the game
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	system("cls");

	do {

		gameMap->resetMap(mapName);
		player->resetCharacterPosition();
		grey->resetCharacterPosition();
		sniper->resetCharacterPosition();
		hal->resetCharacterPosition();
		gameOver = false;
		playerHasQuit = false;


		do {


			cout << "Objective: Avoid all enemies for as long as you can" << endl;
			cout << "Controls: Use WASD to move (W is up, A is left, S is down, and D is right)" << endl;
			cout << "Press and enter space to skip your turn, press and enter q to exit the game" << endl;

			gameMap->displayMap();
			//gameMapAL->displayAdjacencyList();

			//int* piArr;
			//double* dArr;

			//gameMapAL->dijkstraBenchmarkVersion(player->getCharacterVertexPosition(), dArr, piArr);
			//dijkstraDisplayShortestPath(dArr, piArr, gameMapAL->getNumberOfVertices());

			//Showing t useful information about the player and enemies
			player->displayCharacterInfo();
			cout << endl;
			grey->displayCharacterInfo();
			cout << endl;
			sniper->displayCharacterInfo();
			cout << endl;
			hal->displayCharacterInfo();
			cout << endl;


			//Player Turn Start
			cout << "Player Turn (Pres and Enter a Key): ";
			//cin >> userInput;
			getline(cin, userInput);
			//cin.ignore();


			//Checking to see if the player has been spotted
			grey->checkIfPlayerSpotted(player, gameMap);
			sniper->checkIfPlayerSpotted(player, gameMap);
			hal->checkIfPlayerSpotted(player, gameMap);
			player->playerMove(userInput, gameMap, vertexNumberArr);
			player->checkIfHidden(grey, sniper, hal);


			//Enemy Turn Start
			grey->enemyMove(gameMap, vertexNumberArr, player, gameMapAL);
			sniper->enemyMove(gameMap, vertexNumberArr, player, gameMapAL);
			hal->enemyMove(gameMap, vertexNumberArr, player, gameMapAL);

			//Checking to see if the player has been caught or has quit the game
			gameOver = player->isGameOver(gameMap);
			playerHasQuit = player->checkIfQuit(userInput);

			system("cls");


		} while ((!gameOver) && (!playerHasQuit));







	} while (!playerHasQuit);






	cout << "/////////////////////////////////////////////////////////////////////////////" << endl;
	//Memory Management
	delete gameMap;
	delete gameMapAL;
	delete player;
	delete grey;
	delete sniper;
	delete hal;
	delete[] vertexNumberArr;

	cout << "Press and Enter 0 to exit the program: ";
	cin.get();
	cin.ignore();

	return 0;
}



