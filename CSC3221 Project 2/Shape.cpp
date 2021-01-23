#include "Shape.h"

Shape::Shape(float posX, float posY, bool collision) :
	posX(posX),
	posY(posY),
	collision(collision) {};

Shape::~Shape() {}

float Shape::GetPosX() const { return this->posX; }

float Shape::GetPosY() const { return this->posY; }

bool Shape::GetCollision() const { return this->collision; }

void Shape::SetPosX(float x) { this->posX = x; }

void Shape::SetPosY(float y) { this->posY = y; }

void Shape::SetCollision(bool collision) { this->collision = collision; }

void Shape::Transform(float offsetX, float offsetY) {
	this->SetPosX(this->GetPosX() + offsetX);
	this->SetPosY(this->GetPosY() + offsetY);
}
