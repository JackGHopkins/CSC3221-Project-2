#include "Circle.h"
#include "Shape.h"

#include <math.h>

Circle::Circle(float posX, float posY, float radius) :
	Shape(posX, posY, false),
	radius(radius) {}

Circle::~Circle() {}

float Circle::GetRadius() const {
	return this->radius;
}

void Circle::CheckOverlap(const Circle& Other) {
	float distance = sqrt(pow(this->GetPosX() - Other.GetPosX(), 2.0) + pow(this->GetPosY() - Other.GetPosY(), 2.0));
	float sumRadius = this->GetRadius() + Other.GetRadius();

	bool overlap = false;

	if (distance <= sumRadius)
		overlap = true;

	this->SetOverlap(overlap);
}

void Circle::CheckOverlap(const Square& Other) {
	float sqX1 = Other.GetPosX() - (Other.GetLength() / 2);
	float sqX2 = Other.GetPosX() + (Other.GetLength() / 2);
	float sqY1 = Other.GetPosY() - (Other.GetLength() / 2);
	float sqY2 = Other.GetPosY() + (Other.GetLength() / 2);

	float cX1 = this->GetPosX() - this->GetRadius();
	float cX2 = this->GetPosX() + this->GetRadius();
	float cY1 = this->GetPosY() - this->GetRadius();
	float cY2 = this->GetPosY() + this->GetRadius();


	//if()
}