#include "Circle.h"
#include "Collision.h"
#include "Shape.h"
#include <iostream>
#include <math.h>

Circle::Circle(float posX, float posY, float radius) :
	Shape(posX, posY, radius * 2, false), 
	radius(radius) {}

Circle::~Circle() {}

float Circle::GetRadius() const {
	return this->radius;
}

void Circle::CheckCollision(Shape& Other) {
		Collision collision;
		try {
			if (typeid(Other) == typeid(Circle))
				collision.isCollision(static_cast<Circle&>(Other), *this);
			else if (typeid(Other) == typeid(Square))
				collision.isCollision(*this, static_cast<Square&>(Other));
			else
				throw "Error: Shape Type Not Found.";
		}
		catch (char const*& e) {
			std::cout << e;
		}
}

// For checking if a certain point of a shape is within the Circle.
bool Circle::PointWithinRadius(float posX, float posY) const {
	float distance = sqrtf(powf(this->GetPosX() - posX, 2.0) + powf(this->GetPosY() - posY, 2.0));

	if (distance < this->GetRadius())
		return true;

	return false;
}