#include "Square.h"

Square::Square(float posX, float posY, float length) : 
	Shape(posX, posY, false),
	length(length) {}

Square::~Square() {}

float Square::GetLength() const {
	this->length;
}

void Square::CheckOverlap(const Circle& Other) {

}

void Square::CheckOverlap(const Square& Other) {

}