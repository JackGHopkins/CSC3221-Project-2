#pragma once
#include "Shape.h"
#include "Circle.h"
#include "Square.h"
#include <iostream>

const int SIZE = 50;
const int GRID_MAX_WIDTH = 2000;
const int GRID_MAX_HEIGHT = 2000;
const int SHAPE_TYPE_SIZE = 2;

const float SHAPE_MAX_LENGTH_RADIUS = 25.0f;
const float SHAPE_MIN_LENGTH_RADIUS = 0.1f;
const float SHAPE_MAX_VELOCITY = 0.2f;

class Grid;

Shape** GenerateShapes();
void DeleteShape(Shape* shapes[], int i);
float RandomFloat(float min, float max);
void PrintGrid(Grid grid);

/*
	The Grid class is where the Shapes will be stored and
	placed to interact. 
*/

class Grid {
public:
	Grid(int width, int height, Shape* shapes[]);
	~Grid();

	Shape* GetShapes();
private:
	int width, height;
	Shape* shapes[];
};

Grid::Grid(int width, int height, Shape* shapes[]) {
	this->width = width;
	this->height = height;
	*this->shapes = *shapes;
}

Grid::~Grid() {}

Shape* Grid::GetShapes() {
	return *this->shapes;
}

/*
	The Main game loop, where shapes will move in random 
	directions until they collide and be destroyed.
*/
int main() {
	Grid grid(GRID_MAX_WIDTH, GRID_MAX_HEIGHT, GenerateShapes());
	PrintGrid(grid);

	return 0;
}

Shape** GenerateShapes() {
	Shape* shapes[SIZE];

	for (int i = 0; i < SIZE; i++) {
		// Random Number that chooses a random Enum from ShapeType.
		int shapeType = int(rand() % SHAPE_TYPE_SIZE);
		float randLength = RandomFloat(SHAPE_MIN_LENGTH_RADIUS, SHAPE_MAX_LENGTH_RADIUS);
		float posX = RandomFloat(0, GRID_MAX_WIDTH);
		float posY = RandomFloat(0, GRID_MAX_HEIGHT);

		if (shapeType == 0){
			Circle c(posX, posY, randLength);
			shapes[i] = &c;
		}
		if (shapeType == 1) {
			Square s(posX, posY, randLength);
			shapes[i] = &s;
		}
	}
	return shapes;
}

void DeleteShape(Shape* shapes[], int i) {
	delete shapes[i];
}


float RandomFloat(float min, float max) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float x = random * diff;
	return min + x;
}

void PrintGrid(Grid grid) {
	for (int i = 0; i < sizeof(grid.GetShapes()); i++) {
		std::cout << "Shape No: " << i << " | Length: " << grid.GetShapes()[i].GetPosX() << std::endl;
	}
}



/*
- Create Shapes (Store in a Data Structure of your choosing).
- Grid of a certain size.
- Move shapes by random ammoutns (Itterate through data).
	- Movement outside of Grid will be cancelled.
- Check if shapes are overlapping
- Output overlapping shape details
- Remove shape if colliding
*/
