#pragma once

class Entity;
class UnitStatUI;
class UnitStatFactory
{
public:
	UnitStatFactory() {}
	~UnitStatFactory() {}

public:
	void Initialize();
	void Finalize();

public:
	UnitStatUI* CreateUnitCard(int _unitID);
};

