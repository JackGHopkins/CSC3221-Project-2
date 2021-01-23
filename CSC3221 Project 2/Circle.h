#pragma once
#include "Shape.h"
#include "Square.h"

class Circle : public Shape {
public:
	Circle(float posX, float posY, float radius);
	~Circle();

	float GetRadius() const;
	bool PointWithinRadius(float posX, float posY) const;

	virtual void CheckCollision(Shape& Other);
private:
	float radius;
};
