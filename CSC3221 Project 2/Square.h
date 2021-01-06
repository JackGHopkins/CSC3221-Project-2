#pragma once
#include "Shape.h"
#include "Circle.h"

class Square : public Shape {
public:
	Square(float posX, float posY, float length);
	~Square();

	float GetLength() const;

	virtual void CheckOverlap(const Circle& Other);
	virtual void CheckOverlap(const Square& Other);
private:
	float posX, posY, length;
};
	