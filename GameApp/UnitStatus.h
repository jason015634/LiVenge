#pragma once
#include "CustomComponent.h"
#include <string>

class UnitStatus : public CustomComponent
{
public:
	UnitStatus() {}
	~UnitStatus() {}

public:
	// 필수 구현부
public:

	static const ULONGLONG ComponentType = (ULONGLONG)E_CustomComponent::UnitStatus;

	static const ULONGLONG ComponentFlag = 1 << ComponentType;

	// --------------필수 구현부---------------------
	int GetUnitID() { return Unit_ID; }
	/// <returns>1 == team, 2 == enemy, 3 == object</returns>
	int GetUnitTeamID() { return Unit_Team_ID; }

	UnitStatus* SetUnitStatus(int _unitID);

	double GetMoveSpeed()
	{
		double Speed = Unit_MoveSpeed + Effect_MoveSpeed;
		if (Speed < 0)
		{
			return 0;
		}
		return Speed / 100;
	};
	void UnitGetDamage(double _damage)
	{
		double damage = _damage - Unit_Defense;

		if (damage < 0)
		{
			damage = 1;
		}
		Unit_HP -= damage;
	}
	bool IsUnitDead()
	{
		if (Unit_HP <= 0)
		{
			return true;
		}
		return false;
	}
	double GetAttack()
	{
		return Unit_Attack;
	}
	// 데미지를 설정합니다.
	void SetAttack(double _attack)
	{
		Unit_Attack = _attack;
	}

	void EffectReset()
	{
		Effect_MoveSpeed = 0;
	}
	void SetEffectMoveSpeed(double _speed)
	{
		Effect_MoveSpeed += _speed;
	}
	double GetAttackSpeed()
	{
		return Unit_AttackSpeed;
	}
	void HealthyDrain(double _drainPoint)
	{
		Unit_HP += _drainPoint;
		if (Unit_HP > Unit_MaxHP)
		{
			Unit_HP = Unit_MaxHP;
		}
	}
	void SetUnitID(int _ID)
	{
		Unit_ID = _ID;
	}

	void SetMoveSpeed(double _spd)
	{
		Unit_MoveSpeed = _spd;
	}

	void SetUnitTeam(int _team)
	{
		Unit_Team_ID = _team;
	}

public:
	int				Unit_ManaCost;
	int				Unit_LifeCost;
private:
	int				Unit_ID = 0;
	std::wstring	Unit_Name;
	std::wstring	Unit_Team;
	int				Unit_Team_ID;
	double			Unit_Attack;
	double			Unit_AttackSpeed;
	double			Unit_HP;
	double			Unit_Defense;
	double			Unit_MoveSpeed;
	double			Unit_MaxHP;

public:
	bool			Unit_MultiAttack = false;
	double			Effect_MoveSpeed = 0; // buff + debuff


};



