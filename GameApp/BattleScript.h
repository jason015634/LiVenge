#pragma once
#include "Script.h"
#include <vector>
#include <string>

class BattleScript : public Script
{
public:
	BattleScript() {}
	~BattleScript() {}

public:
	virtual void Start() {};
	virtual void FixedUpdate() {};
	virtual void Update();
	virtual void LateUpdate() {};
	virtual void Finalize() {};

	std::vector<Engine::Entity::Entity*>& GetAttackTargets();

private:
	void DefaultAttack();
	void DebuffTower();

	void SetLookDir();
	void SetAttackTarget();

private:
	void BaseUpdate();
	void UpdateIdle();
	void UpdateMove();
	void DetectTarget();
	void UpdateAttack();
	void UpdateDie();

	void UpdateAnim();
	void UpdateAnimDir(Dir _dir);

private:
	double m_AttackTime = D3D10_FLOAT32_MAX;
	double m_MoveDistanceX = 0, m_MoveDistanceY = 0;

	Position m_LookPosition = { 0,1 };

	double m_MaxHP = 0;

	Engine::Entity::Entity* m_myTarget;
	std::vector<Engine::Entity::Entity*> m_attackTargets;

	double m_curAtkTime = 0.f;
	double m_curMoveTime = 0.f;

	double m_AtkDelay = 0.f;
	double m_MoveDelay = 0.f;

	Position m_myPos = {};
	State m_battleState = State::Idle;
	Dir m_lookDir = Dir::DOWN;
	Dir m_moveDir = Dir::Max;

	std::wstring m_AnimDummyName = L"";
	std::wstring m_AnimName = L"";

	bool m_bIsGameStart = false;
	bool m_bIsStart = false;

};

