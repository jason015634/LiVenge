#include "TitleScene.h"
#include "../Component/ComponentList.h"
#include "../GameProcess/SingletonManager.h"
#include "Camera.h"
#include "EditButton.h"
#include "GameEndButton.h"
#include "Player.h"

void TitleScene::Initialize()
{
	m_pCamera = (Camera*)AddEntity(new Camera());
	m_pTitleBackground = AddEntity(new Engine::Entity::Entity());
	m_pTitleBackground->AddComponent<Engine::Component::UI>()->SetBitmapPath(L"..\\Resource/main_title_image.png");
	m_pTitleBackground->GetComponent<Engine::Component::UI>()->SetLayer(0);
	m_pTitleBackground->AddComponent<Engine::Component::Collider>();
	m_pTitleBackground->AddComponent<Engine::Component::Transform>()->SetPosition(960, 540, 1);
	
	m_pEditButton = (EditButton*)AddEntity(new EditButton());
	m_pGameEndButton = (GameEndButton*)AddEntity(new GameEndButton());
}

void TitleScene::Finalize()
{
}

void TitleScene::Start()
{
}

void TitleScene::FixedUpdate()
{
}

void TitleScene::Update()
{
	if (m_pTool->m_Input.IsKeyTap(KEY::LBTN))
	{
		if (m_pTitleBackground->GetComponent<Engine::Component::Collider>()->GetMouseColl() 
			&& !(m_pEditButton->GetComponent<Engine::Component::Collider>()->GetMouseColl())
			&& !(m_pGameEndButton->GetComponent<Engine::Component::Collider>()->GetMouseColl()))
		{
		}
		else if (m_pEditButton->GetComponent<Engine::Component::Collider>()->GetMouseColl())
		{
			// 테스트 용
			m_pEditButton->GetComponent<Engine::Component::UI>()->SetScale(0.9, 0.9, 1);
		}
		else if (m_pGameEndButton->GetComponent<Engine::Component::Collider>()->GetMouseColl())
		{
			m_pGameEndButton->GetComponent<Engine::Component::UI>()->SetScale(0.9, 0.9, 1);
		}
	}
	if (m_pTool->m_Input.IsKeyAway(KEY::LBTN))
	{
		if (m_pTitleBackground->GetComponent<Engine::Component::Collider>()->GetMouseColl()
			&& !(m_pEditButton->GetComponent<Engine::Component::Collider>()->GetMouseColl())
			&& !(m_pGameEndButton->GetComponent<Engine::Component::Collider>()->GetMouseColl()))
		{
			Player::GetInstance()->Initialize();
			Engine::Scene::ChangeScene(L"TestScene");
		}
		else if (m_pEditButton->GetComponent<Engine::Component::Collider>()->GetMouseColl())
		{
			// 테스트 용
			m_pEditButton->GetComponent<Engine::Component::UI>()->SetScale(1.0, 1.0, 1);
		}
		else if (m_pGameEndButton->GetComponent<Engine::Component::Collider>()->GetMouseColl())
		{
			m_pGameEndButton->GetComponent<Engine::Component::UI>()->SetScale(1.0, 1.0, 1);
		}
	}
}

void TitleScene::LateUpdate()
{
}
