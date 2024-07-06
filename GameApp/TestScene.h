#pragma once
#include "../GameProcess/Scene.h"
#include "DataContainer.h"

class ShopSystem;
class BattleSystem;
class System;
class Camera;
class Player;
class GameStartButton;
class TestUnit;
class MouseDragSys;
class ReRollButton;
class ShopLevelUpButton;
class TileManager;
class Shop;
class HpBar;
class ManaBar;
class SellButton;
class Shop2;
class Shop3;
class TestScene : public Engine::Scene
{

public:
	TestScene() {};
	~TestScene() {};

public:
	void Initialize() override;
	void Finalize() override;

	void Start() override;
	void FixedUpdate() override;

	void Update() override;
	void LateUpdate() override;

public:
	void RoundFail();
	void RoundClear();
private:
	Engine::Entity::Entity tile[100];
	Engine::Entity::Entity* m_BgTop;
	Shop* m_pShop;
	Shop2* m_pShop2;
	Shop3* m_pShop3;
	ShopSystem* m_pShopSystem;
	BattleSystem* m_pBattleSystem;
	System* m_pCurrSystem;

	Camera* m_pCamera;
	Player* m_pPlayer;
	MouseDragSys* m_pMouseSystem; // 필요없을거같음

	ReRollButton* m_pReRollButton;
	ShopLevelUpButton* m_pShopLevelUpButton;
	GameStartButton* m_pGameStartButton;
	SellButton* m_pSellButton;

	TestUnit* m_TestUnit;
	TileManager* m_pTileManager;

	HpBar* m_pHpBar;
	ManaBar* m_pManaBar;
private:
	D2D1_RECT_F m_PlayerRect;
	D2D1_RECT_F m_UIRect;
	POINT prevMousePos;

	int KeyTapCount = 0;
	bool IsDragging = false;
	bool IsKeyTap = false;

private:
	TileStruct m_TileStruct;
	bool m_bIsRoundClear = false;
	bool m_bIsGameStart = false;
	bool m_BIsBattle;
};

struct Vector3
{
	FLOAT X;
	FLOAT Y;
	FLOAT Z;
};