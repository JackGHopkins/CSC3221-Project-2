#pragma once
#include "Shape.h"
#include "Circle.h"

/// <summary>
///		Class for the Square Shape.
/// </summary>
class Square : public Shape {
public:
	/* CONSTRUCTOR & DESTRUCTOR */
	Square(float posX, float posY, float length);
	~Square();

	/* METHODS */
	float GetLength() const;
	void CheckCollision(Shape& Other);
private:
	float length;
};
	