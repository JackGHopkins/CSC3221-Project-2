#pragma once

class Circle {};
class Square {};

class Shape
{
public:
	Shape(float posX, float posY, bool overlap);
	~Shape();

	virtual void CheckOverlap(const Circle& Other) = 0;
	virtual void CheckOverlap(const Square& Other) = 0;

	void Transform(float offsetX, float offsetY);

	float GetPosX() const;
	float GetPosY() const;
	bool GetOverlap() const;
	void SetPosX(const float x);
	void SetPosY(const float y);
	void SetOverlap(const bool overlap);

private:
	float posX, posY;
	bool overlap;
};
