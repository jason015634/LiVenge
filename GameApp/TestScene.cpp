#include "TestScene.h"
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
// D2D header
#include <d2d1.h>
#include <d2d1_1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include <iostream>
// d2d lib
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"windowscodecs.lib")

#include "BattleField.h"

void TestScene::Initialize()
{
    m_pCamera = (Camera*)AddEntity(new Camera());
    m_pPlayer = (Player*)AddEntity(new Player());
    AddEntity(m_pPlayer);
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
    for (auto unitStatUI : m_pShopSystem->GetUnitStatList())
    {
        AddEntity((Engine::Entity::Entity*)unitStatUI);
    }
    m_pBattleSystem = new BattleSystem(m_pTileManager);
    m_pBattleSystem->Initialize(GetHierarchyEntity());
    BattleField::GetInstance().Init(m_pTileManager);

    m_pCurrSystem = m_pBattleSystem;
    m_pCurrSystem = m_pShopSystem;
 
    m_pTileManager->SpawnUnit(8, 8, 301);
   
    //shop.AddComponent<Engine::Component::UI>();
    //shop.AddComponent < Engine::Component::Rectangle>()->SetRect(960, 154);
    //shop.GetComponent<Engine::Component::Rectangle>()->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
    //shop.AddComponent<Engine::Component::Transform>();
    //shop.AddComponent<Engine::Component::Render>()->SetBitmapPath(L"..\\Resource/UI_Store_Image.png");
    //shop.GetComponent<Engine::Component::Render>()->SetLayer(1);
    //shop.AddComponent<Engine::Component::Render>();
    // prefeb
    m_BIsBattle = m_pTileManager->IsBattle();
}

void TestScene::Finalize()
{
}

void TestScene::Start()
{
    // 예시코드
    /*m_pShop->GetComponent < Engine::Component::Transform>()->m_Position.X = 675.0f;
    m_pShop->GetComponent < Engine::Component::Transform>()->m_Position.Y = 1590.0f;*/
    /*shop.GetComponent < Engine::Component::Transform>()->m_Position.X = -285.0f;
    shop.GetComponent < Engine::Component::Transform>()->m_Position.Y = 0.0f;*/
}

void TestScene::FixedUpdate()
{
    // 예시코드
    m_pCurrSystem->FixedUpdate();
    
}

Engine::Entity::Entity* temp;

void TestScene::Update()
{
    m_pMouseSystem->Update();
    auto e = GetHierarchyEntity();
    e;

    // 플레이어 이동
   /* if (Engine::SingletonManager::GetInstance()->m_Input.IsKeyHold(KEY::LEFT))
        m_pPlayer->GetComponent<Engine::Component::Transform>()->m_Position.X -= 0.5;
    if (Engine::SingletonManager::GetInstance()->m_Input.IsKeyHold(KEY::UP))
        m_pPlayer->GetComponent<Engine::Component::Transform>()->m_Position.Y -= 0.5;
    if (Engine::SingletonManager::GetInstance()->m_Input.IsKeyHold(KEY::RIGHT))
        m_pPlayer->GetComponent<Engine::Component::Transform>()->m_Position.X += 0.5;
    if (Engine::SingletonManager::GetInstance()->m_Input.IsKeyHold(KEY::DOWN))
        m_pPlayer->GetComponent<Engine::Component::Transform>()->m_Position.Y += 0.5;*/

    // 상점 연출
    //if (m_pCamera->GetComponent<Engine::Component::Transform>()->m_Position.Y == 824.f)
    //{
    //    if (m_pCamera->GetComponent<Engine::Component::Collider>()->ScreenScrollAABB(Engine::SingletonManager::GetInstance()->m_Input.GetMousePos()->x, Engine::SingletonManager::GetInstance()->m_Input.GetMousePos()->y) == 2)
    //    {
    //        shop.GetComponent<Engine::Component::Transform>()->m_Position.Y += 0.5f * m_pTool->m_Time.GetDeltaTime();
    //    }
    //}

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
        Engine::Scene::ChangeScene(L"TestScene2");
        m_pShopSystem->Initialize(GetHierarchyEntity());
    }
}

void TestScene::LateUpdate()
{
    // 임시로 여기서 렌더링
    //if()
    m_pCurrSystem->LateUpdate();
    for (auto& entity : m_pTileManager->GetCreateUnits())
    {
        CreateEntity(entity);
    }
    m_pTileManager->ClearCreateUnits();
  //  m_pTileManager->SetAlltile();

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

void TestScene::RoundFail()
{
    m_bIsRoundClear = false;
}

void TestScene::RoundClear()
{
    m_bIsRoundClear = true;
}