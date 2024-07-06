#pragma once
#include "System.h"
#include "DataContainer.h"

class TileManager;
class BattleSystem : public System
{
public:
	BattleSystem(TileManager* _tileManager) :
		m_pTileManager(_tileManager)
	{}

//	BattleSystem(TileManager* _tileManager) :
//		m_pTileManager(_tileManager)
//	{
//	}
//	~BattleSystem()
//	{}
public:
	bool Initialize(const std::vector<Engine::Entity::Entity*>* _entities) override;
	void Finalize() override;
//	void SetEntity(Engine::Entity::Entity* _entity) override;
//
//
//private:
//	void SetChaseTarget(std::vector<Engine::Entity::Entity*>& _unit, std::vector<Engine::Entity::Entity*>& _target);
//	void SetAttackTarget(std::vector<Engine::Entity::Entity*>& _unit);
//	void SetMoveGrid(std::vector<Engine::Entity::Entity*>& _unit);
//
//	//	void UnitAttack(std::vector<Engine::Entity::Entity*>& _unit);
//
//
//	bool IsRoundEnd();
//
public:
	void Update() override;
//	void FixedUpdate() override;
//	void LateUpdate() override;


private:
	TileManager* m_pTileManager;
//	std::vector<Engine::Entity::Entity*> m_TeamUnit;
//	std::vector<Engine::Entity::Entity*> m_EnemyUnit;


//public:
//	UINT m_Width, m_Height;


//private:
//	bool m_bIsBattleStart = false;
//	int m_TotalTeamCost = 0;
//	int m_TotalEnemyCost = 0;
//	int m_DeadEnemyCost = 0;


//private:
//	bool m_bIsGameStop = false;
	int m_LeftEnemyCount = 0;
private:
	bool m_bIsBattleStart = false;
	int m_TotalTeamCost = 0;
	int m_TotalEnemyCost = 0;
	int m_DeadEnemyCost = 0;};



