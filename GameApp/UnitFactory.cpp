#include "UnitFactory.h"
#include "Entity.h"
#include "UnitList.h"
#include "DataManager.h"
#include "LogicAnimation.h"

Unit* UnitFactory::CreateEntity(int _UnitID)
{
	Unit* entity = new Unit();
	entity->GetComponent<UnitStatus>()->SetUnitStatus(_UnitID);
	// todo : ╬ж╢о╦чюл╪г цъ╟║
	entity->GetComponent<Engine::Component::Animator>()->
		SetResourcePath(DataManager::GetInstance().m_AnimDatas[_UnitID].m_Path);
	entity->GetComponent<Engine::Component::Animator>()->
		m_AnimationAsset = &DataManager::GetInstance().m_AnimDatas[_UnitID];
	entity->GetComponent<Engine::Component::Animator>()->SetOffset(-100, -150);

	entity->GetComponent<Engine::Component::EffectAnimator>()->SetScale(5,5,1);
	entity->GetComponent<Engine::Component::EffectAnimator>()->SetOffset(-15, -20);

	switch (_UnitID)
	{
	case 101:
		entity->GetComponent<BattleInfo>()->SetAttackRange(GetSwordRange());
		entity->GetComponent<Engine::Component::EffectAnimator>()->SetState(L"Team_Melee");
		entity->m_EntityName = L"Team_Melee";

		entity->GetComponent<Engine::Component::EffectAnimator>()->SetScale(9, 9, 1);
		break;
	case 102:
		entity->GetComponent<BattleInfo>()->SetAttackRange(GetArrowRange());
		entity->GetComponent<Engine::Component::EffectAnimator>()->SetState(L"Arrow");
		entity->m_EntityName = L"Team_Arrow";

		break;
	case 103:
		entity->GetComponent<BattleInfo>()->SetAttackRange(GetDrainRange());
		entity->GetComponent<Engine::Component::EffectAnimator>()->SetState(L"Drain");
		entity->m_EntityName = L"Team_Drain";

		entity->GetComponent<Engine::Component::Animator>()->SetOffset(-220, -230);
		entity->GetComponent<UnitStatus>()->Unit_MultiAttack = true;

		break;
	case 104:
		entity->GetComponent<BattleInfo>()->SetAttackRange(GetProjectileRange());
		entity->GetComponent<Engine::Component::EffectAnimator>()->SetState(L"Projectile");

		entity->GetComponent<Engine::Component::Animator>()->SetOffset(-130, -190);

		entity->m_EntityName = L"Team_Projectile";

		break;
	case 105:
		entity->GetComponent<BattleInfo>()->SetAttackRange(GetSummonerRange());
	// entity->GetComponent<Engine::Component::EffectAnimator>()->SetState(L"");
		entity->m_EntityName = L"Team_Summoner";

		break;
	case 115:
		entity->GetComponent<BattleInfo>()->SetAttackRange(GetSummonsRange());
		entity->GetComponent<Engine::Component::EffectAnimator>()->SetState(L"Summon");
		entity->m_EntityName = L"Team_Summons";

		break;
	case 201:
		entity->GetComponent<BattleInfo>()->SetAttackRange(GetSwordRange());
		entity->GetComponent<Engine::Component::EffectAnimator>()->SetState(L"Enemy_Melee");
		entity->m_EntityName = L"Enemy_Melee";
		entity->GetComponent<Engine::Component::EffectAnimator>()->SetScale(9, 9, 1);

		break;
	case 202:
		entity->GetComponent<BattleInfo>()->SetAttackRange(GetArrowRange());
		entity->GetComponent<Engine::Component::EffectAnimator>()->SetState(L"Arrow");
		entity->m_EntityName = L"Enemy_Arrow";

		break;
	case 203:
		entity->GetComponent<BattleInfo>()->SetAttackRange(GetRangerRange());
		entity->GetComponent<Engine::Component::EffectAnimator>()->SetState(L"Enemy_Hero");
		entity->GetComponent<Engine::Component::Animator>()->SetOffset(-225, -170);

		entity->m_EntityName = L"Enemy_Hero";
		entity->GetComponent<UnitStatus>()->Unit_MultiAttack = true;

		break;
	case 204:
		entity->GetComponent<BattleInfo>()->SetAttackRange(GetBallistaRange());
		entity->GetComponent<Engine::Component::EffectAnimator>()->SetState(L"Arrow_Tower");
		entity->m_EntityName = L"Enemy_Tower";

		entity->GetComponent<Engine::Component::Animator>()->SetOffset(-90, -120);

		break;
	case 205:
		entity->GetComponent<BattleInfo>()->SetAttackRange(GetDebuffTowerRange());
		entity->GetComponent<Engine::Component::EffectAnimator>()->SetState(L"Debuff_Tower");
		entity->m_EntityName = L"Enemy_Debuff";

		entity->GetComponent<Engine::Component::Animator>()->SetOffset(-70, -210);

		break;
	case 301:
		entity->GetComponent<Engine::Component::Animator>()->SetOffset(-80,-90);
		entity->m_EntityName = L"Obstacle";

		entity->GetComponent<Engine::Component::Animator>()->SetResourcePath(L"..\\Resource/Object_Sprite.png");
		//Object_Sprite.png
		break;
	default:
		SAFE_DELETE(entity);
		break;
	}
	return entity;
}


std::vector<std::pair<int, int>> UnitFactory::GetSwordRange()
{
	std::vector<std::pair<int, int>> outPutVec = {};

	outPutVec.push_back({ - 1 , 0 }); // аб
	outPutVec.push_back({ 1 ,  0}); // ©Л
	outPutVec.push_back({ 0 , 0 - 1 }); // ╩С
	outPutVec.push_back({ 0 , 0 + 1 }); // го

	return outPutVec;
}

std::vector<std::pair<int, int>> UnitFactory::GetArrowRange()
{
	std::vector<std::pair<int, int>> outPutVec;

	outPutVec.push_back({ 0 - 1, 0 - 1 });
	outPutVec.push_back({ 0 - 1, 0 + 1 });
	outPutVec.push_back({ 0 + 1, 0 - 1 });
	outPutVec.push_back({ 0 + 1, 0 + 1 });

	outPutVec.push_back({ 0 - 1 , 0 }); // аб
	outPutVec.push_back({ 0 + 1 , 0 }); // ©Л
	outPutVec.push_back({ 0     , 0 - 1 }); // ╩С
	outPutVec.push_back({ 0     , 0 + 1 }); // го

	outPutVec.push_back({ 0 - 2 , 0 - 1 }); // аб2
	outPutVec.push_back({ 0 - 2 , 0 + 1 });
	outPutVec.push_back({ 0 - 2 , 0 });

	outPutVec.push_back({ 0 + 2 , 0 - 1 }); // ©Л2
	outPutVec.push_back({ 0 + 2 , 0 + 1 });
	outPutVec.push_back({ 0 + 2 , 0 });

	outPutVec.push_back({ 0 - 1 , 0 - 2 }); // ╩С2
	outPutVec.push_back({ 0 + 1 , 0 - 2 });
	outPutVec.push_back({ 0     , 0 - 2 });

	outPutVec.push_back({ 0 - 1 , 0 + 2 }); // го2
	outPutVec.push_back({ 0 + 1 , 0 + 2 });
	outPutVec.push_back({ 0     , 0 + 2 });
	return outPutVec;
}

std::vector<std::pair<int, int>> UnitFactory::GetDrainRange()
{
	std::vector<std::pair<int, int>> outPutVec;
	outPutVec.push_back({ 0 - 1, 0 });
	outPutVec.push_back({ 0 - 1, 0 - 1 });
	outPutVec.push_back({ 0    , 0 - 1 });
	outPutVec.push_back({ 0 + 1, 0 - 1 });
	outPutVec.push_back({ 0 + 1, 0 });

	return outPutVec;
}

std::vector<std::pair<int, int>> UnitFactory::GetProjectileRange()
{
	std::vector<std::pair<int, int>> outPutVec;

	for (int i = 1; i < 3; i++)
	{
		outPutVec.push_back({ 0 - 1, 0 - i });
		outPutVec.push_back({ 0 + 1, 0 - i });
		outPutVec.push_back({ 0    , 0 - i });
	}

	return outPutVec;
}

std::vector<std::pair<int, int>> UnitFactory::GetSummonerRange()
{
	std::vector<std::pair<int, int>> outPutVec;
	outPutVec.push_back({ 0 - 1, 0 - 1 });
	outPutVec.push_back({ 0 - 1, 0 + 1 });
	outPutVec.push_back({ 0 + 1, 0 - 1 });
	outPutVec.push_back({ 0 + 1, 0 + 1 });

	outPutVec.push_back({ 0 - 1 , 0 }); // аб
	outPutVec.push_back({ 0 + 1 , 0 }); // ©Л
	outPutVec.push_back({ 0     , 0 - 1 }); // ╩С
	outPutVec.push_back({ 0     , 0 + 1 }); // го
	return outPutVec;

}

std::vector<std::pair<int, int>> UnitFactory::GetSummonsRange()
{
	std::vector<std::pair<int, int>> outPutVec;
	outPutVec.push_back({ 0 - 1, 0 - 1 });
	outPutVec.push_back({ 0 - 1, 0 + 1 });
	outPutVec.push_back({ 0 + 1, 0 - 1 });
	outPutVec.push_back({ 0 + 1, 0 + 1 });

	outPutVec.push_back({ 0 - 1 , 0 }); // аб
	outPutVec.push_back({ 0 + 1 , 0 }); // ©Л
	outPutVec.push_back({ 0     , 0 - 1 }); // ╩С
	outPutVec.push_back({ 0     , 0 + 1 }); // го
	return outPutVec;
}

std::vector<std::pair<int, int>> UnitFactory::GetRangerRange()
{
	std::vector<std::pair<int, int>> outPutVec;
	outPutVec.push_back({ 0 - 1, 0 - 1 });
	outPutVec.push_back({ 0 - 1, 0 + 1 });
	outPutVec.push_back({ 0 + 1, 0 - 1 });
	outPutVec.push_back({ 0 + 1, 0 + 1 });

	outPutVec.push_back({ 0 - 1 , 0 }); // аб
	outPutVec.push_back({ 0 + 1 , 0 }); // ©Л
	outPutVec.push_back({ 0     , 0 - 1 }); // ╩С
	outPutVec.push_back({ 0     , 0 + 1 }); // го
	return outPutVec;
}

std::vector<std::pair<int, int>> UnitFactory::GetBallistaRange()
{
	std::vector<std::pair<int, int>> outPutVec;

	/*for (int i = 1; i < (m_tileManager.GetTileMap().size()); i++)
	{
		outPutVec.push_back({ 0    , 0 - i });
	}*/

	return outPutVec;
}

std::vector<std::pair<int, int>> UnitFactory::GetDebuffTowerRange()
{
	std::vector<std::pair<int, int>> outPutVec;

	outPutVec.push_back({ 0 - 1, 0 - 1 });
	outPutVec.push_back({ 0 - 1, 0 + 1 });
	outPutVec.push_back({ 0 + 1, 0 - 1 });
	outPutVec.push_back({ 0 + 1, 0 + 1 });

	outPutVec.push_back({ 0 - 1 , 0 }); // аб
	outPutVec.push_back({ 0 + 1 , 0 }); // ©Л
	outPutVec.push_back({ 0     , 0 - 1 }); // ╩С
	outPutVec.push_back({ 0     , 0 + 1 }); // го

	outPutVec.push_back({ 0 - 2 , 0 - 1 }); // аб2
	outPutVec.push_back({ 0 - 2 , 0 + 1 });
	outPutVec.push_back({ 0 - 2 , 0 });

	outPutVec.push_back({ 0 + 2 , 0 - 1 }); // ©Л2
	outPutVec.push_back({ 0 + 2 , 0 + 1 });
	outPutVec.push_back({ 0 + 2 , 0 });

	outPutVec.push_back({ 0 - 1 , 0 - 2 }); // ╩С2
	outPutVec.push_back({ 0 + 1 , 0 - 2 });
	outPutVec.push_back({ 0     , 0 - 2 });

	outPutVec.push_back({ 0 - 1 , 0 + 2 }); // го2
	outPutVec.push_back({ 0 + 1 , 0 + 2 });
	outPutVec.push_back({ 0     , 0 + 2 });

	outPutVec.push_back({ 0 - 2 , 0 + 2 });
	outPutVec.push_back({ 0 - 2 , 0 + 2 });
	outPutVec.push_back({ 0 + 2 , 0 - 2 });
	outPutVec.push_back({ 0 + 2 , 0 - 2 });
	return outPutVec;

}