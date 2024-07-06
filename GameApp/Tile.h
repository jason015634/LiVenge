#pragma once
#include "CustomComponent.h"

class Tile : public CustomComponent
{
public:
	Tile() {}
	~Tile() {}
	// �ʼ� ������
public:

	static const ULONGLONG ComponentType = (ULONGLONG)E_CustomComponent::Tile;

	static const ULONGLONG ComponentFlag = 1 << ComponentType;

	// --------------�ʼ� ������---------------------
	int GetGx() { return m_Gx; }
	int GetGy() { return m_Gy; }
	void SetGridPos(int _x, int _y)
	{
		m_Gx = _x;
		m_Gy = _y;
	}


private:
	int m_Gx;
	int m_Gy;
};


