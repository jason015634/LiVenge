#pragma once
#include "System.h"
#include "framework.h"

class TileManager;
class ReRollButton;
class ShopLevelUpButton;
class TestUnit;
class Player;
class DataManager;
class MouseDragSys;
class UnitFactoryUI;
class UnitCard;
class GameStartButton;
class HpBar;
class ManaBar;
class Shop;
class Shop2;
class Shop3;
class SellButton;
class UnitStatUI;
class UnitStatFactory;

class ShopSystem : public System
{
public:
	ShopSystem(TileManager* _tileManager) :
		m_pTileManager(_tileManager)
	{
		Unit1Percent = 0;
		Unit2Percent = 0;
		Unit3Percent = 0;
		Unit4Percent = 0;
		Unit5Percent = 0;
	}
	~ShopSystem()
	{}
private:
	std::vector<std::pair<int, int*>> m_FirstRoundUnits;
	std::vector<std::pair<int, int*>> m_SecondRoundUnits;
	std::vector<std::pair<int, int*>> m_FinalRoundUnits;
	// ������ ���̴� ���ֵ�
	std::vector <int> m_LayoutUnitList;

	// �ʵ忡 ��ġ�Ǵ� ���ֵ�
	std::vector<int> m_FieldUnitList;
	int m_ShopLevel = 0;
	const int m_MaxShopLevel = 3;
	int MaxUnit = 4;
public:
	bool Initialize(const std::vector<Engine::Entity::Entity*>* _entities) override;
	void Finalize() override {} 

private:
	void SetRoundUnit();
	// ������ ������ ���� ��ġ (5,6,7)
	void UnitStoreLayout();

	// ������ �ʿ��� ���
	// ��� �ȱ�
	void DeleteUnit(int _i, int _j);
	void SummonUnitClick(int _unitID);
	// ���� ���׷��̵�
	void ShopUpgrade();

	// ���� ����
	void ShopReset();

	// ���� �̵�
	void UnitMove();

	// ���� â ����
	void UnitStat();
	// ü�� ����
	void OnDamage(float _damage);
	void OnHeal(float _restoreHP);
	void UpdateHpBar(float _beforeHP, float _afterHP);
	void HpBarState();
	float lerp(float _lerpStart, float _lerpEnd, float _lerpFactor);

	// ���� ����
	void UseMana(float _usedMana);
	void GainMana(float _gainedMana);
	void UpdateManaBar(float _beforeMP, float _afterMP);
	void MpBarState();
public:
	std::vector<Engine::Entity::Entity*>& GetShopEntity() { return m_ShopEntity; }
	std::vector <UnitCard*>& GetUnitCardList() { return m_UnitCardList; }
	std::vector <UnitStatUI*>& GetUnitStatList() { return m_UnitStatUIList; }
	TileManager* GetTileManager() { return m_pTileManager; }
public:
	void Update() override;
	void LateUpdate() override;
private:
	//int UnitID[5];

	int Unit1ID = 101;
	int Unit2ID = 102;
	int Unit3ID = 103;
	int Unit4ID = 104;
	int Unit5ID = 105;

	int Unit1Percent;
	int Unit2Percent;
	int Unit3Percent;
	int Unit4Percent;
	int Unit5Percent;
	const int m_ReRollCost = 5;
	int m_ShopUpgradeCost = 20;

	// HP ����
	float lerpStart = 0;
	float lerpEnd = 0;
	float reductionSum = 0.0f;
private:
	bool m_bIsReRoll = true;
	bool m_bIsKeyAway = false;
	bool m_bIsUpdateHpBar = false;
	bool m_bIsDamage = false;
	bool m_bIsUpdateManaBar = false;
	bool m_bIsUse = false;
	bool m_bUnitStat = false;
	Player* m_pPlayer;
	TileManager* m_pTileManager;
	ReRollButton* m_ReRollButton;
	ShopLevelUpButton* m_ShopLevelUpButton;
	GameStartButton* m_pGameStartButton;
	TestUnit* m_TestUnit;
	UnitStatUI* m_pUnitStatUI;
	UnitFactoryUI* m_pUnitFactoryUI;
	UnitStatFactory* m_pUnitStatFactory;
	HpBar* m_pHpBar;
	ManaBar* m_pManaBar;
	Shop* m_pShop;
	Shop2* m_pShop2;
	Shop3* m_pShop3;
	SellButton* m_pSellButton;
	Engine::Entity::Entity* m_pDragUnit = nullptr;
private:
	std::vector<Engine::Entity::Entity*> m_ShopEntity;
	std::vector <UnitCard*> m_UnitCardList;
	std::vector <UnitStatUI*> m_UnitStatUIList;
};

