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

void Circle::CheckOverlap(Circle& Other) {
	float distance = sqrtf(powf(this->GetPosX() - Other.GetPosX(), 2.0) + powf(this->GetPosY() - Other.GetPosY(), 2.0));

	this->SetOverlap(CentreWithinRadius(Other.GetPosX(), Other.GetPosY(), Other.GetRadius()));
}

void Circle::CheckOverlap(Square& Other) {
	float sqX1 = Other.GetPosX() - (Other.GetLength() / 2); // left
	float sqX2 = Other.GetPosX() + (Other.GetLength() / 2); // right
	float sqY1 = Other.GetPosY() - (Other.GetLength() / 2); // bottom
	float sqY2 = Other.GetPosY() + (Other.GetLength() / 2); // top

	float cX1 = this->GetPosX() - this->GetRadius(); // left
	float cX2 = this->GetPosX() + this->GetRadius(); // right
	float cY1 = this->GetPosY() - this->GetRadius(); // bottom
	float cY2 = this->GetPosY() + this->GetRadius(); // top

	// Check if the centers are inside the circle.
	if (this->CentreWithinRadius(Other.GetPosX(), Other.GetPosY(), Other.GetLength() / 2)) {
		this->SetOverlap(true);
		return;
	}

	bool cLeftOfS = false;
	bool cRightOfS = false;
	bool cBellowS = false;
	bool cAboveS = false;

	// Check if the left of the square is to the right of the circle
	if (sqX1 >= cX2)
		cLeftOfS = true;

	// Check if the right of the square is to the left of the cirlce
	if (sqX2 <= cX1)
		cRightOfS = true;

	// Check if the bottom of the square is above of the circle
	if (sqY1 >= cY2)
		cBellowS = true;

	// Check if the top of the square is bellow of the cirlce
	if (sqY2 <= cY1)
		cAboveS = true;

	/*
	cLS	cBs R
	0	0	Top Right
	0	1	Bottom Right
	1	0	Top Left
	1	1	Bottom Left
	*/

	// Top Right 
	if (!cLeftOfS && !cBellowS) {
		// Get Bottom Left Circle
		this->SetOverlap(this->PointWithinRadius(sqX1, sqY1));
	}

	// Bottom Right
	if (!cLeftOfS && cBellowS) {
		// Get Top Left Circle
		this->SetOverlap(this->PointWithinRadius(sqX1, sqY2));
	}

	// Top Left
	if (cLeftOfS && !cBellowS) {
		// Get Bottom Right Cirlce
		this->SetOverlap(this->PointWithinRadius(sqX2, sqY1));
	}

	// Bottom Left
	if (cLeftOfS && cBellowS) {
		// Get Top Right Circle
		this->SetOverlap(this->PointWithinRadius(sqX2, sqY2));
	}

}

// For checking the centers of two shapes. If comparing Square, make sure the "Radius" is GetLength() / 2.
bool Circle::CentreWithinRadius(float posX, float posY, float radius) const {
	float distance = sqrtf(powf(this->GetPosX() - posX, 2.0) + powf(this->GetPosY() - posY, 2.0));
	float sumRadius = this->GetRadius() + radius;

	if (distance <= sumRadius)
		return true;

	return false;
}

// For checking if a certain point of a shape is within the Circle.
bool Circle::PointWithinRadius(float posX, float posY) const {
	float distance = sqrtf(powf(this->GetPosX() - posX, 2.0) + powf(this->GetPosY() - posY, 2.0));

	if (distance < this->GetRadius())
		return true;

	return false;
}