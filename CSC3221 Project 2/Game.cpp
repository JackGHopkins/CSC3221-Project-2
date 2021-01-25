#pragma once
#include "Circle.h"
#include "Grid.h"
#include "Shape.h"
#include "Square.h"
#include <iostream>
#include <vector>
#include <math.h>

const int SIZE = 50;
const int CELL_SIZE = 40;
const int GRID_MAX_WIDTH = 2000;
const int GRID_MAX_HEIGHT = 2000;
const int SHAPE_TYPE_SIZE = 2;

const float SHAPE_MAX_SIZE = 50.0f;
const float SHAPE_MIN_SIZE = 0.1f;
const float SHAPE_MAX_VELOCITY = 0.2f;

std::multimap<int, Shape*> multimap;

void GenerateMultimap();
void DeleteShape(Shape* Multimap[], int i);
float RandomFloat(float min, float max);
void PrintGrid(Grid grid);
void Games();

/*
	The Main game loop, where Multimap will move in random 
	directions until they collide and be destroyed.
*/
int main() {
	GenerateMultimap();
	Grid grid(GRID_MAX_WIDTH, GRID_MAX_HEIGHT, multimap);
	PrintGrid(grid);

	Game();

	return 0;
}

void GenerateMultimap() {
	for (int i = 0; i < SIZE; i++) {
		// Random Number that chooses a random Enum from ShapeType.
		int shapeType = int(rand() % SHAPE_TYPE_SIZE);
		float randLength = RandomFloat(SHAPE_MIN_SIZE, SHAPE_MAX_SIZE);
		float posX = RandomFloat(0, GRID_MAX_WIDTH);
		float posY = RandomFloat(0, GRID_MAX_HEIGHT);

		// Finding cell coordinates.
		int cellX = floor(posX / CELL_SIZE);
		int cellY = floor(posY / CELL_SIZE);

		// Creating Unique Key for every Cell. Brackets are for readibility.
		int key = cellX + (cellY * CELL_SIZE);

		// If shapeType is 0 then the shape will be a Circle.
		if (shapeType == 0)
			multimap.insert(std::make_pair(key, new Circle(posX, posY, randLength)));
		// If shapeType is 0 then the shape will be a Square.
		if (shapeType == 1)
			multimap.insert(std::make_pair(key, new Square(posX, posY, randLength)));
	}
}

void DeleteShape(Shape* Multimap[], int i) {
	delete Multimap[i];
}


float RandomFloat(float min, float max) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float x = random * diff;
	return min + x;
}

void PrintGrid(Grid grid) {
	for (int i = 0; i < multimap.size(); i++) {
		std::cout << "Shape No: " << i << " | PosX: " << Multimap[i]->GetPosX() << " | PosY: " << Multimap[i]->GetPosY() << " | Overlap: " << Multimap[i]->GetOverlap() << std::endl;
	}
}

void PrintCollision(int i, int j) {
	std::cout << "+++++++++++++++++ COLLISION FOUND +++++++++++++++++" << std::endl;
	// Print Shape i
	std::cout <<
		"+ Shape No: " << i <<
		" | PosX: " << Multimap[i]->GetPosX() <<
		" | PosY: " << Multimap[i]->GetPosY() <<
		" | Overlap: " << Multimap[i]->GetOverlap() <<
		std::endl;

	// Print Shape j
	std::cout <<
		"+ Shape No: " << j <<
		" | PosX: " << Multimap[j]->GetPosX() <<
		" | PosY: " << Multimap[j]->GetPosY() <<
		" | Overlap: " << Multimap[j]->GetOverlap() <<
		std::endl;

	std::cout << std::endl;
}

void Game() {
	while (true) {
		// Move Multimap
		TransformMultimap();
		// Check Multimap for Collisions
		CheckCollisions();
	}
}

void TransformMultimap() {

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
			int key = x + (y * CELL_SIZE);
			// Check Key for shapes
			if (multimap.count(key) != 0) {
				auto range = multimap.equal_range(key);
				// Iterate through number of shapes in Cell.
				for (auto shapeNo = range.first; shapeNo != range.second; shapeNo++) {
					if (shapeNo->second->GetCollision()) {
						multimap.erase(shapeNo);
						continue;
					}


					// Calculating Maximum number of Cells shape can cover. Equals RoundUp(Size / Cell Size) + 1 + RoundUp(MaxSize / Cell Size) - 1.
					int maxCellCoverage =	ceil(shapeNo->second->GetSize()  / CELL_SIZE) + // Checking possible Cells that the shape could habit.
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
									shapeNo->second->CheckCollision(*(shapeCompare->second));
									if (shapeNo->second->GetCollision()) {
										multimap.erase(shapeNo);
										multimap.erase(shapeCompare);
									}

								}
							}


						}
					}
				}

			}
		}
	}



	// Check Collisions
	for (int i = 0; i < Multimap.size(); i++) {
		for (int j = i + 1; j < Multimap.size(); j++) {
			if (Multimap[i] != Multimap[j]) {
				Multimap[i]->CheckOverlap(*Multimap[j]);
			}
			// Then Delete overlapping Multimap.
		}
	}
}

/*
- Create Multimap (Store in a Data Structure of your choosing).
- Grid of a certain size.
- Move Multimap by random ammoutns (Itterate through data).
	- Movement outside of Grid will be cancelled.
- Check if Multimap are overlapping
- Output overlapping shape details
- Remove shape if colliding
*/
