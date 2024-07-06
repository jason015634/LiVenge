#include "RoundBase.h"

#include "../Component/ComponentList.h"
#include "../GameProcess/SingletonManager.h"
#include "ShopSystem.h"
#include "BattleSystem.h"
#include "DataContainer.h"
#include "Player.h"
#include "Camera.h"
#include "ReRollButton.h"
#include "GameStartButton.h"
#include "ShopLevelUpButton.h"
#include "TestUnit.h"
#include "TileManager.h"
#include "MouseDragSys.h"
#include "UnitFactory.h"
#include "ReRollButton.h"
#include "ShopLevelUpButton.h"
#include "Shop.h"
#include "Shop2.h"
#include "Shop3.h"
#include "HpBar.h"
#include "ManaBar.h"
#include "SellButton.h"
#include "BattleField.h"
#include "UnitStatUI.h"

void RoundBase::Initialize()
{
    m_pCamera = (Camera*)AddEntity(new Camera());
    AddEntity(Player::GetInstance());
    //m_TestUnit = (TestUnit*)AddEntity(new TestUnit());

    m_pReRollButton = (ReRollButton*)AddEntity(new ReRollButton());
    m_pShopLevelUpButton = (ShopLevelUpButton*)AddEntity(new ShopLevelUpButton());
    m_pGameStartButton = (GameStartButton*)AddEntity(new GameStartButton());
    m_pSellButton = (SellButton*)AddEntity(new SellButton());
    m_pHpBar = (HpBar*)AddEntity(new HpBar());
    m_pManaBar = (ManaBar*)AddEntity(new ManaBar());
    m_pShop = (Shop*)AddEntity(new Shop());
    m_pShop2 = (Shop2*)AddEntity(new Shop2());
    m_pShop3 = (Shop3*)AddEntity(new Shop3());
    m_BgTop = AddEntity(new Engine::Entity::Entity());
    m_BgTop->AddComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/UI_Background.png");
    m_BgTop->GetComponent<Engine::Component::UI>()->SetLayer(0);
    m_BgTop->GetComponent<Engine::Component::UI>()->SetCameraAffect(true);
    m_BgTop->AddComponent<Engine::Component::Transform>()->SetPosition(675, 750, 0);
    m_pTileManager = new TileManager();
    m_pTileManager->SetRound(round-1);
    m_pTileManager->Initialize();
    m_pMouseSystem = new MouseDragSys();
    m_pMouseSystem->Initialize(GetHierarchyEntity());
    m_pShopSystem = new ShopSystem(m_pTileManager);
    m_pShopSystem->Initialize(GetHierarchyEntity());
    for (auto tile : *m_pShopSystem->GetTileManager()->GetTileObjects())
    {
        AddEntity(tile);
    }
    for (auto unit : *m_pShopSystem->GetTileManager()->GetUnits())
    {
        AddEntity(unit);
    }
    for (auto unitCard : m_pShopSystem->GetUnitCardList())
    {
        AddEntity((Engine::Entity::Entity*)unitCard);
    }
    for (auto unitStat : m_pShopSystem->GetUnitStatList())
    {
        AddEntity((Engine::Entity::Entity*)unitStat);
    }

    m_pBattleSystem = new BattleSystem(m_pTileManager);
    m_pBattleSystem->Initialize(GetHierarchyEntity());
    BattleField::GetInstance().Init(m_pTileManager);

    m_pCurrSystem = m_pBattleSystem;
    m_pCurrSystem = m_pShopSystem;

    m_pTileManager->SpawnUnit(8, 8, 301);

    m_BIsBattle = m_pTileManager->IsBattle();
}

void RoundBase::Finalize()
{
    /*SAFE_DELETE(m_pCamera);
    SAFE_DELETE(m_pReRollButton);
    SAFE_DELETE(m_pShopLevelUpButton);
    SAFE_DELETE(m_pGameStartButton);
    SAFE_DELETE(m_pSellButton);
    SAFE_DELETE(m_pHpBar);
    SAFE_DELETE(m_pManaBar);
    SAFE_DELETE(m_pShop);
    SAFE_DELETE(m_pShop2);
    SAFE_DELETE(m_pShop3);
    SAFE_DELETE(m_BgTop);*/


}

void RoundBase::Start()
{
}

void RoundBase::FixedUpdate()
{
    m_pCurrSystem->FixedUpdate();
}

void RoundBase::Update()
{
    m_pMouseSystem->Update();

    m_pCurrSystem->Update();

    // 게임 시작 버튼 클릭
    if (m_pTool->m_Input.IsKeyTap(KEY::LBTN))
    {
        if (m_pGameStartButton->GetComponent<Engine::Component::Collider>()->GetMouseColl())
        {
            m_bIsGameStart = true;
        }
    }

    // 다음 씬 넘어가기
    if (m_pTool->m_Input.IsKeyTap(KEY::P))
    {
        RoundClear();
    }
}

void RoundBase::LateUpdate()
{
    m_pCurrSystem->LateUpdate();
    for (auto& entity : m_pTileManager->GetCreateUnits())
    {
        CreateEntity(entity);
    }
    m_pTileManager->ClearCreateUnits();

    if (m_pTileManager->IsBattle() != m_BIsBattle)
    {
        m_BIsBattle = m_pTileManager->IsBattle();
        if (m_pTileManager->IsBattle() == true)
        {
            m_pCurrSystem = m_pBattleSystem;
        }
        else
        {
            m_pCurrSystem = m_pShopSystem;
        }
    }
}

void RoundBase::RoundFail()
{
    //m_bIsRoundClear = false;
    if (Player::GetInstance()->IsPlayerDead() == true)
    {
        //ChangeScene(L"TileScene");
        PostQuitMessage(0);
    }
}

void RoundBase::RoundClear()
{
    //m_bIsRoundClear = true;
    switch (round)
    {
    case 1:
        ChangeScene(L"Round2");
        break;
    case 2:
        ChangeScene(L"Round3");
        break;
    case 3:
        ChangeScene(L"Round4");
        break;
    case 4:
        ChangeScene(L"Round5");
        break;
    case 5:
        PostQuitMessage(0);
        break;
    default:
        break;
    }
}
