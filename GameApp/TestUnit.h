#pragma once
#include "Entity.h"

class TestUnit : public Entity
{
public:
	TestUnit() {};
	~TestUnit() {}
public:
	void Initialize() override;
	int GetUnitCost() { return TestUnitCost; }
	int GetUnitID() { return TestUnitID; }
private:
	int TestUnitID = 102;
	int TestUnitCost = 3;
};
