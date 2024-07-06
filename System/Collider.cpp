#include "pch.h"
#include "Collider.h"
#include "D2DRenderer.h"
#include "../Component/ComponentList.h"
bool Engine::System::Collider::Initialize(const std::vector<Entity::Entity*>* _entities)
{
	m_Entities.clear();
	m_CameraContainer.clear();
	m_BitmapContainer.clear();
	for (auto entity : *_entities)
	{
		SetEntity(entity);
	}

	return true;
}

void Engine::System::Collider::SetEntity(Entity::Entity* _entity)
{
	ULONGLONG flag = 0;
	flag += Component::Collider::ComponentFlag | Component::Transform::ComponentFlag ;
	ULONGLONG BitmapFlag = 0;
	BitmapFlag += Component::Collider::ComponentFlag | Component::Transform::ComponentFlag | Component::UI::ComponentFlag;
	ULONGLONG CameraFlag = 0;
	CameraFlag += Component::Camera::ComponentFlag | Component::Transform::ComponentFlag | Component::Collider::ComponentFlag;
	
	if ((_entity->GetComponentFlag() & CameraFlag) == CameraFlag)
	{
		m_CameraContainer.push_back({ _entity->GetComponent<Component::Camera>() ,_entity->GetComponent<Component::Collider>() });
		return;
	}
	if ((_entity->GetComponentFlag() & BitmapFlag) == BitmapFlag)
	{
		m_BitmapContainer.push_back({ _entity->GetComponent<Component::UI>(), _entity->GetComponent<Component::Collider>() });
	}
	if ((_entity->GetComponentFlag() & flag) == flag)
	{
		m_Entities.push_back(_entity);
		m_Container.push_back({ _entity->GetComponent<Component::Transform>() ,_entity->GetComponent<Component::Collider>() });
	}
	
}

void Engine::System::Collider::SetBitmapCollider()
{
	for (auto entity : m_BitmapContainer)
	{
		if (entity.second->GetActive() == false || entity.second->GetEntity()->GetActive() == false)
		{
			entity.second->SetMouseAABB(false);
			continue;
		}
		else if (entity.first->GetCameraAffect())
		{
			entity.second->SetColliderInfo(entity.first->GetBitmapSize().width / 2.f, entity.first->GetBitmapSize().height / 2.f);
			entity.second->SetColliderRect(entity.first->GetEntity()->GetComponent<Engine::Component::Transform>()->GetScrrenTransform());
			entity.second->MouseAABB(m_pMousePosition->x, m_pMousePosition->y);
		}
		else if (entity.first->GetCameraAffect() == false)
		{
			entity.second->SetColliderInfo(entity.first->GetBitmapSize().width / 2.f, entity.first->GetBitmapSize().height / 2.f);
			entity.second->SetColliderRect(entity.first->GetEntity()->GetComponent<Engine::Component::Transform>()->GetWorldTransform());
			entity.second->MouseAABB(m_pMousePosition->x, m_pMousePosition->y);
		}
	}
}

bool Engine::System::Collider::MouseAABB()
{
	for (auto entity : m_Container)
	{
		if (entity.second->GetActive() == false || entity.second->GetEntity()->GetActive() == false)
		{
			entity.second->SetMouseAABB(false);
			continue;
			//return false;
		}
		else
		{
			entity.second->SetColliderRect(entity.first->GetScrrenTransform());
			entity.second->MouseAABB(m_pMousePosition->x, m_pMousePosition->y);
		}
	}
	return true;
}

bool Engine::System::Collider::ScreenAABB()
{
	for (auto entity : m_CameraContainer)
	{
		entity.second->SetColliderRect(D2D1::Matrix3x2F::Identity());
		entity.second->ScreenScrollAABB(SingletonManager::GetInstance()->m_Input.GetMousePos()->x, SingletonManager::GetInstance()->m_Input.GetMousePos()->y);
	}

	return true;
}

void Engine::System::Collider::Update()
{
	MouseAABB();
	SetBitmapCollider();
}


