#pragma once
#include "Shape.h"

class Circle : Shape {
public:
	Circle(float posX, float posY) : Shape(posX, posY) {};
	~Circle();

	void setPosX(float x);
	void setPosY(float y);

private:
	float posX, posY;
};
