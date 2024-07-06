#include "BattleField.h"
#include "DataContainer.h"
#include "DataManager.h"
#include <map>

void BattleField::Update()
{
	isBattleStart = true;

	for (const auto& unit : *m_StaticTileManager->GetUnits())
	{
		SetEntity(unit);
	//	unit->GetComponent<BattleInfo>()->SetStop(false);
	}
	m_StaticTileManager->SetDefaultTileColor();
}

void BattleField::Init(TileManager* _tileManager)
{
	m_TeamUnit.clear();
	m_EnemyUnit.clear();

	m_StaticTileManager = _tileManager;
}

void BattleField::SetRound()
{
	for (int i = DataManager::GetInstance().m_StageData.size() - 1; i >= 0; i--)
	{
		m_FieldData[i] = DataManager::GetInstance().m_StageData.back();
		DataManager::GetInstance().m_StageData.pop_back();
	}
}

void BattleField::SetTakeTile(unsigned int _x, unsigned int _y, Engine::Entity::Entity* _entity)
{
	if (_x >= 10 || _y >= 10) return;

	m_StaticTileManager->GetTileInfo(_x, _y).SetUnit(_entity);
}

void BattleField::SetResetTile(unsigned int _x, unsigned int _y)
{
	if (_x >= 10 || _y >= 10) return;

	m_StaticTileManager->GetTileInfo(_x, _y).TileReset();
}

void BattleField::SetMoveTile(unsigned int _x, unsigned int _y)
{
	if (_x >= 10 || _y >= 10) return;

	m_StaticTileManager->GetTileInfo(_x, _y).TileMove();
}


std::vector<Engine::Entity::Entity*> BattleField::GetAttackRange(std::vector<std::pair<int, int>> _range, Engine::Entity::Entity* _entity)
{
	std::vector<Engine::Entity::Entity*> myRange;

	for (auto& [_x, _y] : _range)
	{
		if (_x < 0 || _y < 0 || _x >= 10 || _y >= 10) continue;

		auto target = m_StaticTileManager->GetTileInfo(_x, _y).GetEntity();

		if (target == nullptr ||
			target->GetComponent<BattleInfo>()->IsDead() == true ||
			target->GetComponent<UnitStatus>()->GetUnitTeamID() ==
			_entity->GetComponent<UnitStatus>()->GetUnitTeamID() ||
			target->GetComponent<UnitStatus>()->GetUnitTeamID() > 2)
		{
			continue;
		}

		myRange.push_back(target);
	}
	return myRange;
}

// 아군 적군 그룹짓는 로직.
void BattleField::SetEntity(Engine::Entity::Entity* _entity)
{
	int teamId = _entity->GetComponent<UnitStatus>()->GetUnitTeamID();

	if (teamId == 1)
	{
		m_TeamUnit.push_back(_entity);
		return;
	}
	if (teamId == 2)
	{
		m_EnemyUnit.push_back(_entity);
		return;
	}
}

std::vector<std::pair<int, int>> BattleField::GetSearchAround(int x, int y)
{
	std::vector<std::pair<int, int>> aroundCango;

	if (x - 1 >= 0 && m_StaticTileManager->GetTileInfo(x - 1, y).GetTileOnUnitState() == TileOnUnitState::None)
		aroundCango.push_back({ x - 1, y });

	if (x + 1 < 10 && m_StaticTileManager->GetTileInfo(x + 1, y).GetTileOnUnitState() == TileOnUnitState::None)
		aroundCango.push_back({ x + 1, y });

	if (y - 1 >= 0 && m_StaticTileManager->GetTileInfo(x, y - 1).GetTileOnUnitState() == TileOnUnitState::None)
		aroundCango.push_back({ x, y - 1 });

	if (y + 1 < 10 && m_StaticTileManager->GetTileInfo(x, y + 1).GetTileOnUnitState() == TileOnUnitState::None)
		aroundCango.push_back({ x, y + 1 });

	return aroundCango;
}

/*
	Engine::Entity::Entity* target = nullptr;
	target = m_pTileManager->GetTileInfo(x, y).GetEntity();

// 타겟이 이미죽었거나, 타겟이 아군이거나, 타겟이 오브젝트일때

if (target->GetComponent<BattleInfo>()->IsDead() == true ||
	target->GetComponent<UnitStatus>()->GetUnitTeamID() ==
	unit->GetComponent<UnitStatus>()->GetUnitTeamID() ||
	target->GetComponent<UnitStatus>()->GetUnitTeamID() > 2)
{
	continue;
}
*/