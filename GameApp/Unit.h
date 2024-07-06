#pragma once
#include "Entity.h"
class Unit : public Entity
{
public:
	Unit();
	virtual ~Unit() {};
public:
	void Initialize() override;
	int px, py;

};

