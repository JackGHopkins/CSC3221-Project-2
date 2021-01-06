#include "Shape.h"

Shape::Shape(float posX, float posY, bool overlap) :
	posX(posX),
	posY(posY),
	overlap(overlap) {};

Shape::~Shape() {}

float Shape::GetPosX() const { return this->posX; }

float Shape::GetPosY() const { return this->posY; }

bool Shape::GetOverlap() const { return this->overlap; }

void Shape::SetPosX(float x) { this->posX = x; }

void Shape::SetPosY(float y) { this->posY = y; }

void Shape::SetOverlap(bool overlap) { this->overlap = overlap; }

void Shape::Transform(float offsetX, float offsetY) {
	this->SetPosX(this->GetPosX() + offsetX);
	this->SetPosY(this->GetPosY() + offsetY);
}
