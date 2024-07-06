#pragma once
#include "framework.h"

class Entity;
class UnitCard;

class UnitFactoryUI
{
public:
	UnitFactoryUI() {}
	~UnitFactoryUI() {}

public:
	void Initialize();
	void Finalize();

public:
	UnitCard* CreateUnitCard(int _unitID);
};

