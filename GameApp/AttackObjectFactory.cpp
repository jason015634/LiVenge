#include "AttackObjectFactory.h"
#include "AttackObject.h"
#include "DataManager.h"

AttackObject* AttackObjectFactory::CreateEntity(int _UnitID, int _x, int _y, Dir _direction)
{
	AttackObject* a = new AttackObject();
	a->GetComponent<BattleInfo>()->SetFieldPosition(_x,_y);
	a->GetComponent<BattleInfo>()->SetDirection(_direction);


	// 투사체일경우
	if (_UnitID == 104)// (int)DataManager::GetInstance().m_UnitDatas[104].unit_atk)
	{
		a->GetComponent<BattleInfo>()->SetAttackRange(ProfRange());
		a->GetComponent<UnitStatus>()->SetMoveSpeed(10);
		a->GetComponent<UnitStatus>()->SetAttack(DataManager::GetInstance().m_UnitDatas[104].unit_atk);
		a->GetComponent<UnitStatus>()->SetUnitTeam(1);

	}

	else
	{
		SAFE_DELETE(a);
	}

	return a;
}

std::vector<std::pair<int, int>> AttackObjectFactory::ProfRange()
{
	std::vector<std::pair<int, int>> rg;
	rg.push_back({-1,0});
	rg.push_back({ 0,0 });
	rg.push_back({ 0,1 });

	return rg;
}
