#include "ShopSystem.h"
#include "Player.h"
#include "ReRollButton.h"
#include "ShopLevelUpButton.h"
#include "TestUnit.h"
#include "TileManager.h"
#include "TileObject.h"
#include "DataManager.h"
#include "MouseDragSys.h"
#include "UnitFactoryUI.h"
#include "UnitCard.h"
#include "GameStartButton.h"
#include "HpBar.h"
#include "ManaBar.h"
#include "Shop.h"
#include "Shop2.h"
#include "Shop3.h"
#include "SellButton.h"
#include "UnitStatFactory.h"
#include "UnitStatUI.h"
#include <iostream>
#include <cmath>

bool ShopSystem::Initialize(const std::vector<Engine::Entity::Entity*>* _entities)
{
    ULONGLONG GameObjectFlag = 0;
    GameObjectFlag = Engine::Component::GameObject::ComponentFlag;

    for (const auto& a : *_entities)
    {
        if ((a->GetComponentFlag() & GameObjectFlag) == GameObjectFlag)
        {
            if (a->GetComponent<Engine::Component::GameObject>()->GetTag() == L"Player")
            {
                m_pPlayer = (Player*)a;
            }
            if (a->GetComponent<Engine::Component::GameObject>()->GetTag() == L"TestUnit")
            {
                m_TestUnit = (TestUnit*)a;
            }

            if (a->GetComponent<Engine::Component::GameObject>()->GetTag() == L"ReRollButton")
            {
                m_ReRollButton = (ReRollButton*)a;
            }
            if (a->GetComponent<Engine::Component::GameObject>()->GetTag() == L"ShopLevelUpButton")
            {
                m_ShopLevelUpButton = (ShopLevelUpButton*)a;
            }
            if (a->GetComponent<Engine::Component::GameObject>()->GetTag() == L"GameStartButton")
            {
                m_pGameStartButton = (GameStartButton*)a;
            }
            if (a->GetComponent<Engine::Component::GameObject>()->GetTag() == L"HpBar")
            {
                m_pHpBar = (HpBar*)a;
            }
            if (a->GetComponent<Engine::Component::GameObject>()->GetTag() == L"ManaBar")
            {
                m_pManaBar = (ManaBar*)a;
            }
            if (a->GetComponent<Engine::Component::GameObject>()->GetTag() == L"Shop")
            {
                m_pShop = (Shop*)a;
            }
            if (a->GetComponent<Engine::Component::GameObject>()->GetTag() == L"SellButton")
            {
                m_pSellButton = (SellButton*)a;
            }
            if (a->GetComponent<Engine::Component::GameObject>()->GetTag() == L"Shop2")
            {
                m_pShop2 = (Shop2*)a;
            }
            if (a->GetComponent<Engine::Component::GameObject>()->GetTag() == L"Shop3")
            {
                m_pShop3 = (Shop3*)a;
            }
        }
    }
    
    m_pShop2->GetComponent<Engine::Component::UI>()->SetActive(false);
    m_pShop3->GetComponent<Engine::Component::UI>()->SetActive(false);
    m_pHpBar->GetComponent<Engine::Component::Transform>()->SetPosition(390.f, 100.f, 1);
    m_pManaBar->GetComponent<Engine::Component::Transform>()->SetPosition(392.f, 200.f, 1);

    for (int i = 0; i < 7; i++)
    {
        m_UnitCardList.push_back(m_pUnitFactoryUI->CreateUnitCard(101));
    }
    m_UnitCardList[5]->GetComponent<Engine::Component::UI>()->SetActive(false);
    m_UnitCardList[6]->GetComponent<Engine::Component::UI>()->SetActive(false);
    m_UnitCardList[5]->GetComponent<Engine::Component::Collider>()->SetActive(false);
    m_UnitCardList[6]->GetComponent<Engine::Component::Collider>()->SetActive(false);

    m_pUnitFactoryUI = new UnitFactoryUI();
    m_pUnitStatFactory = new UnitStatFactory();

    for (int i = 0; i < 5; i++)
    {
        m_UnitStatUIList.push_back(m_pUnitStatFactory->CreateUnitCard(101 + i));
        m_UnitStatUIList[i]->GetComponent<Engine::Component::UI>()->SetActive(false);
    }
    ShopUpgrade();
    SetRoundUnit();
    UnitStoreLayout();
    return true;
}
void ShopSystem::SetRoundUnit()
{
    if (m_ShopLevel == 1)
    {
        m_FirstRoundUnits.clear();
        m_FirstRoundUnits.push_back({ Unit1ID, & Unit1Percent});
        m_FirstRoundUnits.push_back({ Unit2ID, &Unit2Percent });
        m_FirstRoundUnits.push_back({ Unit3ID, &Unit3Percent });
    }
    else if (m_ShopLevel == 2)
    {
        m_SecondRoundUnits.push_back({ Unit1ID, &Unit1Percent });
        m_SecondRoundUnits.push_back({ Unit2ID, &Unit2Percent });
        m_SecondRoundUnits.push_back({ Unit3ID, &Unit3Percent });
        m_SecondRoundUnits.push_back({ Unit4ID, &Unit4Percent });
    }
    else if (m_ShopLevel == 3)
    {
        m_FinalRoundUnits.push_back({ Unit1ID, &Unit1Percent });
        m_FinalRoundUnits.push_back({ Unit2ID, &Unit2Percent });
        m_FinalRoundUnits.push_back({ Unit3ID, &Unit3Percent });
        m_FinalRoundUnits.push_back({ Unit4ID, &Unit4Percent });
        m_FinalRoundUnits.push_back({ Unit5ID, &Unit5Percent });
    }
}

void ShopSystem::UnitStoreLayout()
{
    m_LayoutUnitList.clear();
    switch (m_ShopLevel)
    {
    case 1:
        while (m_LayoutUnitList.size() < MaxUnit)
        {
            m_LayoutUnitList.push_back(m_pTool->m_Random.GetRandomNumber(m_FirstRoundUnits));
        }
        for (int i = 0; i < MaxUnit; i++)
        {
            m_UnitCardList[i]->GetComponent<Engine::Component::UI>()->SetActive(true);
            m_UnitCardList[i]->SetUnitID(m_LayoutUnitList[i]);
            m_UnitCardList[i]->GetComponent<Engine::Component::Transform>()->SetPosition(i * 215.5 + 188, 1623.f);
            m_UnitCardList[i]->GetComponent<Engine::Component::Collider>()->SetActive(true);
        }

        break;
    case 2:
        while (m_LayoutUnitList.size() < MaxUnit)
        {
            m_LayoutUnitList.push_back(m_pTool->m_Random.GetRandomNumber(m_SecondRoundUnits));
        }
        for (int i = 0; i < MaxUnit; i++)
        {
            m_UnitCardList[i]->SetUnitID(m_LayoutUnitList[i]);
            m_UnitCardList[i]->GetComponent<Engine::Component::Transform>()->SetPosition(i * 215.5 + 188, 1623.f);
            m_UnitCardList[i]->GetComponent<Engine::Component::UI>()->SetActive(true);
            m_UnitCardList[i]->GetComponent<Engine::Component::Collider>()->SetActive(true);
            if (m_pPlayer->GetCurMana() < m_UnitCardList[i]->m_UnitManaCost)
            {
                m_UnitCardList[i]->GetComponent<Engine::Component::UI>()->SetActive(false);
            }
        }
        break;
    case 3:
        while (m_LayoutUnitList.size() < MaxUnit)
        {
            m_LayoutUnitList.push_back(m_pTool->m_Random.GetRandomNumber(m_FinalRoundUnits));
        }
        for (int i = 0; i < MaxUnit; i++)
        {
            m_UnitCardList[i]->SetUnitID(m_LayoutUnitList[i]);
            m_UnitCardList[i]->GetComponent<Engine::Component::Transform>()->SetPosition(i * 215.5 + 188, 1623.f);
            m_UnitCardList[i]->GetComponent<Engine::Component::UI>()->SetActive(true);
            m_UnitCardList[i]->GetComponent<Engine::Component::Collider>()->SetActive(true);
            if (m_pPlayer->GetCurMana() < m_UnitCardList[i]->m_UnitManaCost)
            {
                m_UnitCardList[i]->GetComponent<Engine::Component::UI>()->SetActive(false);
            }
        }
        break;
    }
}

void ShopSystem::DeleteUnit(int _j, int _i)
{
    m_pTileManager->GetTileInfo(_j, _i).GetEntity()->SetActive(false);
    m_pTileManager->GetTileInfo(_j, _i).TileReset();
}

void ShopSystem::SummonUnitClick(int _unitID)
{
    for (int i = 6; i < m_pTileManager->GetTileMap().size(); i++)
    {
        for (int j = 0; j < m_pTileManager->GetTileMap().size(); j++)
        {
            if (m_pTileManager->GetTileInfo(j, i).GetEntity() == nullptr)
            {
                m_pTileManager->SpawnUnit(j, i, _unitID);
                UseMana(DataManager::GetInstance().m_UnitDatas[_unitID].manaCost);
                OnDamage(DataManager::GetInstance().m_UnitDatas[_unitID].lifeCost);
                MpBarState();
                HpBarState();
                std::cout << "현재 마나 : " << m_pPlayer->GetCurMana() << std::endl;
                std::cout << "현재 체력 : " << m_pPlayer->GetCurHP() << std::endl;
                std::cout << "ID : " << _unitID << std::endl;
                return;
            }
        }
    }
}

void ShopSystem::ShopUpgrade()
{
    if (m_ShopLevel < 3)
    {
        m_ShopLevel++;
        MaxUnit++;
    }
    else
        return;
    if (m_ShopLevel == 1)
    {
        Unit1Percent = 55;
        Unit2Percent = 30;
        Unit3Percent = 15;
        Unit4Percent = 0;
        Unit5Percent = 0;
    }
    else if (m_ShopLevel == 2)
    {
        Unit1Percent = 40.0f;
        Unit2Percent = 30.0f;
        Unit3Percent = 25.0f;
        Unit4Percent = 5.0f;
        Unit5Percent = 0.0f;    
        m_pShop->GetComponent<Engine::Component::UI>()->SetActive(false);
        m_pShop2->GetComponent<Engine::Component::UI>()->SetActive(true);
    }
    else if (m_ShopLevel == 3)
    {
        Unit1Percent = 20.0f;
        Unit2Percent = 24.0f;
        Unit3Percent = 31.0f;
        Unit4Percent = 20.0f;
        Unit5Percent = 5.0f;
        m_pShop2->GetComponent<Engine::Component::UI>()->SetActive(false);
        m_pShop3->GetComponent<Engine::Component::UI>()->SetActive(true);
    }
}

void ShopSystem::ShopReset()
{
    if (m_pPlayer->GetCurMana() < m_ReRollCost)
    {
        m_bIsReRoll = false;
        return;
    }
    m_bIsReRoll = true;

    UnitStoreLayout();
}

void ShopSystem::UnitMove()
{
    if (m_pDragUnit == nullptr)
    {
        for (int i = 6; i < m_pTileManager->GetTileMap().size(); i++)
        {
            for (int j = 0; j < m_pTileManager->GetTileMap().size(); j++)
            {
                if (m_pTileManager->GetTileInfo(j, i).GetTileOnUnitState() == TileOnUnitState::Take)
                {
                    if (m_pTileManager->GetTileInfo(j, i).GetTile()->GetComponent<Engine::Component::Collider>()->GetMouseColl())
                    {
                        if (m_pTool->m_Input.IsKeyTap(KEY::LBTN))
                        {
                            m_pDragUnit = m_pTileManager->GetTileInfo(j, i).GetEntity();
                            m_pTileManager->GetTileInfo(j, i).TileReset();
                            m_pDragUnit->m_bIsSelected = true;
                            return;
                        }
                    }
                }
            }
        }
    }
    else
    {
        m_pDragUnit->GetComponent<Engine::Component::Transform>()->SetPosition(m_pTool->m_Input.GetScreenMousePos().x, m_pTool->m_Input.GetScreenMousePos().y);
        for (int i = 6; i < m_pTileManager->GetTileMap().size(); i++)
        {
            for (int j = 0; j < m_pTileManager->GetTileMap().size(); j++)
            {
                if (m_pTileManager->GetTileInfo(j, i).GetTileOnUnitState() == TileOnUnitState::None)
                {
                    if (m_pTileManager->GetTileInfo(j, i).GetTile()->GetComponent<Engine::Component::Collider>()->GetMouseColl())
                    {
                        if (m_pTool->m_Input.IsKeyTap(KEY::LBTN))
                        {
                            m_pTileManager->GetTileInfo(j, i).SetUnit(m_pDragUnit);
                            m_pDragUnit->m_bIsSelected = false;
                            m_pDragUnit->GetComponent<BattleInfo>()->SetFieldPosition(j,i);
                            m_pDragUnit->GetComponent<Engine::Component::Transform>()->SetPosition(j * 150, i * 150);
                            m_pDragUnit = nullptr;
                            return;
                        }
                        
                    }
                }
            }
        }
    }
}
float ShopSystem::lerp(float _lerpStart, float _lerpEnd, float _lerpFactor)
{
    return _lerpStart + _lerpFactor * (_lerpEnd - _lerpStart);
}

void ShopSystem::UseMana(float _usedMana)
{
    m_bIsUse = true;
    if (m_pPlayer->playerMana <= 0) return;
    UpdateManaBar(m_pPlayer->playerMana, m_pPlayer->playerMana - _usedMana);
    m_pPlayer->playerMana -= _usedMana;
}

void ShopSystem::GainMana(float _gainedMana)
{
    m_bIsUse = false;
    if (m_pPlayer->playerMana >= 100) return;
    UpdateManaBar(m_pPlayer->playerMana, m_pPlayer->playerMana + _gainedMana);
    m_pPlayer->playerMana += _gainedMana;
}

void ShopSystem::UpdateManaBar(float _beforeMP, float _afterMP)
{
    m_bIsUpdateManaBar = true;
    lerpStart = _beforeMP / m_pPlayer->MaxMP;
    if (_afterMP == m_pPlayer->MaxMP)
    {
        lerpEnd = m_pPlayer->MaxMP;
    }
    else
    {
        lerpEnd = _afterMP / m_pPlayer->MaxMP;
    }
}

void ShopSystem::MpBarState()
{
    if (m_bIsUse && m_bIsUpdateManaBar)
    {
        float currentScaleX = m_pManaBar->GetComponent<Engine::Component::UI>()->m_Scale.X;
        float newScaleX = lerp(lerpStart, lerpEnd, currentScaleX);
        if (newScaleX < lerpEnd)
        {
            m_bIsUpdateManaBar = false;
        }
        else if(newScaleX >= lerpEnd)
        {
            D2D1_SIZE_F size = m_pManaBar->GetComponent<Engine::Component::UI>()->GetBitmapSize();
            m_pManaBar->GetComponent<Engine::Component::Transform>()->SetScaleOrigin(-(size.width / 2), 0);
            m_pManaBar->GetComponent<Engine::Component::Transform>()->m_Scale.X = newScaleX;
        }
    }
    else if (!m_bIsUse && m_bIsUpdateManaBar)
    {
        float currentScaleX = m_pManaBar->GetComponent<Engine::Component::UI>()->m_Scale.X;
        float newScaleX = lerp(lerpStart, lerpEnd, currentScaleX);
        if (newScaleX > lerpEnd)
        {
            m_bIsUpdateManaBar = false;
        }
        else if (newScaleX <= lerpEnd)
        {
            D2D1_SIZE_F size = m_pManaBar->GetComponent<Engine::Component::UI>()->GetBitmapSize();
            m_pManaBar->GetComponent<Engine::Component::Transform>()->SetScaleOrigin(-(size.width / 2), 0);
            m_pManaBar->GetComponent<Engine::Component::Transform>()->m_Scale.X = newScaleX;
        }
    }
}

void ShopSystem::UnitStat()
{
    for (int i = 0; i < m_pTileManager->GetGridY(); i++)
    {
        for (int j = 0; j < m_pTileManager->GetGridX(); j++)
        {
            if (m_pTileManager->GetTileInfo(j, i).GetTile()->GetComponent<Engine::Component::Collider>()->GetMouseColl())
            {
                for (const auto& a : m_UnitStatUIList)
                {
                    if (m_pTileManager->GetTileInfo(j, i).GetUnitID() == a->m_UnitID)
                    {
                        m_bUnitStat = true;
                        a->GetComponent<Engine::Component::UI>()->SetActive(true);
                        a->GetComponent<Engine::Component::Transform>()->SetPosition(m_pTileManager->GetTileInfo(j, i).GetEntity()->GetComponent<Engine::Component::Transform>()->m_Position.X - 100, m_pTileManager->GetTileInfo(j, i).GetEntity()->GetComponent<Engine::Component::Transform>()->m_Position.Y - 100, 1);
                    }
                    else
                    {
                        a->GetComponent<Engine::Component::UI>()->SetActive(false);
                        //a->GetComponent<Engine::Component::Transform>()->SetPosition(m_pTileManager->GetTileInfo(j, i).GetEntity()->GetComponent<Engine::Component::Transform>()->m_Position.X - 100, m_pTileManager->GetTileInfo(j, i).GetEntity()->GetComponent<Engine::Component::Transform>()->m_Position.Y - 100, 1);
                    }
                }
            }
        }
    }
}

void ShopSystem::OnDamage(float _damage)
{
    m_bIsDamage = true;
    if (m_pPlayer->playerHP <= 0) return;
    UpdateHpBar(m_pPlayer->playerHP, m_pPlayer->playerHP - _damage);
    m_pPlayer->playerHP -= _damage;
}

void ShopSystem::OnHeal(float _restoreHP)
{
    m_bIsDamage = false;
    if (m_pPlayer->playerHP >= 100)
    {
        return;
    }
    UpdateHpBar(m_pPlayer->playerHP, m_pPlayer->playerHP + _restoreHP);
    m_pPlayer->playerHP += _restoreHP;
}

void ShopSystem::UpdateHpBar(float _beforeHP, float _afterHP)
{
    m_bIsUpdateHpBar = true;
    lerpStart = _beforeHP / m_pPlayer->MaxHP;
    if (_afterHP == m_pPlayer->MaxHP)
    {
        lerpEnd = m_pPlayer->MaxHP;
    }
    else
    {
    lerpEnd = _afterHP / m_pPlayer->MaxHP;
    }
}

void ShopSystem::HpBarState()
{
    if (m_bIsDamage && m_bIsUpdateHpBar)
    {
        float currentScaleX = m_pHpBar->GetComponent<Engine::Component::UI>()->m_Scale.X;
        float newScaleX = lerp(lerpStart, lerpEnd, currentScaleX);
        if (newScaleX < lerpEnd)
        {
            m_bIsUpdateHpBar = false;
        }
        else if (newScaleX >= lerpEnd)
        {
            D2D1_SIZE_F size = m_pHpBar->GetComponent<Engine::Component::UI>()->GetBitmapSize();
            m_pHpBar->GetComponent<Engine::Component::Transform>()->SetScaleOrigin(-(size.width / 2), 0);
            m_pHpBar->GetComponent<Engine::Component::Transform>()->m_Scale.X = newScaleX;
        }
    }
    else if (!m_bIsDamage && m_bIsUpdateHpBar)
    {
        float currentScaleX = m_pHpBar->GetComponent<Engine::Component::UI>()->m_Scale.X;
        float newScaleX = lerp(lerpStart, lerpEnd, currentScaleX);
        if (newScaleX > lerpEnd)
        {
            m_bIsUpdateHpBar = false;
        }
        else if (newScaleX <= lerpEnd)
        {
            D2D1_SIZE_F size = m_pHpBar->GetComponent<Engine::Component::UI>()->GetBitmapSize();
            m_pHpBar->GetComponent<Engine::Component::Transform>()->SetScaleOrigin(-(size.width / 2), 0);
            m_pHpBar->GetComponent<Engine::Component::Transform>()->m_Scale.X = newScaleX;
        }
    }
}


void ShopSystem::Update()
{
    m_pTileManager->ShowAttackRange();

    UnitMove();
    UnitStat();
    // 리롤 버튼 클릭
    if (m_pTool->m_Input.IsKeyTap(KEY::LBTN))
    {
        if (m_ReRollButton->GetComponent<Engine::Component::Collider>()->GetMouseColl())
        {
            m_ReRollButton->GetComponent<Engine::Component::UI>()->SetScale(0.9, 0.9, 1);
            if (m_pPlayer->GetCurMana() >= m_ReRollCost)
            {
                ShopReset();
                UseMana(m_ReRollCost);
                MpBarState();
                HpBarState();
                std::cout << "현재마나 :" << m_pPlayer->GetCurMana() << std::endl;
            }
            else
                return;
            if (m_pPlayer->GetCurMana() < m_ReRollCost && m_pPlayer->GetCurMana() < m_ShopUpgradeCost)
            {
                m_ReRollButton->GetComponent<Engine::Component::UI>()->SetActive(false);
                m_ShopLevelUpButton->GetComponent<Engine::Component::UI>()->SetActive(false);
            }
        }
    }
    if (m_pTool->m_Input.IsKeyAway(KEY::LBTN))
    {
        if (m_ReRollButton->GetComponent<Engine::Component::Collider>()->GetMouseColl())
        {
            m_ReRollButton->GetComponent<Engine::Component::UI>()->SetScale(1, 1, 1);
        }
    }
    // 상점 업그레이드 버튼 클릭
    if (m_pTool->m_Input.IsKeyTap(KEY::LBTN))
    {
        if (m_ShopLevelUpButton->GetComponent<Engine::Component::Collider>()->GetMouseColl())
        {
            m_ShopLevelUpButton->GetComponent<Engine::Component::UI>()->SetScale(0.9, 0.9, 1);
            //m_ShopLevelUpButton->GetComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_levelup_4_S_image.png");
            if (m_ShopLevel == m_MaxShopLevel || m_pPlayer->GetCurMana() < m_ReRollCost)
            {
                return;
            }
            else
            {
                ShopUpgrade();
                SetRoundUnit();
                UseMana(m_ShopUpgradeCost);
                std::cout << "현재마나 :" << m_pPlayer->GetCurMana() << std::endl;
                std::cout << "상점 레벨 : " << m_ShopLevel << std::endl;
                MpBarState();
                HpBarState();
                UnitStoreLayout();
            }
            if (m_ShopLevel == m_MaxShopLevel)
            {
                m_ShopLevelUpButton->GetComponent<Engine::Component::UI>()->SetActive(false);
                return;
            }
            if (m_pPlayer->GetCurMana() < m_ReRollCost && m_pPlayer->GetCurMana() < m_ShopUpgradeCost)
            {
                m_ReRollButton->GetComponent<Engine::Component::UI>()->SetActive(false);
                m_ShopLevelUpButton->GetComponent<Engine::Component::UI>()->SetActive(false);
            }
        }
    }
    if (m_pTool->m_Input.IsKeyAway(KEY::LBTN))
    {
        if (m_ShopLevelUpButton->GetComponent<Engine::Component::Collider>()->GetMouseColl())
        {
            m_ShopLevelUpButton->GetComponent<Engine::Component::UI>()->SetScale(1, 1, 1);
        }
    }

    // 삭제

    for (int i = 6; i < m_pTileManager->GetGridY(); i++)
    {
        for (int j = 0; j < m_pTileManager->GetGridX(); j++)
        {
            if (m_pTileManager->GetTileInfo(j, i).GetTile()->GetComponent<Engine::Component::Collider>()->GetMouseColl())
            {
                if (m_pTileManager->GetTileInfo(j, i).GetTileOnUnitState() == TileOnUnitState::Take)
                {
                    if (m_pTool->m_Input.IsKeyTap(KEY::E))
                    {
                        DeleteUnit(j, i);
                    }
                }
            }
        }
    }
    
    // 소환
    for (const auto& b : m_UnitCardList)
    {
        if (b->GetComponent<Engine::Component::Collider>()->GetMouseColl())
        {
            if (m_pTool->m_Input.IsKeyTap(KEY::LBTN))
            {
                b->GetComponent<Engine::Component::UI>()->SetScale(0.9, 0.9, 1);
                /*if (m_pTool->m_Input.IsKeyHold(KEY::LBTN))
                {
                    m_bIsKeyAway = false;
                    SummonUnitDrag(m_TestUnitUI->GetUnitID());
                    return;
                }*/
            }
            if (m_pTool->m_Input.IsKeyAway(KEY::LBTN))
            {
                if (b->GetComponent<Engine::Component::Collider>()->GetMouseColl())
                {
                    if (m_pPlayer->GetCurMana() < b->GetUnitManaCost())
                    {
                        break;
                    }
                    b->GetComponent<Engine::Component::UI>()->SetScale(1, 1, 1);
                    SummonUnitClick(b->m_UnitID);
                    b->GetComponent<Engine::Component::UI>()->SetActive(false);
                    b->GetComponent<Engine::Component::Collider>()->SetActive(false);

                    break;
                }
            }
        }
    }
    
    if (m_pTool->m_Input.IsKeyTap(KEY::O))
    {
        m_pTileManager->SetBattleState(true);
    }
}

void ShopSystem::LateUpdate()
{
    if (m_pTool->m_Input.IsKeyTap(KEY::LBTN))
    {
        if (m_pGameStartButton->GetComponent<Engine::Component::Collider>()->GetMouseColl())
        {
            m_pGameStartButton->GetComponent<Engine::Component::UI>()->SetScale(0.9, 0.9, 1);
        }
    }
    if (m_pTool->m_Input.IsKeyAway(KEY::LBTN))
    {
        if (m_pGameStartButton->GetComponent<Engine::Component::Collider>()->GetMouseColl())
        {
            m_pGameStartButton->GetComponent<Engine::Component::UI>()->SetScale(1, 1, 1);
            m_pTileManager->ShopEnd();
            std::cout << "shopEnd \n";
        }
    }

    if (m_pTileManager->GetBattleState())
    {
        m_pTileManager->SetBattleState(false);
        // 아군이 모두 전멸해서 패배했을 때
        if (m_pTileManager->GetLeftOverTeamCost() == 0)
        {
            GainMana(m_pTileManager->GetLeftOverEnemyCount() * 20);
            //m_pPlayer->LoseHP(m_pTileManager->GetLeftOverEnemyCost());
            OnDamage(m_pTileManager->GetLeftOverEnemyCost());
            //m_pPlayer->RestoreHP(m_pTileManager->GetDeadEnemyCost());
            OnHeal(m_pTileManager->GetDeadEnemyCost());
        }
        // 적군이 모두 전멸해서 승리했을 때
        else if (m_pTileManager->GetLeftOverEnemyCost() == 0)
        {
            // 일정 마나 회복
            GainMana(100);
            OnHeal(m_pTileManager->GetDeadEnemyCost());
        }
    }
}
