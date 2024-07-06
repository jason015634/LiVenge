#pragma once
#include "framework.h"

class AttackObject;
enum class Dir;

class AttackObjectFactory
{
public:
	void Initialize();
	void Finalize();

public:
	AttackObject* CreateEntity(int _UnitID, int _x, int _y, Dir _direction);

private:
	std::vector<std::pair<int, int>> ProfRange();
};

