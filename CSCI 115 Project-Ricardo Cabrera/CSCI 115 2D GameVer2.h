#pragma once

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

using namespace std;


//2D Map Matrix Class
class MapMatrix {

private:

	int numOfColumns;
	int numOfRows;

	//2D map matrix
	char** matrix;

	//Player and Enemy Starting Positions, the first value corresponds to the row and the second value corresponds to the column that they are in
	pair<int, int> playerStartingPosition;

	//Enemies
	pair<int, int> greyStartingPosition;
	pair<int, int> sniperStartingPosition;
	pair<int, int> halStartingPosision;


public:

	//Constructors:
	//Default constructor that sets the number of rows and number of columns to zero
	MapMatrix();

	//Constructor that takes a text file name as an input and creates a map by reading the characters in the file
	MapMatrix(string argFileName);

	//Destructor:
	~MapMatrix();


	//Useful Methods:
	//method to get the number of rows in the map
	int getNumOfRows();

	//method to get the number of columns in the map
	int getNumOfColumns();

	//method to get the char from a given cell in the 2D map
	char getCharAtPosition(int argRow, int argColumn);

	//method to set the char that is in a given cell in the 2D map
	void setCharAtPosition(int argRow, int argColumn, int argChar);

	//testing and debugging version of the method to display the map
	void displayMapTestingVer();

	//method to display the map
	void displayMap();

	//method to reset the map to its original state
	void resetMap(string argFileName);

	//method to set the starting position of the player on the map
	void setPlayerStartingPosition(int argRow, int argColumn);

	//method to get the row and column of the player's starting position
	pair<int, int> getPlayerStartingPosition();

	//method to set the starting position of specific enemy on the map
	void setEnemyStartingPosition(int argRow, int argColumn, string argName);

	//method to get the row and column of a specific enemy's starting position
	pair<int, int> getEnemyStartingPosition(string argName);


};

//Function to get the name of the map that the user has selected
string getMapName(int argMapNumber);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Min Priority Queue Data Type
struct minPQData {

	int index;
	double value;

};




////Min Priority Queue Class implemented using a Min Heap
class MinPriorityQueue {


private:

	//Max number of elements allowed in the priority queue
	int capacity;

	//Number of elements currently in the pririty queue
	int numOfElements;

	minPQData* queue;

	//Min Heapify Method
	void minHeapify(int argIndex, int argSize);

public:

	//Constructors:
	//Default Constructor
	MinPriorityQueue();

	//Constructor that creates a prioirty queue based on a given capacity
	MinPriorityQueue(int argCapacity);


	//Destructor:
	~MinPriorityQueue();



	//Useful Methods:
	//Method to get the current number of elements in the prioruty queue
	int getNumOfElements();

	//Method to check if the priority queue is empty
	bool isEmpty();

	//Method to check if a priority queue is full
	bool isFull();

	//Method to enqueue an element into the priority queue
	void push(int argIndex, double argValue);

	//Method to dequeue an element from the priroity queue
	minPQData pop();

	//Method to decrease the key for an element in the priority queue
	void decreaseKey(int argIndex, double value);

	//Method to build a min heap using the elements in the priority queue
	void buildMinHeap();

	//Method to display the priority queue
	void displayMinPriorityQueue();

	//Method to get the parent node for a given child node in the min heap
	int getParent(int argChild);


};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Adjacency List Graph Node Class
class ALNode {

public:

	int vertex;
	double weight;

	//pointer to next node
	ALNode* next;

	//Constructors:
	//Default constructor
	ALNode();

	//Constructor that takes a vertex and an edge weight as inputs
	ALNode(int argVertex, double argWeight);


	//Destructor:
	~ALNode(); //memory management

};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Adjacency List Graph Class
class GraphAL : public ALNode {

private:

	int numOfVert;

	//Array of ALNode pointers that represents the adjacency list
	ALNode** listArr;
	//Array of ALNode pointers used for the adjacecnt verticies in the graph
	ALNode** current;


public:

	//Constructors:
	//Default constructor
	GraphAL();

	//Constructor that takes in a given number of vertices as an input
	GraphAL(int argNumOfVert);


	//Destructor:
	~GraphAL();


	//Useful Methods:
	//method to add a weighted directed edge between two given verticies in the adjacency list
	void addDirectedEdge(int argVertex1, int argVertex2, double argWeight);

	//method to add a weighted undirected edge between two given verticies in the adjacency list
	void addUndirectedEdge(int argVertex1, int argVertex2, double argWeight);

	//method to display the adjacency list
	void displayAdjacencyList();

	//method to check if there is an edge between two verticies
	bool edgeExists(int argVertex1, int argVertex2);

	//method to get the number of vertices in the adjacecny list graph
	int getNumberOfVertices();

	//method to get the weight of the edge between two vertices
	double getEdgeWeight(int argVertex1, int argVertex2);

	//method to check if an adjacent vertex exits near a given vertex
	bool adjacentVertexExists(int argVertex);

	//method to set the current vertex 
	void setCurrentVertex(int argVertex);

	//method to get the next adjacent vertex for a given vertex
	int getNextAdjacentVertex(int argVertex);

	//method to create an adjacecny list from a given map
	void createALGraphFromMap(MapMatrix* argMap, int** argVertexNumArr);

	//method to get the weight for an edge by using the character in a cell
	double getWeightFromMap(int argRow, int argColumn, MapMatrix* argMap);

	//method to add an edge to the adjacency list graph by checking in four directions to see if an edge can be made
	void addEdgeUsingMap(int argIndex1, int argIndex2, int** argVertexNumArr, MapMatrix* argMap);

	//Method for the Dijkstra Shortest-Path algorithm
	void dijkstra(int sourceVertex, double* &argDistance, int* & argPi);

	//Method for Dijkstra Shortes-Path algorithm used for testing and debugging
	void dijkstraBenchmarkVersion(int sourceVertex, double* &argDistance, int* &argPi);



};

//Function to display the results of the Dijkstra algorithm
void dijkstraDisplayShortestPath(double* argDistance, int* argPi, int argSize);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Character Class
class Character {

private:


	pair<int, int> currentMapPosition;
	char currentCellType;
	char characterType;
	pair<int, int> startingPosition;
	int vertexPosition;
	string currentStatus;
	string name;
	string characterEvent;
	char startingCellType;
	int startingVertexPosition;
	int nextVertexPosition;

public:

	//Constructors:
	//Default Constructor
	Character();

	//Constructor that creates a character of a given type and name
	Character(char argCharacterType, string argName);

	//Destructor:
	~Character();


	//Useful Methods:
	//Method to set the starting position of a player or enemy on the map
	void setCharacterStartingPosition(int argRow, int argColumn);

	//Method to set a character's current position on the map
	void setCharacterPosition(int argRow, int argColumn);

	//Method to get row and column values for a character's current position on the map
	pair<int, int> getCharacterPosition();

	//Method to set the number of the vertex that corresponds to where the character is on the map
	void setCharacterVertexPosition(int argVertexNum);

	//Method to get the vertex number that corresponds to where the character is
	int getCharacterVertexPosition();

	//Method to set the current status for a character
	void setStatus(string argStatus);

	//Method to display the information about a character
	void displayCharacterInfo();

	//Method to move the player when the user preses a movement key
	void playerMove(string argKey, MapMatrix* argMap, int** argVertexNumArr);

	//Method to perform the movement action for a character
	void characterMove(int argRow, int argColumn, MapMatrix* &argMap, int** argVertexNumArr);

	//Method to check if the position that a character wants to move into is a wall
	bool isWall(int argRow, int argColumn, MapMatrix* argMap);

	//Method to check if tow enenies will collide if they move
	bool enemyCollisionExists(int argRow, int argColumn, MapMatrix* argMap);

	//Method to check is the player has been caught by an enemy
	bool isGameOver(MapMatrix* argMap);

	//Method to check if the player has quit the game
	bool checkIfQuit(string argKey);

	//Method to set the name for a character
	void setName(string argName);

	//Method to reset character position to starting position
	void resetCharacterPosition();

	//Method to set the starting vertex position of a character
	void setStartingVertexPosition(int argVertexNumber);

	//Method to check if the player is on a hidden cell type and is now hidden
	void checkIfHidden(Character* &argGrey, Character* &argSniper, Character* &argHal);

	//Method to determine what action the enemy character will perform
	void enemyMove(MapMatrix* &argMap, int** argVertexNumArr, Character* &argPlayer, GraphAL* argGraph);

	//Method to perform a patrol move for an enemey
	void patrolMove(MapMatrix* &argMap, int** argVertexNumArr);

	//Method to check if an enemy can see the player
	void checkIfPlayerSpotted(Character* &argPlayer, MapMatrix* argMap);

	//Alternate player spotted method
	bool checkIfPlayerSpotted2(Character* &argPlayer, MapMatrix* argMap);

	//Method to perform a pursue move for an enemy
	void pursueMove(MapMatrix* &argMap, int** argVertexNumArr, Character* argPlayer, GraphAL* argGraph);

};

//Function to initialize the vertex number array used to hold the vertex numbers in the graph
void initializeVertexNumberArr(int** &vertexNumberArr, MapMatrix* argMap);

//Function to set the starting positions and starting vertex numbers for all of the characters based on the given map number
void initializeStartingPositions(int argMapNumber, int** argVertexNumberArr, Character* &argPlayer, Character* &argGrey, Character* &argSniper, Character* &argHal);



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////