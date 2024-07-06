#pragma once
#include "Entity.h"
#include "DataContainer.h"
#include "TileObject.h"

//class StageStruct;

typedef enum class TileOnUnitState
{
	None,	//해당 타일은 비어있음
	Move,	// 타일을 향에 유닛이 가고있음
	Take	// 해당 타일을 유닛이 점거했음
}U_TileState;

class TileInfo
{
public:
	Engine::Entity::Entity* GetEntity()
	{
		return m_pEntity;
	}
	TileOnUnitState GetTileOnUnitState()
	{
		return E_TileUnitState;
	}
	/// <summary>
	/// 해당 타일로 유닛이 소환됩니다.
	/// </summary>
	/// <param name="_entity"></param>
	Engine::Entity::Entity* SpawnUnit(int _unitID);
	/// <summary>
	/// 해당 타일을 향해 유닛이 이동중입니다.
	/// </summary>
	/// <param name="_entity"></param>
	bool UnitToTile(Engine::Entity::Entity* _entity);
	/// <summary>
	/// 해당 타일을 유닛이 점거했습니다.
	/// </summary>
	/// <param name="_entity"></param>
	bool UnitTakeTile(Engine::Entity::Entity* _entity);

	void TileReset()
	{
		m_pEntity = nullptr;
		m_UnitID = NULL;
		E_TileUnitState = U_TileState::None;
	}

	void TileMove()
	{
		E_TileUnitState = U_TileState::Move;
	}

	void SetGridPos(UINT _x, UINT _y)
	{
		m_GridX = _x;
		m_GridY = _y;
		m_tile.SetGridPos(_x, _y);
	}

	UINT GetGridX() { return m_GridX; }
	UINT GetGridY() { return m_GridY; }

	TileObject* GetTile() { return &m_tile; }
	void SetUnitID(int _unitID) { m_UnitID = _unitID; }
	void SetUnit(Engine::Entity::Entity* _entity)
	{
		m_pEntity = _entity;
		E_TileUnitState = U_TileState::Take;
	}
	int GetUnitID() { return m_UnitID; }

public:
	TileOnUnitState E_TileUnitState = U_TileState::None;

private:
	Engine::Entity::Entity* m_pEntity = nullptr;
	UINT m_GridX, m_GridY;
	TileObject m_tile;
	int m_UnitID = NULL;
	int m_ObjectID = NULL;
};



class TileManager
{
public:
	TileManager() {}
	~TileManager()	{}

public:
	int round = 0;
	void SetRound(int r) { round = r; }

	bool Initialize();
	void Finalize() {  }

	TileInfo& GetTileInfo(UINT _x, UINT _y);
	void SetNextRound();
	UINT GetGridX() { return m_GridX; } // 전체 타일 x길이를 반환합니다.
	UINT GetGridY() { return m_GridY; } // 전체 타일 y길이를 반환합니다.
	std::vector<std::vector<TileInfo>>& GetTileMap() { return m_TileMap; };
	std::vector<Engine::Entity::Entity*>* GetTileObjects() { return &m_TileObjects; }
	std::vector<Engine::Entity::Entity*>* GetUnits ()
	{
		return &m_Units;
	}
	void SetRound();
	void ShowAttackRange();
	void BattleEnd()
	{
		m_bIsBattle = false;
	}
	void ShopEnd()
	{
		m_bIsBattle = true;
	}
	bool IsBattle()
	{
		return m_bIsBattle;
	}
	void SpawnUnit(UINT _x, UINT _y, int _unitID)
	{
		Engine::Entity::Entity* entity = GetTileInfo(_x, _y).SpawnUnit(_unitID);
		m_CreateUnits.push_back(entity);
		m_Units.push_back(entity);
	}

	Engine::Entity::Entity* SpawnObject(UINT _x, UINT _y, int _unitID, Dir _dir);
	void SpawnObject(Engine::Entity::Entity* _entity)
	{
		m_CreateUnits.push_back(_entity);
	}

	// [4,5] [5,5]
	
	void SetLeftOverTeamCost(int _LeftOverTeam) { m_LeftOverTeamCost = _LeftOverTeam; }
	void SetLeftOverEnemyCost(int _LeftOverEnemy) { m_LeftOverEnemyCost = _LeftOverEnemy; }
	void SetDeadEnemyCost(int _DeadEnemy) { m_DeadEnemyCost = _DeadEnemy; }
	void SetLeftOverEnemyCount(int _enemyCount) {
		m_LeftOverEnemyCount = _enemyCount;
	}

	int GetLeftOverTeamCost() { return m_LeftOverTeamCost; }
	int GetLeftOverEnemyCost() { return m_LeftOverEnemyCost; }
	int GetDeadEnemyCost() { return m_DeadEnemyCost; }
	int GetLeftOverEnemyCount() {
		return m_LeftOverEnemyCount;
	}

	void SetBattleState(bool _isGameOver) { m_bIsBattleOver = _isGameOver; }
	bool GetBattleState() { return m_bIsBattleOver; }
	std::vector<Engine::Entity::Entity*>& GetCreateUnits()
	{
		return m_CreateUnits;
	}
	void ClearCreateUnits()
	{
		m_CreateUnits.clear();
	}
	void SetDefaultTileColor();

	void SetAlltile();

private:
	//TileInfo* m_TileMap;
	RoundStruct m_Stage;
	UINT m_CurrentRound;
	bool m_bIsStageClear;
	UINT m_GridX, m_GridY;
	std::vector<std::vector<TileInfo>> m_TileMap;
	std::vector<Engine::Entity::Entity*> m_TileObjects;
	std::vector<Engine::Entity::Entity*> m_Units;

	std::vector<Engine::Entity::Entity*> m_CreateUnits;

	bool m_bIsBattle = false;
	bool m_bIsBattleOver = false;

	int m_LeftOverTeamCost = 0;
	int m_LeftOverEnemyCost = 0;
	int m_DeadEnemyCost = 0;
	int m_LeftOverEnemyCount = 0;
};

