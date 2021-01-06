#pragma once
#include "Shape.h"
#include "Square.h"

class Circle : public Shape {
public:
	Circle(float posX, float posY, float radius);
	~Circle();

	float GetRadius() const;

	virtual void CheckOverlap(const Circle& Other);
	virtual void CheckOverlap(const Square& Other);
private:
	float radius;
};
