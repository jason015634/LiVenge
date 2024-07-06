#include "UnitStatus.h"
#include "DataManager.h"


UnitStatus* UnitStatus::SetUnitStatus(int _unitID)
{
	/*if (DataManager::GetInstance().m_UnitDatas.find(_unitID) == DataManager::GetInstance().m_UnitDatas.end())
	{
		LOG_ERROR(L"UnitStatus : UnitID Error ");
		return nullptr;
	}*/
	//auto data2 = DataManager::GetInstance().m_UnitDatas;
	UnitSaveData data = DataManager::GetInstance().m_UnitDatas[_unitID];
	Unit_ID = _unitID;
	Unit_Name;
	Unit_Team;
	Unit_ManaCost = data.manaCost;
	Unit_LifeCost = data.lifeCost;
	// todo : ¼öÁ¤¿ä¸Á
	Unit_AttackSpeed = data.unit_atkSp / 100;

	Unit_Team_ID = _unitID / 100;
	Unit_Attack = data.unit_atk;
	Unit_HP = data.unit_hp;
	Unit_MaxHP = data.unit_hp;
	Unit_Defense = data.unit_defense;
	Unit_MoveSpeed = data.unit_moveSp;
	return this;
}
