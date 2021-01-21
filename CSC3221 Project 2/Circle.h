#pragma once
#include "Shape.h"
#include "Square.h"

class Circle : public Shape {
public:
	Circle(float posX, float posY, float radius);
	~Circle();

	float GetRadius() const;

	bool CentreWithinRadius(float posX, float posY, float raidus) const;
	bool PointWithinRadius(float posX, float posY) const;

	virtual void CheckOverlap(Circle& Other);
	virtual void CheckOverlap(Square& Other);
private:
	float radius;
};
