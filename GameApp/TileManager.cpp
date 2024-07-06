#include "TileManager.h"
#include "TileObject.h"
#include "DataContainer.h"
#include "ComponentList.h"
#include "UnitFactory.h"
#include "AttackObjectFactory.h"
#include "DataManager.h"
#include "Unit.h"
#include "Player.h"

bool TileManager::Initialize()
{
	std::vector<StageStruct> m_StageData = DataManager::GetInstance().m_StageData;

	m_Stage = DataManager::GetInstance().m_StageData[0].roundData[round];
	m_CurrentRound = 0;
	m_bIsStageClear = false;
	SetRound();
	
	
	return true;
}

TileInfo& TileManager::GetTileInfo(UINT _x, UINT _y)
{
	return m_TileMap[_y][_x];
}

void TileManager::SetNextRound()
{
	/*m_CurrentRound++;
	if (m_CurrentRound >= m_Stage)
	{
		m_CurrentRound = m_Stage.roundData.size();
		m_bIsStageClear = true;
		return;
	}*/
	SetRound();
}

void TileManager::SetRound()
{
	m_GridX = m_Stage.grid_x;
	m_GridY = m_Stage.grid_y;

	std::vector<TileInfo> tile;
	for (size_t y = 0; y < m_GridY; y++)
	{
		tile.clear();
		tile.reserve(m_GridX);
		for (size_t x = 0; x < m_GridX; x++)
		{
			tile.emplace_back();
			tile.back().SetGridPos(x, y);
			if ((x + y) & 1)
			{
				tile[x].GetTile()->SetColor(m_Stage.tileColor_One);
			}
			else
			{
				tile[x].GetTile()->SetColor(m_Stage.tileColor_Two);
			}
		}
		m_TileMap.push_back(tile);
	}

	for (int y = 0; y < m_TileMap.size();y++)
	{
		for (int x = 0; x < m_TileMap[y].size(); x++)
		{
			m_TileObjects.push_back(m_TileMap[y][x].GetTile());
		}
	}
	
	for (auto data : m_Stage.tileMapData)
	{
		SpawnUnit(data.x, data.y, data.unit_id);
	}


	int p = 0;
	for (int i = 6; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (GetTileInfo(j, i).GetEntity() == nullptr &&
				 p < Player::GetInstance()->m_Unit.size())
			{
				SpawnUnit(j, i, Player::GetInstance()->m_Unit[p]);
				p++;
			}
		}
	}

	Player::GetInstance()->m_Unit.clear();

	// test code
	//for (int i = 0; i < 5; i++)
	//{
	//	int j = 1;
	//	/*if (i & 1)
	//	{
	//		j += 1;
	//	}*/
	//	j *= 100;
	//	j += 1;

	//	SpawnUnit(i, 8, 301);
	//}
}

void TileManager::ShowAttackRange()
{
	SetDefaultTileColor();
	for (auto tile : m_TileObjects)
	{
		Engine::Entity::Entity* entity = nullptr;
		if (tile->GetComponent<Engine::Component::Collider>()->GetMouseColl())
		{
			tile->GetComponent<Engine::Component::Rectangle>()->SetAlpha(0.5);
			entity = m_TileMap[tile->GetComponent<Tile>()->GetGy()][tile->GetComponent<Tile>()->GetGx()].GetEntity();
			
		}
		if (entity == nullptr)
		{
			continue;
		}
		for (auto range : entity->GetComponent<BattleInfo>()->GetAttackRange())
		{
			int x = entity->GetComponent<BattleInfo>()->GetFieldPosition().X + range.first;
			int y = entity->GetComponent<BattleInfo>()->GetFieldPosition().Y + range.second;
			if (x < 0 || y < 0 || x >= m_GridX || y >= m_GridY)
			{
				continue;
			}
			D2D1_COLOR_F c = m_TileMap[y][x].GetTile()->GetComponent<Engine::Component::Rectangle>()->GetColor();

			m_TileMap[y][x].GetTile()->GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
		}
	}
}

Engine::Entity::Entity* TileManager::SpawnObject(UINT _x, UINT _y, int _unitID, Dir _dir)
{
	AttackObjectFactory aft;
	Engine::Entity::Entity* entity = (Engine::Entity::Entity*)aft.CreateEntity(_unitID, _x, _y, _dir);
	entity->GetComponent<Engine::Component::Transform>()->SetPosition(_x * 150, _y * 150);
	m_CreateUnits.push_back(entity);
	return entity;
}

void TileManager::SetDefaultTileColor()
{
	for (size_t y = 0; y < m_GridY; y++)
	{
		for (size_t x = 0; x < m_GridX; x++)
		{
			if ((x + y) & 1)
			{
				m_TileMap[y][x].GetTile()->GetComponent<Engine::Component::Rectangle>()->SetColor(m_Stage.tileColor_One);
			}
			else
			{
				m_TileMap[y][x].GetTile()->GetComponent<Engine::Component::Rectangle>()->SetColor(m_Stage.tileColor_Two);
			}
			m_TileMap[y][x].GetTile()->GetComponent<Engine::Component::Rectangle>()->ReSetAlpha();
		}
	}
}

void TileManager::SetAlltile()
{
	for (auto& tileY : m_TileMap)
	{
		for (auto& tileX : tileY)
		{
			if (tileX.GetEntity() == nullptr)
			{
				tileX.TileReset();
				continue;
			}
			if (tileX.GetEntity()->GetComponent<BattleInfo>()->IsDead() == true)
			{
				//tileX.GetEntity()->SetActive(false);
				tileX.TileReset();
			}
			if (tileX.GetTileOnUnitState() == TileOnUnitState::Move)
			{
				GetTileInfo(tileX.GetEntity()->GetComponent<BattleInfo>()->GetFieldPosition().X, tileX.GetEntity()->GetComponent<BattleInfo>()->GetFieldPosition().Y).TileReset();
				if (tileX.GetEntity()->GetComponent<BattleInfo>()->IsDead())
				{
					tileX.TileReset();
					continue;
				}
				tileX.GetEntity()->GetComponent<BattleInfo>()->SetFieldPosition(tileX.GetGridX(), tileX.GetGridY());

				tileX.UnitTakeTile(tileX.GetEntity());
			}
		}
	}
	

}

//-------------------------------------------------------------------------

/// <summary>
/// 해당 타일로 유닛이 소환됩니다.
/// </summary>
/// <param name="_entity"></param>
Engine::Entity::Entity* TileInfo::SpawnUnit(int _unitID)
{
	// 나중에 주석 풀것
	/*if (_entity == nullptr)
	{
		LOG_ERROR(L"entity spawn fail");
		return false;
	}*/
	if (_unitID < 100 || _unitID > 400)
	{
		return nullptr;
	}

	if (m_pEntity != nullptr)
	{
		return m_pEntity;
	}
	m_UnitID = _unitID;
	E_TileUnitState = U_TileState::Take;

	UnitFactory unitFactory;
	Unit* entity = unitFactory.CreateEntity(_unitID);
	entity->px = m_GridX;
	entity->py = m_GridY;
	m_pEntity = entity;
	return m_pEntity;

}

/// <summary>
/// 해당 타일을 향해 유닛이 이동중입니다.
/// </summary>
/// <param name="_entity"></param>
bool TileInfo::UnitToTile(Engine::Entity::Entity* _entity)
{
	/*if (_entity == nullptr)
	{
		LOG_ERROR(L"entity move fail");
		return false;
	}*/
	if (m_pEntity != nullptr && E_TileUnitState == U_TileState::Take)
	{
		return false;
	}
	if (m_pEntity != nullptr && E_TileUnitState == U_TileState::Move)
	{
		if (m_pEntity->GetComponent<UnitStatus>()->GetUnitTeamID() ==
			_entity->GetComponent<UnitStatus>()->GetUnitTeamID())
		{
			return false;
		}

		if (m_pEntity->GetComponent<UnitStatus>()->GetMoveSpeed() <=
			_entity->GetComponent<UnitStatus>()->GetMoveSpeed())
		{
			m_pEntity->GetComponent<BattleInfo>()->SetState(State::Idle);
			E_TileUnitState = U_TileState::Move;
			m_pEntity = _entity;
			return true;
		}
		return false;
	}
	m_pEntity = _entity;
	E_TileUnitState = U_TileState::Move;
	return true;
}

/// <summary>
/// 해당 타일을 유닛이 점거했습니다.
/// </summary>
/// <param name="_entity"></param>

bool TileInfo::UnitTakeTile(Engine::Entity::Entity* _entity)
{
	/*if (_entity == nullptr)
	{
		LOG_ERROR(L"entity move fail");
		return false;
	}*/
	m_pEntity = _entity;
	E_TileUnitState = U_TileState::Take;
	return true;
}

//GetTileInfo(3, 3).E_TileUnitState = take;
//GetTileInfo(3, 3).E_TileUnitState = none;
