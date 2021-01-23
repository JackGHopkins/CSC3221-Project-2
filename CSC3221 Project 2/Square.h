#pragma once
#include "Shape.h"
#include "Circle.h"

class Square : public Shape {
public:
	Square(float posX, float posY, float length);
	~Square();

	float GetLength() const;
	void CheckCollision(Shape& Other);
private:
	float length;
};
	