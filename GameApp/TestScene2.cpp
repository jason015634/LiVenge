#include "TestScene2.h"

#include "UnitFactory.h"
#include "DataManager.h"
#include "TileManager.h"

#include "ShopSystem.h"
#include "BattleSystem.h"

#include "TestUnit.h"
#include "Camera.h"
#include "Player.h"


void TestScene2::Initialize()
{
	//Splayer = AddEntity(new TestUnit);
	m_pPlayer = new Player();
	AddEntity(m_pPlayer);

	AddEntity(new Camera());
	//m_pPlayer = (Player*)AddEntity(new Player());

	m_pTileManager = new TileManager();
	m_pTileManager->Initialize();
	
	for (auto tile : *m_pTileManager->GetTileObjects())
	{
		AddEntity(tile);
	}
	for (auto unit : *m_pTileManager->GetUnits())
	{
		AddEntity(unit);
	}

	m_pShopSystem = new ShopSystem(m_pTileManager);
	m_pShopSystem->Initialize(GetHierarchyEntity());
	m_pBattleSystem = new BattleSystem(m_pTileManager);
	m_pBattleSystem->Initialize(GetHierarchyEntity());

	m_pCurrSystem = m_pBattleSystem;
}

void TestScene2::Finalize()
{
	delete[] m_Tile;
	SAFE_DELETE(player);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pTileManager);

	SAFE_DELETE(m_pShopSystem);
	SAFE_DELETE(m_pBattleSystem);

}

void TestScene2::Start()
{
}

void TestScene2::FixedUpdate()
{
	m_pCurrSystem->FixedUpdate();
	/*if(m_pTool->m_Input.IsKeyHold(KEY::T))
	player->GetComponent<Engine::Component::Transform>()->m_Scale.Z += 0.001;*/
}

void TestScene2::Update()
{
	m_pCurrSystem->Update();
	if (m_pTool->m_Input.IsKeyTap(KEY::P))
	{
		Engine::Scene::ChangeScene(L"TestScene3");
		m_pShopSystem->Initialize(GetHierarchyEntity());
	}
}

void TestScene2::LateUpdate()
{
	m_pCurrSystem->LateUpdate();
}








// 업데이트 주석
//UnitFactory uf;
//for (size_t i = 0; i < 10; i++)
//{
//	for (size_t j = 0; j < 10; j++)
//	{
//		float a = 1;
//		int tile = (10 * i) + j;
//		if ((*m_pTileManager->GetTileObjects())[tile]->GetComponent<Engine::Component::Collider>()->GetMouseColl())
//		{
//			a = 0.5;
//			(*m_pTileManager->GetTileObjects())[tile]->GetComponent<Engine::Component::Rectangle>()->SetAlpha(a);
//			if (m_pTool->m_Input.IsKeyTap(KEY::LBTN))
//			{
//				CreateEntity((Engine::Entity::Entity*)uf.CreateEntity(201));
//				GetCreatedEntities()->back()->GetComponent<Engine::Component::Transform>()->SetPosition(j * 150, i * 150);
//				->GetComponent<Engine::Component::Transform>()->SetPosition(j*150,i*150);
//			}
//		}
//		else
//		{
//			(*m_pTileManager->GetTileObjects())[tile]->GetComponent<Engine::Component::Rectangle>()->SetAlpha(a);
//		}
//	}
//
//}