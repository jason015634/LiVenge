#include "pch.h"
#include "UISystem.h"

bool Engine::System::UISystem::Initialize(const std::vector<Engine::Entity::Entity*>* _entities)
{
	m_Entities.clear();

	for (auto entity : *_entities)
	{
		SetEntity(entity);
	}
	return true;
}

void Engine::System::UISystem::SetEntity(Entity::Entity* _entity)
{
	ULONGLONG flag = 0;
	flag += Component::UI::ComponentFlag;
	if ((_entity->GetComponentFlag() & flag) == flag)
	{
		m_Entities.push_back(_entity);
		m_UIContainer.push_back(_entity->GetComponent<Component::UI>());
	}
}

void Engine::System::UISystem::Update()
{

}
