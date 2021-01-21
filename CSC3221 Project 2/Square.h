#pragma once
#include "Shape.h"
#include "Circle.h"

class Square : public Shape {
public:
	Square(float posX, float posY, float length);
	~Square();

	float GetLength() const;

	virtual void CheckOverlap(Circle& Other);
	virtual void CheckOverlap(Square& Other);
private:
	float length;
};
	