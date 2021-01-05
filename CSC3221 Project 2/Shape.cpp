#include "Shape.h"

Shape::Shape(float posX, float posY) {}

Shape::~Shape() {}

float Shape::GetPosX() const {
	return this->posX;
}

float Shape::GetPosY() const {
	return this->posY;
}

void Shape::SetPosX(float x) {
	this->posX = x;

}

void Shape::SetPosY(float y) {
	this->posY = y;
}
