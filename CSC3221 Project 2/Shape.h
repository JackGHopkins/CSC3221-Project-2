#pragma once

class Circle;
class Square;

class Shape
{
public:
	Shape(float posX, float posY, bool collision);
	~Shape();

	virtual void CheckCollision(Shape& Other) = 0;

	void Transform(float offsetX, float offsetY);

	float GetPosX() const;
	float GetPosY() const;
	bool GetCollision() const;
	void SetPosX(const float x);
	void SetPosY(const float y);
	void SetCollision(bool collision);

private:
	float posX, posY;
	bool collision;
};
