#pragma once
#include "../GameProcess/Scene.h"

class TileManager;
class ShopSystem;
class BattleSystem;
class System;

class Camera;
class Player;

class TestScene2 : public Engine::Scene
{
public:
	TestScene2() {};
	~TestScene2() {};

public:
	void Initialize() override;
	void Finalize() override;

	Engine::Entity::Entity* player;
	Player* m_pPlayer;
	TileManager* m_pTileManager;

	Engine::Entity::Entity* m_Tile;

	void Start() override;
	void FixedUpdate() override;

	void Update() override;
	void LateUpdate() override;

private:
	ShopSystem* m_pShopSystem;
	BattleSystem* m_pBattleSystem;
	System* m_pCurrSystem;

};

