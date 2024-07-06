#include "BattleSystem.h"
#include "BattleField.h"
#include "TileManager.h"
#include <iostream>

bool BattleSystem::Initialize(const std::vector<Engine::Entity::Entity*>* _entities)
{
//	/*for (auto entity : *_entities)
//	{
//		SetEntity(entity);
//	}*/
//	return true;
	return true;
}

void BattleSystem::Finalize()
{

}
//
//// 아군 적군 그룹짓는 로직.
//void BattleSystem::SetEntity(Engine::Entity::Entity* _entity)
//{
//	m_Entities.push_back(_entity);
//
//	int teamId = m_Entities.back()->GetComponent<UnitStatus>()->GetUnitTeamID();
//
//	if (teamId == 1)
//	{
//		m_TeamUnit.push_back(_entity);
//		return;
//	}
//	if (teamId == 2)
//	{
//		m_EnemyUnit.push_back(_entity);
//		return;
//	}
//}
//
//// 적을 쫓기
//void BattleSystem::SetChaseTarget(std::vector<Engine::Entity::Entity*>& _unit, std::vector<Engine::Entity::Entity*>& _target)
//{
//	for (auto team : _unit)
//	{
//		if (team->GetComponent<BattleInfo>()->GetState() != State::Idle)
//		{
//			continue;
//		}
//		if (team->GetComponent<BattleInfo>()->GetChaseTarget() != nullptr)
//		{
//			if (team->GetComponent<BattleInfo>()->
//				GetChaseTarget()->GetComponent<BattleInfo>()->IsDead() == false)
//			{
//				if (m_pTool->m_Random.GetRandomNumber() & 1)
//				{
//					team->GetComponent<BattleInfo>()->SetChaseTarget(nullptr);
//				}
//			}
//			else
//			{
//				team->GetComponent<BattleInfo>()->SetChaseTarget(nullptr);
//			}
//		}
//
//		if (team->GetComponent<BattleInfo>()->GetChaseTarget() != nullptr)
//		{
//			continue;
//		}
//
//
//		Engine::Entity::Entity* target = nullptr;
//		//UINT finalDistance = UINT_MAX;
//		/*for (auto Enemy : _target)
//		{
//			if (Enemy->GetActive() == false || Enemy->GetComponent<BattleInfo>()->IsDead() == true)
//			{
//				continue;
//			}
//			UINT distance = team->GetComponent<BattleInfo>()->GetOtherUnitDistance(Enemy->GetComponent<BattleInfo>()->GetFieldPosition());
//			if (finalDistance > distance)
//			{
//				target = static_cast<Entity*>(Enemy);
//				finalDistance = distance;
//			}
//			 todo : 수정 필요
//			if (finalDistance == distance)
//			{
//				if (m_pTool->m_Random.GetRandomNumber() & 1)
//				{
//					target = static_cast<Entity*>(Enemy);
//				}
//			}
//		}*/
//		
//		for (size_t i = 0; i < 10; i++)
//		{
//			target = _target[m_pTool->m_Random.GetRandomNumber(_target.size() - 1)];
//
//			if (target->GetActive() == false || target->GetComponent<BattleInfo>()->IsDead() == true)
//			{
//				target = nullptr;
//			}
//		}
//		team->GetComponent<BattleInfo>()->SetChaseTarget(target);
//	}
//
//}
//
//void BattleSystem::SetAttackTarget(std::vector<Engine::Entity::Entity*>& _unit)
//{
//	for (auto unit : _unit)
//	{
//		if (unit->GetComponent<BattleInfo>()->GetState() != State::Idle)
//		{
//			continue;
//		}
//		unit->GetComponent<BattleInfo>()->ResetAttackTarget();
//
//		Engine::Entity::Entity* target = nullptr;
//
//		for (auto range : unit->GetComponent<BattleInfo>()->GetAttackRange())
//		{
//			int x = unit->GetComponent<BattleInfo>()->GetFieldPosition().X + range.first;
//			int y = unit->GetComponent<BattleInfo>()->GetFieldPosition().Y + range.second;
//			auto a = m_pTileManager->GetGridX();
//
//			if (x < 0 || y < 0 || x >= m_pTileManager->GetGridX() || y >= m_pTileManager->GetGridY())
//			{
//				continue;
//			}
//
//			target = m_pTileManager->GetTileInfo(x, y).GetEntity();
//			
//			if (target == nullptr)
//			{
//				continue;
//			}
//
//			// 타겟이 이미죽었거나, 타겟이 아군이거나, 타겟이 오브젝트일때
//			if (target->GetComponent<BattleInfo>()->IsDead() == true ||
//				target->GetComponent<UnitStatus>()->GetUnitTeamID() == 
//				  unit->GetComponent<UnitStatus>()->GetUnitTeamID() ||
//				target->GetComponent<UnitStatus>()->GetUnitTeamID() > 2)
//			{
//				continue;
//			}
//
//			unit->GetComponent<BattleInfo>()->SetAttackTarget(target);
//		}
//	}
//}

//void BattleSystem::SetMoveGrid(std::vector<Engine::Entity::Entity*>& _unit)
//{
//	for (auto unit : _unit)
//	{
//		if (unit->GetComponent<BattleInfo>()->GetState() != State::Idle)
//		{
//			continue;
//		}
//
//		UINT x = unit->GetComponent<BattleInfo>()->GetMoveGrid().X;
//		UINT y = unit->GetComponent<BattleInfo>()->GetMoveGrid().Y;
//
//		if (x < m_pTileManager->GetGridX() &&
//			y < m_pTileManager->GetGridY() &&
//			x >= 0 && 
//			y >= 0 )
//		{
//			if (m_pTileManager->GetTileInfo(x, y).UnitToTile(unit) == true)
//			{
//				unit->GetComponent<BattleInfo>()->SetState(State::Move);
//			}
//			else
//			{
//				unit->GetComponent<BattleInfo>()->SetChaseTarget(nullptr);
//			}
//		}	
//	}
//}
//
////void BattleSystem::UnitAttack(std::vector<Engine::Entity::Entity*>& _unit)
////{
////	for (auto unit : _unit)
////	{
////		if (unit->GetComponent<BattleInfo>()->GetState() == State::Move ||
////			unit->GetComponent<BattleInfo>()->GetAttackTarget().empty())
////		{
////			continue;
////		}
////
////		unit->GetComponent<BattleInfo>()->SetState(State::Attack);
////
////		if (unit->GetComponent<UnitStatus>()->Unit_MultiAttack == false)
////		{
////			unit->GetComponent<BattleInfo>()->GetAttackTarget().front()->GetComponent<UnitStatus>()->UnitGetDamage(unit->GetComponent<UnitStatus>()->GetAttack());
////		}
////		else
////		{
////			for (auto target : unit->GetComponent<BattleInfo>()->GetAttackTarget())
////			{
////				target->GetComponent<UnitStatus>()->UnitGetDamage(unit->GetComponent<UnitStatus>()->GetAttack());
////			}
////		}
////	}
////}
//
//bool BattleSystem::IsRoundEnd()
//{
//	bool isTeamAllDead = true;
//	bool isEnemyAllDead = true;
//
//	for (auto team : m_TeamUnit)
//	{
//		if (team->GetComponent<BattleInfo>()->IsDead() == false)
//		{
//			isTeamAllDead = false;
//			m_TotalTeamCost += team->GetComponent<UnitStatus>()->Unit_LifeCost;
//		}
//
//	}
//	for (auto enemy : m_EnemyUnit)
//	{
//		if (enemy->GetComponent<BattleInfo>()->IsDead() == false)
//		{
//			isEnemyAllDead = false;
//			m_TotalEnemyCost += enemy->GetComponent<UnitStatus>()->Unit_LifeCost;
//		}
//		else if (enemy->GetComponent<BattleInfo>()->IsDead() == true)
//		{
//			m_DeadEnemyCost += enemy->GetComponent<UnitStatus>()->Unit_LifeCost;
//		}
//	}
//	m_pTileManager->SetLeftOverTeamCost(m_TotalTeamCost);
//	m_pTileManager->SetLeftOverEnemyCost(m_TotalEnemyCost);
//	m_pTileManager->SetDeadEnemyCost(m_DeadEnemyCost);
//	return ((isTeamAllDead || isEnemyAllDead) == true);
//}
//
//void BattleSystem::FixedUpdate()
//{
//	if (m_bIsBattleStart == false)
//	{
//		m_TeamUnit.clear();
//		m_EnemyUnit.clear();
//		m_Entities.clear();
//		m_bIsBattleStart = true;
//		for (const auto& unit : *m_pTileManager->GetUnits())
//		{
//			SetEntity(unit);
//			unit->GetComponent<BattleInfo>()->SetStop(false);
//		}
//		m_pTileManager->SetDefaultTileColor();
//	}
//
//	if (IsRoundEnd())
//	{
//		for (auto& unit : m_Entities)
//		{
//			unit->GetComponent<BattleInfo>()->SetStop(true);
//			if (unit->GetComponent<BattleInfo>()->IsDead() == true)
//			{
//				unit->SetActive(false);
//				unit->GetComponent<BattleInfo>()->IsDeadComplate();
//			}
//		}
//		m_pTileManager->SetBattleState(true);
//		m_bIsBattleStart = false;
//		m_pTileManager->BattleEnd();
//	}
//}

void BattleSystem::Update()
{
	BattleField::GetInstance().Update();

	//// 일시정지 조건
	//m_pTileManager->ShowAttackRange();

	//if (m_pTool->m_Input.IsKeyTap(KEY::SPACE))
	//{
	//	m_bIsGameStop = !m_bIsGameStop;

	//	for (auto& unit : m_Entities)
	//	{
	//		unit->GetComponent<BattleInfo>()->SetStop(m_bIsGameStop);
	//	}
	//}	
	//else
	//{
	//	if (m_bIsGameStop == false)
	//	{
	//		SetChaseTarget(m_TeamUnit, m_EnemyUnit);
	//		SetChaseTarget(m_EnemyUnit, m_TeamUnit);
	//		SetAttackTarget(m_Entities);
	//		SetMoveGrid(m_Entities);

	//		// debug
	//		if (GetAsyncKeyState('B') & 0x8000)
	//		{
	//			for (auto& unit : m_Entities)
	//			{
	//				std::cout << (int)unit->GetComponent<BattleInfo>()->GetState() << " ";
	//			}
	//			std::cout << std::endl;
	//		}
	//		// ---------
	//	}
	//}
}
//
//void BattleSystem::LateUpdate()
//{
//	
//
//	for (auto& unit : m_Entities)
//	{
//		BattleInfo& bt = *unit->GetComponent<BattleInfo>();
//		if (bt.IsDead())
//		{
//			continue;
//		}
//
//	}
//}