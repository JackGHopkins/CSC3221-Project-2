#pragma once
#include "Shape.h"
#include "Square.h"

/// <summary>
///		Class for the Circle Shape.
/// </summary>
class Circle : public Shape {
public:
	/* CONSTRUCTORS & DESTRUCTORS*/
	Circle(float posX, float posY, float radius);
	~Circle();

	/* METHODS */
	float GetRadius() const;
	bool PointWithinRadius(float posX, float posY) const;
	void CheckCollision(Shape& Other);
private:
	float radius;
};
