#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

public:
	void Initialize() override;
	static Player* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new Player();
		}

		return Instance;
	}

public:
	int playerMana = 100;
	int MaxMP = 100;
	int playerHP = 100;
	int MaxHP = 100;
public:
	// 마나 차감
	void UseMana(int _usedMana)
	{
		playerMana -= _usedMana;
	}

	void GainMana(int _gainedMana)
	{
		playerMana += _gainedMana;
	}

	void LoseHP(int _lostHP)
	{
		playerHP -= _lostHP;
	}

	void RestoreHP(int _restoredHP)
	{
		playerHP += _restoredHP;
	}

	int GetCurMana() { return playerMana; }
	int GetCurHP() { return playerHP; }

	bool IsPlayerDead()
	{
		if (playerHP <= 0)
		{
			return true;
		}
		return false;
	}

	void SetPlayer()
	{
		playerMana = 100;
		MaxMP = 100;
		playerHP = 100;
		MaxHP = 100;
	}

private:
	static Player* Instance;

public:
	std::vector<int> m_Unit;
};

