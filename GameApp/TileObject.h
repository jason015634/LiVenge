#pragma once
#include "Entity.h"
class TileObject :public Entity
{
public:
	TileObject()
	{
	}
	~TileObject() {}
public:
	void Initialize() override;

public:
	void SetGridPos(int _x, int _y)
	{
		px = _x;
		py = _y;
	}
	void SetColor(float _r,float _g,float _b, float _a)
	{
		color.r = _r;
		color.g = _g;
		color.b = _b;
		color.a = _a;

	}
	void SetColor(float* _color)
	{
		color.r = _color[0];
		color.g = _color[1];
		color.b = _color[2];
		color.a = _color[3];

	}

private:
	// gird Position
	int px = 0;
	int py = 0;
	D2D1_COLOR_F color;
};

