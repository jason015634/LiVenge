#pragma once
#include "DataContainer.h"
#include "BattleInfo.h"
#include "TileManager.h"

#include <memory>
#include <map>

class BattleField
{
public:
	static BattleField& GetInstance()
	{
		static std::shared_ptr<BattleField> m_instance = std::make_shared<BattleField>();
		return *m_instance;
	}

	void Update();
	void Init(TileManager* _tileManager);
	 
	void SetRound();
	void SetTakeTile(unsigned int _x, unsigned int _y, Engine::Entity::Entity* _entity);
	void SetResetTile(unsigned int _x, unsigned int _y);
	void SetMoveTile(unsigned int _x, unsigned int _y);
	void SetEntity(Engine::Entity::Entity* _entity);

	TileManager* GetTimeManager() 
	{
		return m_StaticTileManager;
	}
	std::vector<std::pair<int, int>> GetSearchAround(int x, int y);

	std::vector<Engine::Entity::Entity*> GetAttackRange(std::vector<std::pair<int, int>> _range, Engine::Entity::Entity* _entity);

public:
	std::vector<Engine::Entity::Entity*> m_TeamUnit;
	std::vector<Engine::Entity::Entity*> m_EnemyUnit;
	bool isBattleStart = false;

private:
	int m_roundIndex = 0;

	std::map<int, StageStruct> m_FieldData;
	TileManager* m_StaticTileManager = nullptr;
};
