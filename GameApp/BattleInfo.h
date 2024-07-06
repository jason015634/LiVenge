#pragma once
#include "CustomComponent.h"
#include <iostream>
#include <cmath>

struct Position
{
	int X = 0, Y = 0;
	Position operator -(const Position _obj)
	{
		return {(X - _obj.X),(Y - _obj.Y)};
	}
	void Reset()
	{
		X = Y = 0;
	}
};

enum class Dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	Max
};

enum class State
{
	Idle,
	Move,
	Attack,
	Die,
};

class BattleInfo : public CustomComponent
{

public:
	BattleInfo() {}
	~BattleInfo() {}
	
public:

	static const ULONGLONG ComponentType = (ULONGLONG)E_CustomComponent::BattleInfo;

	static const ULONGLONG ComponentFlag = 1 << ComponentType;

	// --------------필수 구현부---------------------

public:
	Position& GetFieldPosition()
	{
		return m_FieldPosition;
	}
	void SetFieldPosition(int _x,int _y)
	{
		m_FieldPosition = { _x,_y };
	}

	//void AddFieldPosition(int _x, int _y)
	//{
	//	m_FieldPosition.X += _x;
	//	m_FieldPosition.Y += _y;
	//}
	
	void SetChaseTarget(Engine::Entity::Entity* _target)
	{
		m_pChaseTarget = _target;
		SetChaseDistance();
	}
	void SetAttackTarget(Engine::Entity::Entity* _target)
	{
		m_AttackTarget.push_back(_target);
	}
	void ResetAttackTarget()
	{
		m_AttackTarget.clear();
	}

	Engine::Entity::Entity* GetChaseTarget()
	{
		SetChaseDistance();
		return m_pChaseTarget;
	}
	std::vector<Engine::Entity::Entity*>& GetAttackTarget()
	{
		return m_AttackTarget;
	}

	void SetState(State _state)
	{
		m_State = _state;
		if (m_State == State::Idle)
		{
			std::cout << "Idle\n";
		}
	}
	State GetState() { return m_State; }

	void SetDead() { m_bIsDead = true; }
	void SetDeadComplate() { m_bIsDeadComplate = true; }
	void SetDamaged(bool _damaged) { m_bIsDamaged = _damaged; }

	// todo 변경 필요
	bool IsDead() { return m_bIsDead ; }
	bool IsDeadComplate() { return m_bIsDeadComplate; }
	bool IsDamaged() { return m_bIsDamaged; }

	// UnitMove
	UINT GetOtherUnitDistance(Position _pos)
	{
		Position distance = m_FieldPosition - _pos;
		return (std::labs(distance.X) + std::labs(distance.Y));
	}

	void SetChaseDistance();
	Position GetChaseDistance()
	{
		SetChaseDistance();
		return m_ChaseDistance;
	}
	/// <summary>
	/// 유닛이 그리드상 이동해야할 방향을 리턴합니다.
	/// </summary>
	/// <returns></returns>
	Position GetMoveDirection()
	{
		return m_MoveDirection;
	}
	void SetMoveDistance(int _x, int _y)
	{
		m_MoveDistance = { _x,_y };
	}
	Position& GetMoveDistance()
	{
		return m_MoveDistance;
	}
	/// <summary>
	/// 현재 유닛이 바라보는 방향을 리턴합니다.
	/// </summary>
	/// <returns></returns>
	Dir GetDirection()
	{
		return m_Direction;
	}
	void SetDirection(Dir _dir)
	{
		m_Direction = _dir;
	}
	// 유닛이 이동할 그리드상의 좌표를 반환합니다.
	Position GetMoveGrid()
	{
		SetMoveGrid();
		SetMoveDistance(m_MoveGrid.X * 150, m_MoveGrid.Y * 150);
		return m_MoveGrid;
	}
	Position GetFeildPos()
	{
		return m_FieldPosition;
	}

	void SetMoveGrid()
	{
		m_MoveGrid = { m_FieldPosition.X + m_MoveDirection.X,
					   m_FieldPosition.Y + m_MoveDirection.Y };
	}

	void SetMoveGrid(int _x, int _y)
	{
		m_MoveGrid = { _x,_y };
	}

	// UnitAttack
	void SetAttackRange(std::vector<std::pair<int, int>> _range)
	{
		m_AttackRange = std::move(_range);
	}
	std::vector<std::pair<int, int>> GetAttackRange();

	void Reset()
	{
		m_pChaseTarget = nullptr;
		m_AttackTarget.clear();
	}
	
	void SetStop(bool _stop) { m_bIsStop = _stop; }
	bool IsStop() { return m_bIsStop; }

std::wstring GetAnimName() { return m_animName; }
	void SetAnimName(std::wstring _name) { m_animName = _name; }Engine::Entity::Entity* GetSpawnObject()
	{
		Engine::Entity::Entity* en = nullptr;
		if (m_SpawnObject != nullptr)
		{
			en = m_SpawnObject;
			m_SpawnObject = nullptr;
		}
		return en;
	}
	Engine::Entity::Entity* GetSpawnUnit()
	{
		Engine::Entity::Entity* en = nullptr;
		if (m_SpawnUnit != nullptr)
		{
			en = m_SpawnUnit;
			m_SpawnUnit = nullptr;
		}
		return en;
	}
private:
	Position m_ChaseDistance; // 추적 유닛과의 그리드거리
	Position m_MoveDirection; // 유닛이 이동해야할 방향
	Position m_MoveDistance;  // 유닛이 이동해야할 좌표상 거리
	Position m_MoveGrid;	// 유닛이 이동해야할 그리드상 좌표
	Dir m_Direction; // 현재 유닛이 보고있는 방향

	Position m_FieldPosition;
	Engine::Entity::Entity* m_pChaseTarget = nullptr;
	std::vector<Engine::Entity::Entity*> m_AttackTarget;
	bool m_bIsDead = false;
	bool m_bIsDeadComplate = false;
	bool m_bIsDamaged = false;

	/// <summary>
	/// x,	y
	/// </summary>
	std::vector<std::pair<int, int>> m_AttackRange;
	State m_State = State::Idle;

std::wstring m_animName = L"";
Engine::Entity::Entity* m_SpawnObject = nullptr;
	Engine::Entity::Entity* m_SpawnUnit = nullptr;
public:
	bool m_bIsMoveComplate = true;

private:
	bool m_bIsStop = false;
	
};

