#include "Shape.h"

Shape::Shape(float posX, float posY, float size, bool collision) :
	posX(posX),
	posY(posY),
	size(size),
	collision(collision) {};

Shape::~Shape() {}

float Shape::GetPosX() const { return this->posX; }

float Shape::GetPosY() const { return this->posY; }

float Shape::GetSize() const { return this->size;  }

bool Shape::GetCollision() const { return this->collision; }

void Shape::SetPosX(float x) { this->posX = x; }

void Shape::SetPosY(float y) { this->posY = y; }

void Shape::SetCollision(bool collision) { this->collision = collision; }

/* Moves Shape to a new position in the grid. */
void Shape::Transform(float newX, float newY) {
	this->SetPosX(newX);
	this->SetPosY(newY);
}
