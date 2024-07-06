#pragma once
#include "Entity.h"
class TestUnitUI : public Entity
{
public:
	TestUnitUI() {}
	~TestUnitUI() {}

public:
	void Initialize() override;
	int GetUnitID() { return UnitID; }
private:
	int UnitID = 102;
};

