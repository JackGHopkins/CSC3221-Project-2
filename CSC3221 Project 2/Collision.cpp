#include "Collision.h"
#include <math.h>

Collision::Collision() {}

Collision::~Collision() {}

void Collision::isCollision(Circle& c1, Circle& c2) {
	c1.SetCollision(IsSameShapeCollide(c1.GetPosX(), c1.GetPosY(), c1.GetRadius(), c2.GetPosX(), c2.GetPosY(), c2.GetRadius()));
}

void Collision::isCollision(Square& s1, Square& s2) {
	s1.SetCollision(IsSameShapeCollide(s1.GetPosX(), s1.GetPosY(), s1.GetLength() / 2, s2.GetPosX(), s2.GetPosY(), s2.GetLength() / 2 ));
}

void Collision::isCollision(Circle& c, Square& s) {
	float sqX1 = s.GetPosX() - (s.GetLength() / 2); // left
	float sqX2 = s.GetPosX() + (s.GetLength() / 2); // right
	float sqY1 = s.GetPosY() - (s.GetLength() / 2); // bottom
	float sqY2 = s.GetPosY() + (s.GetLength() / 2); // top

	float cX1 = c.GetPosX() - c.GetRadius(); // left
	float cX2 = c.GetPosX() + c.GetRadius(); // right
	float cY1 = c.GetPosY() - c.GetRadius(); // bottom
	float cY2 = c.GetPosY() + c.GetRadius(); // top

	// Check if the centers are inside the circle.
	if (IsSameShapeCollide(c.GetPosX(), c.GetPosY(), c.GetRadius(),s.GetPosX(), s.GetPosY(), s.GetLength() / 2)) {
		c.SetCollision(true);
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
		c.SetCollision(c.PointWithinRadius(sqX1, sqY1));
	}

	// Bottom Right
	if (!cLeftOfS && cBellowS) {
		// Get Top Left Circle
		c.SetCollision(c.PointWithinRadius(sqX1, sqY2));
	}

	// Top Left
	if (cLeftOfS && !cBellowS) {
		// Get Bottom Right Cirlce
		c.SetCollision(c.PointWithinRadius(sqX2, sqY1));
	}

	// Bottom Left
	if (cLeftOfS && cBellowS) {
		// Get Top Right Circle
		c.SetCollision(c.PointWithinRadius(sqX2, sqY2));
	}

}

/*
	For checking if the distance between the centers are less then the combined length of the two shapes.
	If comparing Squares, make sure the "Raidus" of the Squares is the radius are GetLength() / 2. 
*/
bool Collision::IsSameShapeCollide(float x1, float y1, float r1, float x2, float y2, float r2) const {
	float distance = sqrtf(powf(x1 - x2, 2.0) + powf(y1 - y2, 2.0));
	float sumLength = r1 + r2;

	if (distance <= sumLength)
		return true;

	return false;
}
