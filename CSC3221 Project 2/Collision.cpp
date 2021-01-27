#include "Collision.h"
#include <math.h>

/*
	Checks collisions between two Circles.
*/
void Collision::isCollision(Circle& c1, Circle& c2) {
	c1.SetCollision(IsSameShapeCollide(c1.GetPosX(), c1.GetPosY(), c1.GetRadius(), c2.GetPosX(), c2.GetPosY(), c2.GetRadius()));
	c2.SetCollision(c1.GetCollision());
}

/*
	Checks collisions between two Squares.
*/
void Collision::isCollision(Square& s1, Square& s2) {
	s1.SetCollision(IsSameShapeCollide(s1.GetPosX(), s1.GetPosY(), s1.GetLength() / 2, s2.GetPosX(), s2.GetPosY(), s2.GetLength() / 2 ));
	s2.SetCollision(s1.GetCollision());
}

/*
	Checks collisions between a Circle and a Square.
*/
void Collision::isCollision(Circle& c, Square& s) {
	// Finds the distance between the centers of the shapes.
	float distanceX = fabsf(c.GetPosX() - s.GetPosX());
	float distanceY = fabsf(c.GetPosY() - s.GetPosY());

	// Checks for case when shapes are out of range ofr the X or Y axis.
	if (distanceX > (s.GetLength() / 2 + c.GetRadius())) {
		s.SetCollision(false);
		c.SetCollision(false);
		return;
	}
	if (distanceY > (s.GetLength() / 2 + c.GetRadius())) {
		s.SetCollision(false);
		c.SetCollision(false);
		return;
	}

	// Checks for Case where the shapes are colliding directly horizontally or vertically.
	if (distanceX <= (s.GetLength()/ 2)) {
		s.SetCollision(true);
		c.SetCollision(true);
		return;
	}
	if (distanceY <= (s.GetLength() / 2)) {
		s.SetCollision(true);
		c.SetCollision(true);
		return;
	}

	// Checks if Circle is overlapping with the corner of the Square.
	float cornerCheck = powf((distanceX - s.GetLength() / 2), 2.0) +
		powf((distanceY - s.GetLength() / 2), 2.0);

	bool cornerCollision = (cornerCheck <= powf(c.GetRadius(), 2.0));
	c.SetCollision(cornerCollision);
	s.SetCollision(cornerCollision);
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
