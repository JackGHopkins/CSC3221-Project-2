#pragma once

class Circle;
class Square;

/// <summary>
///		Abstract class to be inherited by all shapes.
/// </summary>
class Shape
{
public:
	/* CONSTRUCTOR & DECONSTRUCTORS */
	Shape(float posX, float posY, float size, bool collision);
	~Shape();

	/* ABSTRACT METHODS */
	virtual void CheckCollision(Shape& Other) = 0;

	/* METHODS */
	float GetPosX() const;
	float GetPosY() const;
	float GetSize() const;
	bool GetCollision() const;
	void SetPosX(const float x);
	void SetPosY(const float y);
	void SetCollision(bool collision);
	void Transform(float offsetX, float offsetY);

private:
	float posX, posY, size;
	bool collision;
};
