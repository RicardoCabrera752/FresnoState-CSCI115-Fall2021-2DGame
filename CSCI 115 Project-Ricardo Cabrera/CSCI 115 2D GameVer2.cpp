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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//2D Map Matrix Method Implementations:

//Default constructor that sets the number of rows and number of columns to zero
MapMatrix::MapMatrix() {

	//default map properties
	numOfColumns = 0;
	numOfRows = 0;

	matrix = nullptr;

	//Default starting positions for the player and enemies are off the map
	playerStartingPosition.first = -1;
	playerStartingPosition.second = -1;

	greyStartingPosition.first = -1;
	greyStartingPosition.second = -1;

	sniperStartingPosition.first = -1;
	sniperStartingPosition.second = -1;

	halStartingPosision.first = -1;
	halStartingPosision.second = -1;
}


//Constructor that takes a text file name as an input and creates a map by reading the characters in the file
MapMatrix::MapMatrix(string argFileName) {

	ifstream myFile;
	myFile.open(argFileName);

	//Creating variables that will be used to read the text file and create a map
	int tempNumOfRows = 0;
	int tempNumOfColumns = 0;
	int tempNumOfCells = 0;
	char tempChar;
	string tempString;
	stringstream tempSS;
	myFile >> noskipws;

	getline(myFile, tempString);
	tempSS << tempString;

	//Counting the number of cells the finished 2D map will have
	while (tempSS >> tempChar) {
		tempNumOfCells++;
	}

	tempNumOfColumns = tempNumOfCells;

	while (myFile >> tempChar) {
		tempNumOfCells++;
	}

	//Checking to see if the input text file name corresponds to a text file that exists
	//If tempNumOfColumns is equal to 0 it means that tempNumOfCells is equal to 0, therefore the input text file does not exist
	if (tempNumOfColumns != 0) {

		tempNumOfRows = tempNumOfCells / tempNumOfColumns;
	}
	else {
		cout << "Text File Does Not Exist" << endl;
	}


	//Setting the rows and colums for map that will be created
	numOfColumns = tempNumOfColumns;
	numOfRows = tempNumOfRows;

	myFile.close();


	//Creating the map
	ifstream myFile2;
	myFile2.open(argFileName);

	string line;

	matrix = new char*[numOfRows];

	for (int i = 0; i < numOfRows; i++) {

		getline(myFile2, line);

		matrix[i] = new char[numOfColumns];

		for (int j = 0; j < numOfColumns; j++) {

			matrix[i][j] = line[j];

		}


	}

	myFile2.close();


	//Default starting positions for the player and enemies are off the map
	playerStartingPosition.first = -1;
	playerStartingPosition.second = -1;

	greyStartingPosition.first = -1;
	greyStartingPosition.second = -1;

	sniperStartingPosition.first = -1;
	sniperStartingPosition.second = -1;

	halStartingPosision.first = -1;
	halStartingPosision.second = -1;
}


//Destructor:
MapMatrix::~MapMatrix() {

	delete[] matrix;
}


//Method to get the number of rows in the map
int MapMatrix::getNumOfRows() {

	return numOfRows;
}


//Method to get the number of columns in the map
int MapMatrix::getNumOfColumns() {

	return numOfColumns;
}


//Method to get the char from a given cell in the 2D map
char MapMatrix::getCharAtPosition(int argRow, int argColumn) {

	return matrix[argRow][argColumn];

}


//Method to set the char that is in a given cell in the 2D map
void MapMatrix::setCharAtPosition(int argRow, int argColumn, int argChar) {

	matrix[argRow][argColumn] = argChar;

}


//Testing and debugging version of the method to display the map
void MapMatrix::displayMapTestingVer() {

	int numOfCells = numOfRows * numOfColumns;

	cout << "Displaying Map of Size: " << numOfCells << endl;
	cout << "Number of Rows = " << numOfRows << ", Number of Columns = " << numOfColumns << endl;


	for (int i = 0; i < numOfRows; i++) {

		for (int j = 0; j < numOfColumns; j++) {

			cout << (char)matrix[i][j];


		}

		cout << endl;

	}


}


//Method to display the map
void MapMatrix::displayMap() {


	//cout << "Number of Rows = " << numOfRows << ", Number of Columns = " << numOfColumns << endl;

	for (int i = 0; i < numOfRows; i++) {

		for (int j = 0; j < numOfColumns; j++) {

			cout << (char)matrix[i][j];


		}

		cout << endl;

	}
}


//Method to reset the map to its original state
void MapMatrix::resetMap(string argFileName) {

	//Reseting the map to its original version
	ifstream myFile1;
	myFile1.open(argFileName);

	string line;

	for (int i = 0; i < numOfRows; i++) {

		getline(myFile1, line);


		for (int j = 0; j < numOfColumns; j++) {

			matrix[i][j] = line[j];

		}


	}

	myFile1.close();


}


//Method to set the starting position of the player on the map
void MapMatrix::setPlayerStartingPosition(int argRow, int argColumn) {

	playerStartingPosition.first = argRow; //setting the row value of the staring position
	playerStartingPosition.second = argColumn; //setting the column value of the starting position


}


//Method to get the row and column of the player's starting position
pair<int, int> MapMatrix::getPlayerStartingPosition() {

	return playerStartingPosition;
}


//Method to set the starting position of specific enemy on the map
void MapMatrix::setEnemyStartingPosition(int argRow, int argColumn, string argName) {

	if (argName == "Grey") {

		greyStartingPosition.first = argRow;
		greyStartingPosition.second = argColumn;

	}
	else if (argName == "Sniper") {

		sniperStartingPosition.first = argRow;
		sniperStartingPosition.second = argColumn;
	}
	else {
		halStartingPosision.first = argRow;
		halStartingPosision.second = argColumn;
	}

}


//Method to get the row and column of a specific enemy's starting position
pair<int, int> MapMatrix::getEnemyStartingPosition(string argName) {


	if (argName == "Grey") {

		return greyStartingPosition;

	}
	else if (argName == "Sniper") {

		return sniperStartingPosition;
	}
	else {
		return halStartingPosision;
	}

}


//Function to get the name of the map that the user has selected
string getMapName(int argMapNumber) {

	if (argMapNumber == 1) {
		return "2D Game TestingMap1.txt";
	}

	if (argMapNumber == 2) {
		return "2D Game TestingMap2.txt";
	}

	if (argMapNumber == 3) {
		return "2D Game Map1.txt";
	}

	if (argMapNumber == 4) {
		return "2D Game Map2.txt";
	}

	if (argMapNumber == 5) {
		return "2D Game Map3.txt";
	}


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Adjacency List Graph Node Method Implementations:

//Default constructor
ALNode::ALNode() {

	vertex = 0;
	weight = 0;
	next = nullptr;
}


//Constructor that takes a vertex and an edge weight as inputs
ALNode::ALNode(int argVertex, double argWeight) {

	vertex = argVertex;
	weight = argWeight;
	next = nullptr;
}


//Destructor:
ALNode::~ALNode() {

}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Adjacency List Graph Method Implementations:

//Default constructor
GraphAL::GraphAL() {

	numOfVert = 0;
	listArr = nullptr;
	current = nullptr;

}


//Constructor that takes in a given number of vertices as an input
GraphAL::GraphAL(int argNumOfVert) {

	numOfVert = argNumOfVert;

	listArr = new ALNode*[argNumOfVert];
	current = new ALNode*[argNumOfVert];

	for (int i = 0; i < numOfVert; i++) {

		listArr[i] = nullptr;
		current[i] = nullptr;

	}

}


//Destructor:
GraphAL::~GraphAL() {

	//Memory Management
	for (int i = 0; i < numOfVert; i++) {

		ALNode* tempCurrent = listArr[i];


		while (tempCurrent != nullptr) {

			ALNode* tempNext = tempCurrent->next;
			delete tempCurrent;
			tempCurrent = tempNext;


		}


	}

	delete[] listArr;
	delete[] current;


}


//Method to add a weighted directed edge between two given verticies in the adjacency list
void GraphAL::addDirectedEdge(int argVertex1, int argVertex2, double argWeight) {

	//Checking to see if the edge that will be added already exists in the graph
	if (!edgeExists(argVertex1, argVertex2)) {
		ALNode* temp = new ALNode(argVertex2, argWeight);

		temp->next = listArr[argVertex1];
		listArr[argVertex1] = temp;
	}

}


//Method to add a weighted undirected edge between two given verticies in the adjacency list
void GraphAL::addUndirectedEdge(int argVertex1, int argVertex2, double argWeight) {

	//Checking to see if the edges that will be added already exist in the graph
	if (!edgeExists(argVertex1, argVertex2)) {

		ALNode* temp = new ALNode(argVertex2, argWeight);

		temp->next = listArr[argVertex1];
		listArr[argVertex1] = temp;

	}

	if (!edgeExists(argVertex2, argVertex1)) {

		ALNode* temp = new ALNode(argVertex1, argWeight);
		temp->next = listArr[argVertex2];
		listArr[argVertex2] = temp;

	}

}


//Method to check if there is an edge between two verticies
bool GraphAL::edgeExists(int argVertex1, int argVertex2) {

	if (argVertex1 < numOfVert) {

		ALNode* temp = listArr[argVertex1];

		while (temp != nullptr) {

			//If temp->vertex is equal to argVertex2, then the edge already exists in the graph
			if (temp->vertex == argVertex2) {
				return true;
			}
			else {
				temp = temp->next;
			}

		}

		//Edge doesn't exist
		return false;


	}
	else {

		return false;
	}

}


//Method to display the adjacency list for testing and debugging
void GraphAL::displayAdjacencyList() {

	for (int i = 0; i < numOfVert; i++) {

		cout << "Vertex " << i << " ==> ";

		ALNode* temp = listArr[i];
		while (temp != nullptr) {

			cout << "Vertex: " << temp->vertex << ", Weight: " << temp->weight << " ==> ";
			temp = temp->next;

		}
		cout << endl;

	}

}


//Method to get the number of vertices in the adjacecny list graph
int GraphAL::getNumberOfVertices() {

	return numOfVert;
}


//Method to get the weight of the edge between two vertices
double GraphAL::getEdgeWeight(int argVertex1, int argVertex2) {


	if (argVertex1 < numOfVert) {

		ALNode* temp = listArr[argVertex1];

		//Searching for the edge
		while (temp != nullptr) {

			if (temp->vertex == argVertex2) {

				return temp->weight;

			}
			else {

				temp = temp->next;

			}

		}

		return 0;

	}

	return 0;

}


//Method to check if an adjacent vertex exits near a given vertex
bool GraphAL::adjacentVertexExists(int argVertex) {

	return current[argVertex] != nullptr;
}


//Method to set the current vertex you are dealing with
void GraphAL::setCurrentVertex(int argVertex) {

	current[argVertex] = listArr[argVertex];
}


//Method to get the next adjacent vertex for a given vertex
int GraphAL::getNextAdjacentVertex(int argVertex) {

	int vertex = current[argVertex]->vertex;
	current[argVertex] = current[argVertex]->next;
	return vertex;
}


//Method to create an adjacecny list from a given map
void GraphAL::createALGraphFromMap(MapMatrix* argMap, int** argVertexNumArr) {


	//Getting the rows and columns from the map
	int tempNumOfRows = argMap->getNumOfRows();
	int tempNumOfColumns = argMap->getNumOfColumns();



	//Adding edges to the graph using the map
	for (int i = 0; i < tempNumOfRows; i++) {

		for (int j = 0; j < tempNumOfColumns; j++) {

			addEdgeUsingMap(i, j, argVertexNumArr, argMap);


		}

	}



}


//Method to get the weight for an edge by using the character in a cell
double GraphAL::getWeightFromMap(int argRow, int argColumn, MapMatrix* argMap) {

	char cellType = argMap->getCharAtPosition(argRow, argColumn);

	if (cellType == '-') {

		return 2.0;
	}
	else {
		return 1.0;
	}


}


//Method to add an edge to the adjacency list graph by checking in four directions to see if an edge can be made
void GraphAL::addEdgeUsingMap(int argIndex1, int argIndex2, int** argVertexNumArr, MapMatrix* argMap) {

	int nRows = argMap->getNumOfRows();
	int nColumns = argMap->getNumOfColumns();

	//Checking to see if the char in cell is a wall, if not then check in all 4 directions to see if any edges can be made
	if (argMap->getCharAtPosition(argIndex1, argIndex2) == ' ' || argMap->getCharAtPosition(argIndex1, argIndex2) == '-' || argMap->getCharAtPosition(argIndex1, argIndex2) == 'O' || argMap->getCharAtPosition(argIndex1, argIndex2) == 'X') {
		double edgeWeight = getWeightFromMap(argIndex1, argIndex2, argMap);

		//Check up to see if any edge can be made
		if (argIndex1 >= 0 && argIndex2 < nColumns) {
			if ((argMap->getCharAtPosition(argIndex1 - 1, argIndex2) != '#') && (argMap->getCharAtPosition(argIndex1 - 1, argIndex2) != 'H')) {

				addDirectedEdge(argVertexNumArr[argIndex1][argIndex2], argVertexNumArr[argIndex1 - 1][argIndex2], edgeWeight);

			}
		}


		//Checking to the left to see if any edge can be made
		if (argIndex1 < nRows && argIndex2 >= 0) {

			if ((argMap->getCharAtPosition(argIndex1, argIndex2 - 1) != '#') && (argMap->getCharAtPosition(argIndex1, argIndex2 - 1) != 'H')) {

				addDirectedEdge(argVertexNumArr[argIndex1][argIndex2], argVertexNumArr[argIndex1][argIndex2 - 1], edgeWeight);

			}

		}


		//Checking down to see if an edge can be made
		if (argIndex1 < nRows && argIndex2 < nColumns) {
			if ((argMap->getCharAtPosition(argIndex1 + 1, argIndex2) != '#') && (argMap->getCharAtPosition(argIndex1 + 1, argIndex2) != 'H')) {

				addDirectedEdge(argVertexNumArr[argIndex1][argIndex2], argVertexNumArr[argIndex1 + 1][argIndex2], edgeWeight);

			}


		}


		//Checking to the right to see if an edge can be made
		if (argIndex1 < nRows && argIndex2 < nColumns) {
			if ((argMap->getCharAtPosition(argIndex1, argIndex2 + 1) != '#') && (argMap->getCharAtPosition(argIndex1, argIndex2 + 1) != 'H')) {

				addDirectedEdge(argVertexNumArr[argIndex1][argIndex2], argVertexNumArr[argIndex1][argIndex2 + 1], edgeWeight);
			}

		}


	}



	/*
	//checking to see if the char in cell is a wall, if not then check in all 4 directions to see if any edges can be made
	if ((argMap->getCharAtPosition(argIndex1, argIndex2) != '#') && (argMap->getCharAtPosition(argIndex1, argIndex2) != 'H')) {

		double edgeWeight = getWeightFromMap(argIndex1, argIndex2, argMap);

		if ((argIndex1 >= 0 && argIndex1 < argMap->getNumOfRows()) && (argIndex2 >= 0 && argIndex2 < argMap->getNumOfColumns())) {
			//checking up to see if an edge can be made
			if ((argMap->getCharAtPosition(argIndex1 - 1, argIndex2) != '#') && (argMap->getCharAtPosition(argIndex1 - 1, argIndex2) != 'H')) {

				addDirectedEdge(argVertexNumArr[argIndex1][argIndex2], argVertexNumArr[argIndex1 - 1][argIndex2], edgeWeight);

			}

			//checking down to see if an edge can be made
			if ((argMap->getCharAtPosition(argIndex1 + 1, argIndex2) != '#') && (argMap->getCharAtPosition(argIndex1 + 1, argIndex2) != 'H')) {

				addDirectedEdge(argVertexNumArr[argIndex1][argIndex2], argVertexNumArr[argIndex1 + 1][argIndex2], edgeWeight);

			}

			//checking left to see if an edge can be made
			if ((argMap->getCharAtPosition(argIndex1, argIndex2 - 1) != '#') && (argMap->getCharAtPosition(argIndex1, argIndex2 - 1) != 'H')) {

				addDirectedEdge(argVertexNumArr[argIndex1][argIndex2], argVertexNumArr[argIndex1][argIndex2 - 1], edgeWeight);

			}

			//checking right to see if an edge can be made
			if ((argMap->getCharAtPosition(argIndex1, argIndex2 + 1) != '#') && (argMap->getCharAtPosition(argIndex1, argIndex2 + 1) != 'H')) {

				addDirectedEdge(argVertexNumArr[argIndex1][argIndex2], argVertexNumArr[argIndex1][argIndex2 + 1], edgeWeight);
			}



		}





	}
	*/


}


//Method for the Dijkstra Shortest-Path algorithm
void GraphAL::dijkstra(int sourceVertex, double* &argDistance, int* & argPi) {


	//Initializing for Single Source
	argDistance = new double[numOfVert];
	argPi = new int[numOfVert];

	MinPriorityQueue* tempPQ = new MinPriorityQueue(numOfVert);
	queue<int> tempQueue;

	for (int i = 0; i < numOfVert; i++) {

		argDistance[i] = DBL_MAX;
		argPi[i] = -1;

	}

	//Setting values for source vertex
	argDistance[sourceVertex] = 0;
	argPi[sourceVertex] = -1;

	//Inserting the verticies into the priority queue
	for (int i = 0; i < numOfVert; i++) {
		tempPQ->push(i, argDistance[i]);
	}


	while (!tempPQ->isEmpty()) {

		//Extracting smallest element
		minPQData i = tempPQ->pop();

		//Inserting extracted element into a finished queue
		tempQueue.push(i.index);

		//Index of current vertex
		int u = i.index;
		setCurrentVertex(u);

		//Checking to see if any adjacent vertices exist
		while (adjacentVertexExists(u)) {

			int v = getNextAdjacentVertex(u);

			double weight = getEdgeWeight(u, v);

			if (argDistance[v] > argDistance[u] + weight) {
				//Relaxing the Edge
				argDistance[v] = argDistance[u] + weight;
				argPi[v] = u;
				tempPQ->decreaseKey(v, argDistance[v]);

			}


		}

	}

	delete tempPQ;

}



//Method for Dijkstra Shortes-Path algorithm used for testing and debugging
void GraphAL::dijkstraBenchmarkVersion(int sourceVertex, double* &argDistance, int* &argPi) {

	argDistance = new double[numOfVert];
	argPi = new int[numOfVert];

	MinPriorityQueue* tempPQ = new MinPriorityQueue(numOfVert);
	queue<int> tempQueue;

	for (int i = 0; i < numOfVert; i++) {

		argDistance[i] = DBL_MAX;
		argPi[i] = -1;

	}

	argDistance[sourceVertex] = 0;
	argPi[sourceVertex] = -1;

	for (int i = 0; i < numOfVert; i++) {
		tempPQ->push(i, argDistance[i]);
	}



	while (!tempPQ->isEmpty()) {

		minPQData i = tempPQ->pop();

		tempQueue.push(i.index);

		int u = i.index;



		for (int v = 0; v < numOfVert; v++) {
			if (edgeExists(u, v)) {

				double weight = getEdgeWeight(u, v);


				if (argDistance[v] > argDistance[u] + weight) {

					argDistance[v] = argDistance[u] + weight;
					argPi[v] = u;
					tempPQ->decreaseKey(v, argDistance[v]);

				}


			}

		}


	}


	delete tempPQ;



}


//Function to display the results of the Dijkstra algorithm for testing and debugging
void dijkstraDisplayShortestPath(double* argDistance, int* argPi, int argSize) {

	for (int i = 0; i < argSize; i++) {
		cout << "Vertex: " << i << ", Distance = " << argDistance[i] << ", Pi = " << argPi[i] << endl;
	}

	cout << endl;


}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Character Class Method Implementations:

//Default Constructor
Character::Character() {

	//Default character type is T-pose
	characterType = 'T';
	currentCellType = ' ';
	name = "Placeholder";

	//Default starting positions for the player and enemies are off the map
	startingPosition.first = -1;
	startingPosition.second = -1;

	currentMapPosition.first = -1;
	currentMapPosition.second = -1;

	startingVertexPosition = -1;
	startingCellType = ' ';

	vertexPosition = -1;
	nextVertexPosition = -1;
	currentStatus = "Nothing";
	characterEvent = "None";

}


//Constructor that creates a character of a given type and name
Character::Character(char argCharacterType, string argName) {

	characterType = argCharacterType;
	currentCellType = ' ';
	name = argName;

	//Default starting positions for the player and enemies are off the map
	startingPosition.first = -1;
	startingPosition.second = -1;

	currentMapPosition.first = -1;
	currentMapPosition.second = -1;

	startingVertexPosition = -1;
	startingCellType = ' ';

	vertexPosition = -1;
	nextVertexPosition = -1;
	currentStatus = "Nothing";
	characterEvent = "None";

}


//Destructor:
Character::~Character() {

}


//Method to set the starting position of a player or enemy on the map
void Character::setCharacterStartingPosition(int argRow, int argColumn) {

	startingPosition.first = argRow;
	startingPosition.second = argColumn;

	currentMapPosition.first = argRow;
	currentMapPosition.second = argColumn;

}


//Method to set a character's current position on the map
void Character::setCharacterPosition(int argRow, int argColumn) {

	currentMapPosition.first = argRow;
	currentMapPosition.second = argColumn;

}


//Method to get row and column values for a character's current position on the map
pair<int, int> Character::getCharacterPosition() {

	return currentMapPosition;
}


//Method to set the number of the vertex that corresponds to where the character is on the map
void Character::setCharacterVertexPosition(int argVertexNum) {

	vertexPosition = argVertexNum;

}


//Method to get the vertex number that corresponds to where the character is
int Character::getCharacterVertexPosition() {

	return vertexPosition;
}


//Method to set the current status for a character
void Character::setStatus(string argStatus) {

	currentStatus = argStatus;
}


//Method to display the information about a character
void Character::displayCharacterInfo() {

	cout << "Character: " << name << ", Staus: " << currentStatus << endl;
	//cout << "Status: " << currentStatus << endl;
	cout << "Current Location: " << "Row " << currentMapPosition.first << ", Column " << currentMapPosition.second << ", Current Vertex: " << vertexPosition << endl;
	//cout << "Current Vertex: " << vertexPosition << endl;
	//cout << "Next Vertex: " << nextVertexPosition << endl;
	cout << "Event: " << characterEvent << endl;

}


//Method to set the name for a character
void Character::setName(string argName) {

	name = argName;

}


//Function to initialize the vertex number array used to hold the vertex numbers in the graph
void initializeVertexNumberArr(int** &vertexNumberArr, MapMatrix* argMap) {

	//Getting the rows and columns from the map
	int tempNumOfRows = argMap->getNumOfRows();
	int tempNumOfColumns = argMap->getNumOfColumns();

	//temporary matrix that holds the number corresponding to a vertex in the adjacency list
	//int** vertexNumberArr;

	vertexNumberArr = new int*[tempNumOfRows];

	for (int i = 0; i < tempNumOfRows; i++) {

		vertexNumberArr[i] = new int[tempNumOfColumns];
	}


	//populating the temporary matrix from numbers starting at 0 to the number of cells minus 1
	//example: a map with 5 rows and 5 colums has 25 cells in total, so the temporary matrix would hold the numbers 0 to 24
	int k = 0;

	for (int i = 0; i < tempNumOfRows; i++) {

		for (int j = 0; j < tempNumOfColumns; j++) {

			vertexNumberArr[i][j] = k;
			k++;


		}

	}


}


//Method to move the player when the user preses a movement key
void Character::playerMove(string argKey, MapMatrix* argMap, int** argVertexNumArr) {

	//Player has chosen to move up
	if (argKey == "w" || argKey == "W") {

		int nextPositionRow = currentMapPosition.first - 1;
		int nextPositionColumn = currentMapPosition.second;


		//Check if the new player position is a wall
		if (!isWall(nextPositionRow, nextPositionColumn, argMap)) {

			//If there is no wall, then the player will move
			characterMove(nextPositionRow, nextPositionColumn, argMap, argVertexNumArr);
			characterEvent = "The player has moved up";

		}
		else {

			//The player has run into a wall and cannot move
			characterEvent = "The player has hit their head against a wall!";

		}

	}


	//Player has chosen to move to the left
	if (argKey == "a" || argKey == "A") {

		int nextPositionRow = currentMapPosition.first;
		int nextPositionColumn = currentMapPosition.second - 1;


		//Check if the new player position is a wall
		if (!isWall(nextPositionRow, nextPositionColumn, argMap)) {

			//If there is no wall, then the player will move
			characterMove(nextPositionRow, nextPositionColumn, argMap, argVertexNumArr);
			characterEvent = "The player has moved to the left";

		}
		else {

			//The player has run into a wall and cannot move
			characterEvent = "The player has hit their head against a wall!";

		}

	}


	//Player has chosen to move down
	if (argKey == "s" || argKey == "S") {

		int nextPositionRow = currentMapPosition.first + 1;
		int nextPositionColumn = currentMapPosition.second;


		//Check if the new player position is a wall
		if (!isWall(nextPositionRow, nextPositionColumn, argMap)) {

			//If there is no wall, then the player will move
			characterMove(nextPositionRow, nextPositionColumn, argMap, argVertexNumArr);
			characterEvent = "The player has moved down";

		}
		else {

			//The player has run into a wall and cannot move
			characterEvent = "The player has hit their head against a wall!";

		}

	}



	//Player has chosen to move to the right
	if (argKey == "d" || argKey == "D") {

		int nextPositionRow = currentMapPosition.first;
		int nextPositionColumn = currentMapPosition.second + 1;


		//Check if the new player position is a wall
		if (!isWall(nextPositionRow, nextPositionColumn, argMap)) {

			//If there is no wall, then the player will move
			characterMove(nextPositionRow, nextPositionColumn, argMap, argVertexNumArr);
			characterEvent = "The player has moved to the right";

		}
		else {

			//The player has run into a wall and cannot move
			characterEvent = "The player has hit their head against a wall!";

		}

	}


	if (argKey == " ") {
		characterEvent = "The player has skipped thier turn";
	}


}


//Method to check if the position that a character wants to move into is a wall
bool Character::isWall(int argRow, int argColumn, MapMatrix* argMap) {

	//Check to see if the character that is moving is a player or enemy
	if (characterType == 'O') {

		if (argMap->getCharAtPosition(argRow, argColumn) == '#') {

			//The position that the character is trying to move in is a wall
			return true;
		}
		else {

			//The character is able to move to the desired position
			return false;
		}
	}
	else {

		if ((argMap->getCharAtPosition(argRow, argColumn) == '#') || (argMap->getCharAtPosition(argRow, argColumn) == 'H')) {

			//The position that the character is trying to move in is a wall
			return true;
		}
		else {

			//The character is able to move to the desired position
			return false;
		}


	}



}


//Method to perform the movement action for a character
void Character::characterMove(int argRow, int argColumn, MapMatrix* &argMap, int** argVertexNumArr) {

	//Saving the row, column, and cell type that the character is currently in
	char previousCellType = currentCellType;
	int previousRow = currentMapPosition.first;
	int previousColumn = currentMapPosition.second;


	//Updating the position of the character
	currentMapPosition.first = argRow;
	currentMapPosition.second = argColumn;

	if (argMap->getCharAtPosition(argRow, argColumn) != 'X') {
		currentCellType = argMap->getCharAtPosition(argRow, argColumn);
		vertexPosition = argVertexNumArr[argRow][argColumn];

		//Updating the map to reflect movement of the character
		argMap->setCharAtPosition(previousRow, previousColumn, previousCellType);
		argMap->setCharAtPosition(argRow, argColumn, characterType);
	}

	/*
	currentCellType = argMap->getCharAtPosition(argRow, argColumn);
	vertexPosition = argVertexNumArr[argRow][argColumn];

	//Updating the map to reflect movement of the character
	argMap->setCharAtPosition(previousRow, previousColumn, previousCellType);
	argMap->setCharAtPosition(argRow, argColumn, characterType);
	*/

	//Checking to see if the player has left a hidden cell type and it now exposed
	if ((previousCellType == 'H') && (currentCellType != 'H')) {

		currentStatus = "Exposed";

	}




}


//Method to check is the player has been caught by an enemy
bool Character::isGameOver(MapMatrix* argMap) {

	char topCellType = argMap->getCharAtPosition(currentMapPosition.first - 1, currentMapPosition.second);
	char leftCellType = argMap->getCharAtPosition(currentMapPosition.first, currentMapPosition.second - 1);
	char bottomCellType = argMap->getCharAtPosition(currentMapPosition.first + 1, currentMapPosition.second);
	char rightCellType = argMap->getCharAtPosition(currentMapPosition.first, currentMapPosition.second + 1);

	//Checking to see if an enemy is next to the player
	if ((topCellType == 'X') || (leftCellType == 'X') || (bottomCellType == 'X') || (rightCellType == 'X') || (currentCellType == 'X')) {


		if (currentStatus != "Hidden") {
			//The player has been caught
			characterEvent = "You have been caught! Game Over!";
			return true;
		}
		else {
			return false;
		}



	}
	else {
		return false;
	}


}


//Function to set the starting positions and starting vertex numbers for all of the characters based on the given map number
void initializeStartingPositions(int argMapNumber, int** argVertexNumberArr, Character* &argPlayer, Character* &argGrey, Character* &argSniper, Character* &argHal) {

	//Map 1
	if (argMapNumber == 1) {

		argPlayer->setCharacterStartingPosition(9, 1);
		argPlayer->setStartingVertexPosition(argVertexNumberArr[9][1]);

		argGrey->setCharacterStartingPosition(1, 2);
		argGrey->setStartingVertexPosition(argVertexNumberArr[1][2]);

		argSniper->setCharacterStartingPosition(7, 24);
		argSniper->setStartingVertexPosition(argVertexNumberArr[7][24]);

		argHal->setCharacterStartingPosition(3, 20);
		argHal->setStartingVertexPosition(argVertexNumberArr[3][20]);


	}


	//Map 2
	if (argMapNumber == 2) {

		argPlayer->setCharacterStartingPosition(7, 1);
		argPlayer->setStartingVertexPosition(argVertexNumberArr[7][1]);

		argGrey->setCharacterStartingPosition(1, 2);
		argGrey->setStartingVertexPosition(argVertexNumberArr[1][2]);

		argSniper->setCharacterStartingPosition(6, 18);
		argSniper->setStartingVertexPosition(argVertexNumberArr[6][18]);

		argHal->setCharacterStartingPosition(3, 15);
		argHal->setStartingVertexPosition(argVertexNumberArr[3][15]);

	}


	//Map 3
	if (argMapNumber == 3) {

		argPlayer->setCharacterStartingPosition(5, 53);
		argPlayer->setStartingVertexPosition(argVertexNumberArr[5][53]);

		argGrey->setCharacterStartingPosition(5, 2);
		argGrey->setStartingVertexPosition(argVertexNumberArr[5][2]);

		argSniper->setCharacterStartingPosition(6, 67);
		argSniper->setStartingVertexPosition(argVertexNumberArr[6][67]);

		argHal->setCharacterStartingPosition(8, 31);
		argHal->setStartingVertexPosition(argVertexNumberArr[8][31]);

	}


	//Map 4
	if (argMapNumber == 4) {

		argPlayer->setCharacterStartingPosition(2, 40);
		argPlayer->setStartingVertexPosition(argVertexNumberArr[2][40]);

		argGrey->setCharacterStartingPosition(5, 7);
		argGrey->setStartingVertexPosition(argVertexNumberArr[5][7]);

		argSniper->setCharacterStartingPosition(4, 72);
		argSniper->setStartingVertexPosition(argVertexNumberArr[4][72]);

		argHal->setCharacterStartingPosition(5, 25);
		argHal->setStartingVertexPosition(argVertexNumberArr[5][25]);

	}


	//Map 5
	if (argMapNumber == 5) {

		argPlayer->setCharacterStartingPosition(4, 36);
		argPlayer->setStartingVertexPosition(argVertexNumberArr[4][36]);

		argGrey->setCharacterStartingPosition(5, 15);
		argGrey->setStartingVertexPosition(argVertexNumberArr[5][15]);

		argSniper->setCharacterStartingPosition(6, 44);
		argSniper->setStartingVertexPosition(argVertexNumberArr[6][44]);

		argHal->setCharacterStartingPosition(3, 64);
		argHal->setStartingVertexPosition(argVertexNumberArr[3][64]);

	}


}


//Method to reset character position to starting position
void Character::resetCharacterPosition() {

	currentMapPosition.first = startingPosition.first;
	currentMapPosition.second = startingPosition.second;

	currentCellType = startingCellType;
	vertexPosition = startingVertexPosition;


	if (characterType == 'O') {

		currentStatus = "Exposed";
	}
	else {
		currentStatus = "Patrolling";
		characterEvent = "None";
	}

}


//Method to set the starting vertex position of a character
void Character::setStartingVertexPosition(int argVertexNumber) {

	startingVertexPosition = argVertexNumber;
}


//Method to check if the player has quit the game
bool Character::checkIfQuit(string argKey) {

	if (argKey == "q" || argKey == "Q") {

		//The player has quit the game
		return true;
	}
	else {
		return false;
	}

}


//Method to check if the player is on a hidden cell type and is now hidden
void Character::checkIfHidden(Character* &argGrey, Character* &argSniper, Character* &argHal) {

	if (currentCellType == 'H') {

		currentStatus = "Hidden";
		argGrey->currentStatus = "Patrolling";
		argSniper->currentStatus = "Patrolling";
		argHal->currentStatus = "Patrolling";

	}

}


//Method to check if tow enenies will collide if they move
bool Character::enemyCollisionExists(int argRow, int argColumn, MapMatrix* argMap) {

	if (argMap->getCharAtPosition(argRow, argColumn) == 'X') {
		return true;
	}
	else {
		return false;
	}

}


//Method to determine what action the enemy character will perform
void Character::enemyMove(MapMatrix* &argMap, int** argVertexNumArr, Character* &argPlayer, GraphAL* argGraph) {

	//Checking to see what the enemy can do

	/*
	if (argPlayer->currentStatus == "Hidden") {

		//The player is currently hidden so the enemy will resume patrolling
		currentStatus = "Patrolling";
		patrolMove(argMap, argVertexNumArr);

	}
	else if (currentStatus == "Pursuing") {
		//The enemy is pursuing the player
		pursueMove(argMap, argVertexNumArr, argPlayer, argGraph);


	}
	else {

		//Enemy cannot see the player and is not already pursing, so the move is patrol
		currentStatus = "Patrolling";
		patrolMove(argMap, argVertexNumArr);

	}
	*/


	//Checking to see what the enemy can do
	if (currentStatus == "Pursuing") {
		//The enemy is pursuing the player
		pursueMove(argMap, argVertexNumArr, argPlayer, argGraph);
	}
	else {

		if (argPlayer->currentStatus == "Hidden") {

			//The player is currently hidden so the enemy will resume patrolling
			currentStatus = "Patrolling";
			patrolMove(argMap, argVertexNumArr);

		}
		else {
			//Enemy cannot see the player and is not already pursing, so the move is patrol
			currentStatus = "Patrolling";
			patrolMove(argMap, argVertexNumArr);
		}


	}



}


//Method to perform a pursue move for an enemy
void Character::pursueMove(MapMatrix* &argMap, int** argVertexNumArr, Character* argPlayer, GraphAL* argGraph) {

	int sourceVertex = argPlayer->vertexPosition;
	double* distanceArr;
	int* piArr;

	argGraph->dijkstra(sourceVertex, distanceArr, piArr);

	//Getting the vertex that corresponds with the next position the enemy will move
	int nextPositionVertex = piArr[vertexPosition];
	nextVertexPosition = piArr[vertexPosition];
	cout << piArr[vertexPosition] << endl;
	cout << nextPositionVertex << endl;

	bool rowAndColumnFound = false;
	int row = currentMapPosition.first;
	int column = currentMapPosition.second;

	int numOfRows = argMap->getNumOfRows();
	int numOfColumns = argMap->getNumOfColumns();

	int i1 = row - 1;
	int i2 = row;
	int i3 = row + 1;
	int i4 = row;

	int j1 = column;
	int j2 = column - 1;
	int j3 = column;
	int j4 = column + 1;


	//Checking to see where the enemy is going to move to:
	//Checking up
	if (nextPositionVertex == argVertexNumArr[i1][j1]) {

		if ((!enemyCollisionExists(i1, j1, argMap)) && (!isWall(i1, j1, argMap))) {

			characterMove(i1, j1, argMap, argVertexNumArr);
			characterEvent = "Moved up";

		}

	}


	//Checking left
	if (nextPositionVertex == argVertexNumArr[i2][j2]) {

		if ((!enemyCollisionExists(i2, j2, argMap)) && (!isWall(i2, j2, argMap))) {

			characterMove(i2, j2, argMap, argVertexNumArr);
			characterEvent = "Moved left";

		}

	}


	//Checking down
	if (nextPositionVertex == argVertexNumArr[i3][j3]) {

		if ((!enemyCollisionExists(i3, j3, argMap)) && (!isWall(i3, j3, argMap))) {

			characterMove(i3, j3, argMap, argVertexNumArr);
			characterEvent = "Moved down";

		}

	}


	//Checking right
	if (nextPositionVertex == argVertexNumArr[i4][j4]) {

		if ((!enemyCollisionExists(i4, j4, argMap)) && (!isWall(i4, j4, argMap))) {

			characterMove(i4, j4, argMap, argVertexNumArr);
			characterEvent = "Moved right";

		}

	}




	//Memory Management
	delete[] distanceArr;
	delete[] piArr;

}


//Method to check if an enemy can see the player
void Character::checkIfPlayerSpotted(Character* &argPlayer, MapMatrix* argMap) {


	int row = currentMapPosition.first;
	int column = currentMapPosition.second;

	int numOfRows = argMap->getNumOfRows();
	int numOfColumns = argMap->getNumOfColumns();

	bool topLineOfSight = true;
	bool leftLineOfSight = true;
	bool bottomLineOfSight = true;
	bool rightLineOfSight = true;

	bool playerSpotted = false;

	int i1 = row;
	int i2 = row;
	int i3 = row;
	int i4 = row;
	int j1 = column;
	int j2 = column;
	int j3 = column;
	int j4 = column;


	//Checking up to see if the enemy has spotted the player
	while ((!playerSpotted) && (topLineOfSight) && (i1 >= 0) && (j1 < numOfColumns)) {

		if (isWall(i1, j1, argMap)) {
			//Line of sight is blocked
			topLineOfSight = false;
		}
		else {

			if (argMap->getCharAtPosition(i1, j1) == 'O') {
				//The player has been spotted
				playerSpotted = true;
				argPlayer->currentStatus = "Spotted";
				currentStatus = "Pursuing";

			}
			else {
				//Keep looking
				i1--;

			}

		}
	}



	//Checking left to see if the enemy has spotted the player
	while ((!playerSpotted) && (leftLineOfSight) && (i2 < numOfRows) && (j2 >= 0)) {

		if (isWall(i2, j2, argMap)) {
			//Line of sight is blocked
			leftLineOfSight = false;
		}
		else {

			if (argMap->getCharAtPosition(i2, j2) == 'O') {
				//The player has been spotted
				playerSpotted = true;
				argPlayer->currentStatus = "Spotted";
				currentStatus = "Pursuing";
			}
			else {
				//Keep looking
				j2--;

			}

		}
	}


	//Checking down to see if the enemy has spotted the player
	while ((!playerSpotted) && (bottomLineOfSight) && (i3 < numOfRows) && (j3 < numOfColumns)) {

		if (isWall(i3, j3, argMap)) {
			//Line of sight is blocked
			bottomLineOfSight = false;
		}
		else {

			if (argMap->getCharAtPosition(i3, j3) == 'O') {
				//The player has been spotted
				playerSpotted = true;
				argPlayer->currentStatus = "Spotted";
				currentStatus = "Pursuing";
			}
			else {
				//Keep looking
				i3++;

			}

		}
	}


	//Checking right to see if the enemy has spotted the player
	while ((!playerSpotted) && (rightLineOfSight) && (i4 < numOfRows) && (j4 < numOfColumns)) {

		if (isWall(i4, j4, argMap)) {
			//Line of sight is blocked
			rightLineOfSight = false;
		}
		else {

			if (argMap->getCharAtPosition(i4, j4) == 'O') {
				//The player has been spotted
				playerSpotted = true;
				argPlayer->currentStatus = "Spotted";
				currentStatus = "Pursuing";
			}
			else {
				//Keep looking
				j4++;

			}

		}
	}



}



//Alternate player spotted method
bool Character::checkIfPlayerSpotted2(Character* &argPlayer, MapMatrix* argMap) {

	int row = currentMapPosition.first;
	int column = currentMapPosition.second;

	int numOfRows = argMap->getNumOfRows();
	int numOfColumns = argMap->getNumOfColumns();

	bool topLineOfSight = true;
	bool leftLineOfSight = true;
	bool bottomLineOfSight = true;
	bool rightLineOfSight = true;

	bool playerSpotted = false;

	int i1 = row;
	int i2 = row;
	int i3 = row;
	int i4 = row;
	int j1 = column;
	int j2 = column;
	int j3 = column;
	int j4 = column;


	//Checking up to see if the enemy has spotted the player
	while ((!playerSpotted) && (topLineOfSight) && (i1 >= 0) && (j1 < numOfColumns)) {

		if (isWall(i1, j1, argMap)) {
			//Line of sight is blocked
			topLineOfSight = false;
		}
		else {

			if (argMap->getCharAtPosition(i1, j1) == 'O') {
				//The player has been spotted
				playerSpotted = true;
				argPlayer->currentStatus = "Spotted";
				currentStatus = "Pursuing";
				return true;

			}
			else {
				//Keep looking
				i1--;

			}

		}
	}



	//Checking left to see if the enemy has spotted the player
	while ((!playerSpotted) && (leftLineOfSight) && (i2 < numOfRows) && (j2 >= 0)) {

		if (isWall(i2, j2, argMap)) {
			//Line of sight is blocked
			leftLineOfSight = false;
		}
		else {

			if (argMap->getCharAtPosition(i2, j2) == 'O') {
				//The player has been spotted
				playerSpotted = true;
				argPlayer->currentStatus = "Spotted";
				currentStatus = "Pursuing";
				return true;
			}
			else {
				//Keep looking
				j2--;

			}

		}
	}


	//Checking down to see if the enemy has spotted the player
	while ((!playerSpotted) && (bottomLineOfSight) && (i3 < numOfRows) && (j3 < numOfColumns)) {

		if (isWall(i3, j3, argMap)) {
			//Line of sight is blocked
			bottomLineOfSight = false;
		}
		else {

			if (argMap->getCharAtPosition(i3, j3) == 'O') {
				//The player has been spotted
				playerSpotted = true;
				argPlayer->currentStatus = "Spotted";
				currentStatus = "Pursuing";
				return true;
			}
			else {
				//Keep looking
				i3++;

			}

		}
	}


	//Checking right to see if the enemy has spotted the player
	while ((!playerSpotted) && (rightLineOfSight) && (i4 < numOfRows) && (j4 < numOfColumns)) {

		if (isWall(i4, j4, argMap)) {
			//Line of sight is blocked
			rightLineOfSight = false;
		}
		else {

			if (argMap->getCharAtPosition(i4, j4) == 'O') {
				//The player has been spotted
				playerSpotted = true;
				argPlayer->currentStatus = "Spotted";
				currentStatus = "Pursuing";
				return true;
			}
			else {
				//Keep looking
				j4++;

			}

		}
	}


	return false;

}


//Method to perform a patrol move for an enemey
void Character::patrolMove(MapMatrix* &argMap, int** argVertexNumArr) {

	int row = currentMapPosition.first;
	int column = currentMapPosition.second;

	vector<string> possibleLocations;

	bool up;
	bool left;
	bool down;
	bool right;
	int sum = 0;

	//Getting the possible move locations
	//Checking up
	if ((isWall(row - 1, column, argMap)) || (enemyCollisionExists(row - 1, column, argMap))) {

		up = false;

	}
	else {
		up = true;
		possibleLocations.push_back("up");
		sum++;
	}

	//Checking left
	if ((isWall(row, column - 1, argMap)) || (enemyCollisionExists(row, column - 1, argMap))) {

		left = false;

	}
	else {
		left = true;
		possibleLocations.push_back("left");
		sum++;
	}

	//Checking down
	if ((isWall(row + 1, column, argMap)) || (enemyCollisionExists(row + 1, column, argMap))) {

		down = false;

	}
	else {
		down = true;
		possibleLocations.push_back("down");
		sum++;
	}


	//Checking right
	if ((isWall(row, column + 1, argMap)) || (enemyCollisionExists(row, column + 1, argMap))) {

		right = false;

	}
	else {
		right = true;
		possibleLocations.push_back("right");
		sum++;
	}



	if (sum == 0) {

		//There is no location to move to
		characterEvent = "Did not move";

	}
	else {

		//Get random location to move to
		int index = rand() % sum;
		string direction = possibleLocations[index];


		if (direction == "up") {
			characterEvent = "Moved up";
			characterMove(row - 1, column, argMap, argVertexNumArr);
		}


		if (direction == "left") {
			characterEvent = "Moved left";
			characterMove(row, column - 1, argMap, argVertexNumArr);
		}


		if (direction == "down") {
			characterEvent = "Moved down";
			characterMove(row + 1, column, argMap, argVertexNumArr);
		}

		if (direction == "right") {
			characterEvent = "Moved right";
			characterMove(row, column + 1, argMap, argVertexNumArr);
		}


	}



}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Min Priority Queue Class Method Implementations:

//Default Constructor
MinPriorityQueue::MinPriorityQueue() {

	capacity = 0;
	numOfElements = 0;
	queue = nullptr;

}


//Constructor that creates a prioirty queue based on a given capacity
MinPriorityQueue::MinPriorityQueue(int argCapacity) {

	capacity = argCapacity;
	numOfElements = 0;
	queue = new minPQData[capacity];
}


//Destructor:
MinPriorityQueue::~MinPriorityQueue() {

	//Memory Management
	delete[] queue;
}


//Min Heapify Method
void MinPriorityQueue::minHeapify(int argIndex, int argSize) {

	int leftChild;
	int rightChild;
	int smallest;

	//Indicies of the child nodes for the node at index argIndex
	leftChild = (2 * argIndex) + 1;
	rightChild = (2 * argIndex) + 2;

	//Index of the smallest element in the priority queue
	smallest = argIndex;


	//Checking to see if the left child node is less than the smallest element
	if ((leftChild < argSize) && (queue[leftChild].value < queue[argIndex].value)) {
		smallest = leftChild;

	}

	//Checking to see if the right child node is less than the smallest element
	if (rightChild < argSize && queue[rightChild].value < queue[smallest].value) {
		smallest = rightChild;

	}

	//Checking to see if the index for the smallest element has changed
	if (smallest != argIndex) {

		//If it has changed then there needs to be a swap in the priority queue
		swap(queue[argIndex], queue[smallest]);
		minHeapify(smallest, argSize);
	}

}


//Method to build a min heap using the elements in the priority queue
void MinPriorityQueue::buildMinHeap() {

	//Build the min heap by traversing right to left starting from the bottom
	for (int i = (numOfElements / 2) - 1; i >= 0; i--) {

		minHeapify(i, numOfElements);

	}
}


//Method to get the current number of elements in the prioruty queue
int MinPriorityQueue::getNumOfElements() {

	return numOfElements;
}


//Method to check if the priority queue is empty
bool MinPriorityQueue::isEmpty() {

	//If the number of elements is equal to 0 then the queue is empty
	return(numOfElements == 0);
}


//Method to check if a priority queue is full
bool MinPriorityQueue::isFull() {

	//If the number of elements is equal to the capacity then the queue is full
	return(numOfElements == capacity);

}


//Method to enqueue an element into the priority queue
void MinPriorityQueue::push(int argIndex, double argValue) {

	//Checking to see if there is enough space to add an element to the priority queue
	if (numOfElements < capacity) {

		//Creating the element that will be added
		minPQData temp;
		temp.index = argIndex;
		temp.value = argValue;


		//Finding the position that the element will be added into
		int i = numOfElements;
		while ((i != 0) && (temp.value < queue[i / 2].value)) {
			queue[i] = queue[i / 2];
			i = i / 2;
		}

		//Adding the element to the priority queue
		queue[i] = temp;
		numOfElements++;


	}
	else {

		//Cannot add any more elements
		cout << "Queue Capacity is Full" << endl;
	}

}


//Method to dequeue an element from the priroity queue
minPQData MinPriorityQueue::pop() {


	if (numOfElements > 0) {

		//Creating a variable to hold the information of the element that will be extracted from the priority queue
		minPQData temp = queue[0];

		//Replacing the element that was removed with the last element in the priority queue
		queue[0] = queue[numOfElements - 1];

		//Re-heapify the priority queue

		numOfElements--;


		for (int i = 0; i < numOfElements; i++) {
			minHeapify(i, numOfElements);
		}

		minHeapify(0, numOfElements);
		//numOfElements--;

		//Output the extracted element
		return temp;


	}
	else {

		//There was nothing to extract from the prioirty queue
		minPQData temp;
		temp.index = -1;
		temp.value = 0;
		return temp;

	}
}


//Method to get the parent node for a given child node in the min heap
int MinPriorityQueue::getParent(int argChild) {

	if (argChild % 2 == 0) {
		//Returning the index of the right child
		return (argChild / 2) - 1;
	}
	else {
		//Returning the index of the left child
		return argChild / 2;
	}

}


//Method to decrease the key for an element in the priority queue
void MinPriorityQueue::decreaseKey(int argIndex, double value) {

	int i = 0;
	bool found = false;

	//Finding the element that will have thier key decreased
	while ((!found) && (i < numOfElements)) {

		if (queue[i].index == argIndex) {

			//The element has been found
			queue[i].value = value;
			found = true;

			//Re-Heapify the Priority Queue
			for (int i = 0; i < numOfElements; i++) {
				minHeapify(i, numOfElements);
			}


		}
		else {
			i++;
		}

	}


	if (found) {

		//Changing the positions of the two elements in front element that was decreased
		int child = i - 1;
		int parent = getParent(child);

		while ((queue[child].value < queue[parent].value) && (child >= 0 && parent >= 0)) {

			swap(queue[child], queue[parent]);
			child = parent;
			parent = getParent(child);

		}

	}

}


//Method to display the priority queue for testing and debugging
void MinPriorityQueue::displayMinPriorityQueue() {


	cout << "Priority Queue with Capacity = " << capacity << " and Number of Elements = " << numOfElements << endl;

	for (int i = 0; i < numOfElements; i++) {

		cout << "Element " << i << ": Value = " << queue[i].index << "Weight:" << queue[i].value << endl;

	}



}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////