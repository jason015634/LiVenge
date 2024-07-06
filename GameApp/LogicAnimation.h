#pragma once
#include "Script.h"
#include <d2d1_1.h>

class Engine::Component::Transform;

enum class AnimState
{
	Idle,
	Move,
	Damaged,
	Die,
	Max
};

class LogicAnimation : public Script
{
public:
	LogicAnimation() {}
	~LogicAnimation() {}
public:
	virtual void Start();
	virtual void FixedUpdate() {};
	virtual void Update();
	virtual void LateUpdate();
	virtual void Finalize();

	void IdleAnimUpdate(float _percentY, float _speed);
	void MoveAnimUpdate(float _percentX, float _percentY, float _speedX, float _speedY);

	void DamagedAnimUpdate();
	void DieAnimUpdate();

	void MakeDamagedBitmap();
	void SetAnimName(std::wstring _animName);

	void StateUpdate(AnimState _state);

public:
	// 필수 구현부
public:

	static const ULONGLONG ComponentType = -1;

	static const ULONGLONG ComponentFlag = 1 << ComponentType;

	// --------------필수 구현부---------------------
private:
	
	ULONGLONG m_Damagedtime = 0;
	float m_alpha = 1.f;

	float m_cosNumY = 1;
	float m_cosNumX = 1;

	float m_scaleY = 1;
	float m_scaleX = 1;

	bool m_isIncreaseScaleY = false;
	bool m_isIncreaseScaleX = false;
	bool m_isWhite = false;

	bool m_stateArr[static_cast<int>(AnimState::Max)] = {false, };

	ID2D1Bitmap* m_pAnimBitmap = nullptr;
	ID2D1Bitmap* m_pDamagedAnimBitmap = nullptr;

	std::wstring m_AnimationName = L"Idle";
	std::wstring m_AnimationCheck;
	bool m_bAnimState = true;

};