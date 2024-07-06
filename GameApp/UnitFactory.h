#pragma once
#include "framework.h"

class Entity;
class Unit;
// ������ �������ִ� Ŭ����
class UnitFactory
{
public:
	UnitFactory() {}
	~UnitFactory() {}
public:
	void Initialize();
	void Finalize();

public:
	Unit* CreateEntity(int _UnitID);

private:
	std::vector<std::pair<int, int>> GetSwordRange();
	std::vector<std::pair<int, int>> GetArrowRange();

	std::vector<std::pair<int, int>> GetDrainRange();
	std::vector<std::pair<int, int>> GetProjectileRange();
	std::vector<std::pair<int, int>> GetSummonerRange();
	std::vector<std::pair<int, int>> GetSummonsRange();
	std::vector<std::pair<int, int>> GetRangerRange();
	std::vector<std::pair<int, int>> GetBallistaRange();
	std::vector<std::pair<int, int>> GetDebuffTowerRange();







};

