#include "Square.h"

Square::Square(float posX, float posY, float length) : 
	Shape(posX, posY, false),
	length(length) {}

Square::~Square() {}

float Square::GetLength() const {
	return this->length;
}

void Square::CheckOverlap(Circle& Other) {
	Other.CheckOverlap(*this);
}

void Square::CheckOverlap(Square& Other) {

}