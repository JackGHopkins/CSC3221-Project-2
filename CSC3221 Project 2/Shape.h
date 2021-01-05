#pragma once

class Circle {};
class Square {};

class Shape
{
public:
	Shape(float posX, float posY) : posX(posX), posY(posY) {};
	~Shape();

	virtual void CheckOverlap(const Circle& Other) const = 0;
	virtual void CheckOverlap(const Square& Other) const = 0;

	virtual void Transform(const Shape& shape) = 0;

	float GetPosX() const;
	float GetPosY() const;
	void SetPosX(float x);
	void SetPosY(float y);

private:
	float posX, posY;
};
