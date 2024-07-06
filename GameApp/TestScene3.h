#pragma once
#include "../GameProcess/Scene.h"
#include "TileManager.h"
#include "Camera.h"
#include "Player.h"

#include <vector>

class TestUnit;
// class SoundMgr;

enum class AttackType
{
	None,
	ShortRangeAttack,   // 근거리
	LongRangeAttack,    // 장거리
	Drain,              // 드레인
	Projectile,         // 투사체
	Summons,			// 소환수
	Line,				// 공격타워
	DebufTower,			// 디버프타워
};

enum class Dir1
{
	Up,
	Down,
	Left,
	Right
};

class player;

class TestScene3 : public Engine::Scene
{
public:
	TestScene3() {};
	~TestScene3() {};

public:
	Player* m_pPlayer;
	void Initialize() override;
	void Finalize() override;

	void Start() override;
	void FixedUpdate() override;

	void Update() override; 
	void LateUpdate() override;

	// Attack Range
	std::vector<std::pair<int, int>> ShortRange(int _x, int _y);
	std::vector<std::pair<int, int>> LongRange(int _x, int _y);
	std::vector<std::pair<int, int>> DrainRange(int _x, int _y);
	std::vector<std::pair<int, int>> ProjectileRange(int _x, int _y);
	std::vector<std::pair<int, int>> SummonsRange(int _x, int _y);
	std::vector<std::pair<int, int>> LineRange(int _x, int _y);
	std::vector<std::pair<int, int>> DebufRange(int _x, int _y);


	// Util
	std::vector<std::pair<int, int>> RotatePoints(const std::vector<std::pair<int, int>>& _points, Dir1 _dir);

public:
	AttackType FindAttackType(int _id);
	void FindAttackRange(int _x, int _y, int _id);
	
public:
	Engine::Entity::Entity* m_Effect;
	std::vector<std::pair<int, int>> m_coordinateVec;

	TileManager m_tileManager;
	Camera m_Camera;
	//TestUnit* m_pPlayer;
//	SoundMgr* m_pSound;
};
