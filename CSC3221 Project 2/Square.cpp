#include "Square.h"
#include "Collision.h"
#include <iostream>

Square::Square(float posX, float posY, float length) : 
	Shape(posX, posY, length, false),
	length(length) {}

Square::~Square() {}

float Square::GetLength() const {
	return this->length;
}

void Square::CheckCollision(Shape& Other) {
	Collision collision;
	try {
		// Checks if Other is a Circle or a Square.
		if (typeid(Other) == typeid(Circle))
			collision.isCollision(static_cast<Circle&>(Other), *this);
		else if (typeid(Other) == typeid(Square))
			collision.isCollision(static_cast<Square&>(Other), *this);
		else 
			throw "Error: Shape Type Not Found.";
	}
	catch (char const*& e) {
		std::cout << e;
	}
}
