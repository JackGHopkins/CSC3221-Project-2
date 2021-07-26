#pragma once
#include "Circle.h"
#include "Grid.h"
#include "Shape.h"
#include "Square.h"
#include <iostream>
#include <vector>
#include <math.h>

/* GLOBAL VARIABLES */
const int SHAPE_NUMBER = 50;
const int SHAPE_TYPE_NUMBER = 2;
const int CELL_SIZE = 100;
const int GRID_MAX_WIDTH = 2000;
const int GRID_MAX_HEIGHT = 2000;

const float SHAPE_MAX_SIZE = 100.0f;
const float SHAPE_MIN_SIZE = 70.0f;
const float SHAPE_TRANSFORM_MULTIPLIER = 10.0f;

bool IS_RANDOM = true;

std::multimap<int, Shape*> multimap;
std::vector<int> movementVectorX;
std::vector<int> movementVectorY;
std::vector<Shape*> eraseVector;

/* METHOD DECLARATIONS */
void CheckCollisions();
void DeleteShapes();
void GenerateRandomMultimap();
float RandomFloat(float min, float max);
void PrintCollision(Shape* i, Shape* j);
void RandomGame();
void TransformMultimap();
void Test();

/* METHOD IMPLEMENTATION */
int main() {
	/* Testing for unique circumstances. Should match the Sample Output. */
	Test();

	/* Main Game, with Random Shapes */
	RandomGame();

	return 0;
}

/*
	Method it to check collisions. Order of operation:
		1. Iterate through Cells to find Shape.
		2. Get the Shape and find the possible are it could have collisions
		   within given that its origin is in a particular Cell.
		3. Check for collisions with all possible shapes in that area.
		4. Delete Shapes with collisions.
*/
void CheckCollisions() {
	if (multimap.empty())
		std::cout << "MULTIMAP IS EMPTY" << std::endl;

	// Iterate through Cells
	for (int x = 0; x < GRID_MAX_WIDTH / CELL_SIZE; x++) {
		for (int y = 0; y < GRID_MAX_HEIGHT / CELL_SIZE; y++) {

			// DELETE LATER
			//std::cout << "CC Cell X: " << x << " | Cell Y: " << y << std::endl;


			int key = x + (y * CELL_SIZE);
			// Check Key for shapes
			if (multimap.count(key) != 0) {
				auto range = multimap.equal_range(key);
				// Iterate through number of shapes in Cell.
				for (auto shapeNo = range.first; shapeNo != range.second; shapeNo++) {
					if (shapeNo->second->GetCollision()) {
						continue;
					}

					// Calculating Maximum number of Cells shape can cover. Equals RoundUp(Size / Cell Size) + 1 + RoundUp(MaxSize / Cell Size) - 1.
					int maxCellCoverage = ceil(shapeNo->second->GetSize() / CELL_SIZE) + // Checking possible Cells that the shape could habit.
						ceil(SHAPE_MAX_SIZE / CELL_SIZE); // Checking if any Cells contain possible largest shape around it.

					// Finding Cell Bounds
					int CellsLowerX = x - floor(maxCellCoverage / 2);
					int CellsHigherX = x + floor(maxCellCoverage / 2);
					int CellsLowerY = y - floor(maxCellCoverage / 2);
					int CellsHigherY = y + floor(maxCellCoverage / 2);

					// Checking if the bounds are on the boarder of the grid.
					if (CellsLowerX < 0)
						CellsLowerX = 0;

					if (CellsHigherX > ceil(GRID_MAX_WIDTH / CELL_SIZE))
						CellsHigherX = ceil(GRID_MAX_WIDTH / CELL_SIZE);

					if (CellsLowerY < 0)
						CellsLowerY = 0;

					if (CellsHigherY > ceil(GRID_MAX_HEIGHT / CELL_SIZE))
						CellsHigherY = ceil(GRID_MAX_HEIGHT / CELL_SIZE);

					// Checking all possible surrounding cells that the Shape could collide within.
					for (int i = CellsLowerX; i <= CellsHigherX; i++) {
						for (int j = CellsLowerY; j <= CellsHigherY; j++) {
							// Make another key for the Cells you are comparing it to.
							int keyCompare = i + (j * CELL_SIZE);
							// Check Key for shapes
							if (multimap.count(keyCompare) != 0) {
								auto range = multimap.equal_range(keyCompare);
								for (auto shapeCompare = range.first; shapeCompare != range.second; shapeCompare++) {
									if (shapeNo->second == shapeCompare->second || shapeCompare->second->GetCollision() == true)
										continue;
									
									// Break if Shape is already collided.
									if  (shapeNo->second->GetCollision() == true) {
										break;
									}

									shapeNo->second->CheckCollision(*(shapeCompare->second));

									if (shapeNo->second->GetCollision() == true || shapeCompare->second->GetCollision() == true) {
										PrintCollision(shapeNo->second, shapeCompare->second);
										eraseVector.push_back(shapeNo->second);
										eraseVector.push_back(shapeCompare->second);
										break;
									}

								}
							}

						}
					}
				}
			}
		}
	}
}

/*
	Iterate through eraseVector, deleting all the elements (collided shapes),
	and updating it with a clean vector.
*/
void DeleteShapes() {
	// Only Erase if there are Shapes to Erase.
	if (eraseVector.size() > 0) {
		// Delete Shapes added to eraseVector.
		for (int i = 0; i < eraseVector.size(); i++)
			delete eraseVector[i];

		std::vector<Shape*> cleanVector;
		eraseVector = cleanVector;
		std::cout << "No. Shapes Remaining:" << multimap.size() << std::endl;
	}
	return;
}

/*
	Generate shapes of random position and size (within a range), placing them in multimap.
*/
void GenerateRandomMultimap() {
	for (int i = 0; i < SHAPE_NUMBER; i++) {
		// Random Number that chooses a random Enum from ShapeType.
		int shapeType = int(rand() % SHAPE_TYPE_NUMBER);
		float randLength = RandomFloat(SHAPE_MIN_SIZE, SHAPE_MAX_SIZE);
		float posX = RandomFloat(0, GRID_MAX_WIDTH);
		float posY = RandomFloat(0, GRID_MAX_HEIGHT);

		// Finding cell coordinates.
		int cellX = floor(posX / CELL_SIZE);
		int cellY = floor(posY / CELL_SIZE);

		// Creating Unique Key for every Cell. Brackets are for readibility.
		int key = cellX + (cellY * CELL_SIZE);

		// If shapeType is 0 then the shape will be a Circle. Radius = randLength / 2
		if (shapeType == 0)
			multimap.insert(std::make_pair(key, new Circle(posX, posY, randLength / 2)));
		// If shapeType is 0 then the shape will be a Square.
		if (shapeType == 1)
			multimap.insert(std::make_pair(key, new Square(posX, posY, randLength)));
	}
}

/*
	Creates a random float between two numbers.
*/
float RandomFloat(float min, float max) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float x = random * diff;
	return min + x;
}

/*
	The random game loop, where Multimap is made of Shapes with Random sizes,
	position and will move in random directions until they collide and be destroyed.
*/
void RandomGame() {
	std::cout << "***** RANDOMGAME: START *****" << std::endl;
	GenerateRandomMultimap();
	Grid grid(GRID_MAX_WIDTH, GRID_MAX_HEIGHT, multimap);

	while (true) {
		// Break if multimap is empty or has only one shape left.
		if (multimap.size() == 0 || multimap.size() == 1)
			break;

		// Check Multimap for Collisions.
		CheckCollisions();

		// Move Multimap
		TransformMultimap();

		// Delete shapes from eraseVector.
		DeleteShapes();
	}

	// Delete left over shapes.
	for (int x = 0; x < GRID_MAX_WIDTH / CELL_SIZE; x++) {
		for (int y = 0; y < GRID_MAX_HEIGHT / CELL_SIZE; y++) {
			// Finding cell coordinates.
			int cellX = floor(x / CELL_SIZE);
			int cellY = floor(x / CELL_SIZE);

			// Creating Unique Key for every Cell. Brackets are for readibility.
			int key = cellX + (cellY * CELL_SIZE);
			multimap.erase(key);
		}
	}
	std::cout << "***** RANDOMGAME: END *****" << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

/*
	Prints information about the collision.
*/
void PrintCollision(Shape* i, Shape* j) {
	std::cout << "+++++++++++++++++ COLLISION FOUND +++++++++++++++++" << std::endl;
	// Print Shape i
	std::cout <<
		"+ Shape No: " << i <<
		" | PosX: " << i->GetPosX() <<
		" | PosY: " << i->GetPosY() <<
		" | CellX: " << floor(i->GetPosX() / CELL_SIZE) <<
		" | CellY: " << floor(i->GetPosY() / CELL_SIZE) <<
		" | Collision: " << i->GetCollision() <<
		" | Size: " << i->GetSize() <<
		std::endl;

	// Print Shape j
	std::cout <<
		"+ Shape No: " << j <<
		" | PosX: " << j->GetPosX() <<
		" | PosY: " << j->GetPosY() <<
		" | CellX: " << floor(j->GetPosX() / CELL_SIZE) <<
		" | CellY: " << floor(j->GetPosY() / CELL_SIZE) <<
		" | Collision: " << j->GetCollision() <<
		" | Size: " << j->GetSize() <<
		std::endl;

	std::cout << std::endl;
}

/*
	Transforms all the shapes that have not collided to new random positions.

*/
void TransformMultimap() {
	std::multimap<int, Shape*> newMultimap;
	// Keeps track of how a shape moves when IS_RANDOM = false.
	int moveCounter = 0;

	// Iterate through Cells
	for (int x = 0; x < GRID_MAX_WIDTH / CELL_SIZE; x++) {
		for (int y = 0; y < GRID_MAX_HEIGHT / CELL_SIZE; y++) {
			int key = x + (y * CELL_SIZE);
			// Check Key for shapes.
			if (multimap.count(key) != 0) {
				auto range = multimap.equal_range(key);
				// Iterate through number of shapes in Cell.
				for (auto shapeNo = range.first; shapeNo != range.second; shapeNo++) {
					if (shapeNo->second->GetCollision() == true) {
						continue;
					}
					float newPosX;
					float newPosY;

					if (IS_RANDOM) {
						// Create random float between -1 and 1, and adds that to current position.
						newPosX = shapeNo->second->GetPosX()
							+ RandomFloat(-1.0, 1.0)
							* SHAPE_TRANSFORM_MULTIPLIER;
						newPosY = shapeNo->second->GetPosY()
							+ RandomFloat(-1.0, 1.0)
							* SHAPE_TRANSFORM_MULTIPLIER;
					}
					else {
						// Create random float between -1 and 1, and adds that to current position.
						newPosX = shapeNo->second->GetPosX()
							+ movementVectorX[moveCounter];
						newPosY = shapeNo->second->GetPosY()
							+ movementVectorY[moveCounter];
					}

					// Checking if New Positions are Out of Bounds.
					if (newPosX < 0 || newPosX > GRID_MAX_WIDTH)
						newPosX = shapeNo->second->GetPosX();
					if (newPosY < 0 || newPosY > GRID_MAX_HEIGHT)
						newPosY = shapeNo->second->GetPosY();
					shapeNo->second->Transform(newPosX, newPosY);

					// Move Shape to a new Multimap.
					int cellX = floor(shapeNo->second->GetPosX() / CELL_SIZE);
					int cellY = floor(shapeNo->second->GetPosY() / CELL_SIZE);
					int key = cellX + (cellY * CELL_SIZE);
					newMultimap.insert(std::make_pair(key, shapeNo->second));

					if (!IS_RANDOM)
						moveCounter++;
				}
			}
		}
	}
	// Update Multimap
	multimap = newMultimap;
}

/*
	TESTING Methods for particular scenoriors. Global variables need to be set to this:
		const int CELL_SIZE = 100;
		const int GRID_MAX_WIDTH = 2000;
		const int GRID_MAX_HEIGHT = 2000;
*/
void Test() {
	std::cout << "***** TESTING: START *****" << std::endl;

	std::multimap<int, Shape*> cleanMultimap;
	IS_RANDOM = false;

	// Setting up movementVector
	movementVectorX = { 10, -10, 10, -10 };
	movementVectorY = { 0, 0 , 0, 0 };

	// TEST 1: Circle colliding with Circle
	multimap.insert(std::make_pair(0, new Circle(0, 0, 10 / 2)));
	multimap.insert(std::make_pair(0, new Circle(5, 0, 10 / 2)));
	multimap.insert(std::make_pair(0, new Circle(80, 0, 10 / 2)));

	// TEST 2: Square colliding with Square
	multimap.insert(std::make_pair(1, new Square(100, 0, 10)));
	multimap.insert(std::make_pair(1, new Square(140, 0, 10)));
	multimap.insert(std::make_pair(1, new Square(145, 0, 10)));

	// TEST 3: Circle colliding with Square
	// Test for overlap.
	multimap.insert(std::make_pair(2, new Circle(200, 0, 10 / 2)));
	multimap.insert(std::make_pair(2, new Square(205, 0, 10)));

	// No Overlap
	multimap.insert(std::make_pair(2, new Circle(250, 0, 10 / 2)));
	multimap.insert(std::make_pair(2, new Square(270, 0, 10)));

	// Circle within Square
	multimap.insert(std::make_pair(2, new Circle(250, 50, 5 / 2)));
	multimap.insert(std::make_pair(2, new Square(250, 50, 10)));

	// Square within Circle
	multimap.insert(std::make_pair(2, new Circle(200, 50, 10 / 2)));
	multimap.insert(std::make_pair(2, new Square(200, 50, 5)));

	// Crossing Corners 
	multimap.insert(std::make_pair(3, new Circle(330, 33, 37 / 2)));
	multimap.insert(std::make_pair(3, new Square(310, 10, 20)));

	for (int i = 0; i < 2; i++) {
		CheckCollisions();
		TransformMultimap();
		DeleteShapes();
	}

	multimap = cleanMultimap;
	IS_RANDOM = true;

	std::cout << "***** TESTING: END *****" << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}
