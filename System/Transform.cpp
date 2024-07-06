#include "pch.h"
#include "Transform.h"
#include "../Component/Transform.h"

bool Engine::System::Transform::Initialize(const std::vector<Entity::Entity*>* _entities)
{
	m_TransformContainer.clear();
	m_TransformContainer.emplace_back();
	m_Entities.clear();

	for (auto entity : *_entities)
	{
		SetEntity(entity);
	}

	return true;
}

void Engine::System::Transform::SetEntity(Entity::Entity* _entity)
{
	ULONGLONG flag = 0;
	flag += Component::Transform::ComponentFlag;
	ULONGLONG cameraFlag = Component::Camera::ComponentFlag;
	std::vector<Component::Transform*> container;

	if ((_entity->GetComponentFlag() & flag) == flag)
	{
		m_TransformContainer[0].push_back(_entity->GetComponent<Component::Transform>());
		if ((_entity->GetComponentFlag() & cameraFlag) == cameraFlag)
		{
			m_pCamera = _entity;
		}

	}
}

void Engine::System::Transform::FixedUpdate()
{
	if (m_pCamera == nullptr)
	{
		LOG_ERROR(L"Scene : Camera Not Include");
	}
	if (m_pCamera != nullptr)
	{
		m_pCamera->GetComponent<Component::Camera>()->SetInverseViewTransform(m_pCamera->GetComponent<Component::Transform>()->GetWorldTransform());
	}
	for (size_t i = 0; i < m_TransformContainer.size(); i++)
	{
		for (size_t j = 0; j < m_TransformContainer[i].size(); j++)
		{
			if (m_TransformContainer[i][j]->GetActive() == false)
			{
				return;
			}
			m_TransformContainer[i][j]->SetLocalTransform();
			if (m_TransformContainer[i][j]->GetEntity()->GetParent() == nullptr)
			{
				m_TransformContainer[i][j]->SetWorldTransform();
			}
			else
			{
				m_TransformContainer[i][j]->SetWorldTransform(
					m_TransformContainer[i][j]->GetEntity()->GetComponentInParent<Component::Transform>()->GetWorldTransform()
				);
			}
			m_TransformContainer[i][j]->SetScrrenTransform(m_pCamera->GetComponent<Component::Camera>()->GetViewTransform());

		}
	}
	


}
