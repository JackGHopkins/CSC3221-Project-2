#include "Circle.h"

Circle::Circle(float posX, float posY) {
	this->posX = posX;
	this->posY = posY;
}

Circle::~Circle() {}

void Circle::setPosX(float x) {
	this->posX = x;

}

void Circle::setPosY(float y) {
	this->posY = y;
}
