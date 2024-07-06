#include "MouseDragSys.h"
#include "MouseDragging.h"

bool MouseDragSys::Initialize(const std::vector<Engine::Entity::Entity*>* _entities)
{
	m_Entities.clear();
	m_MouseDragContainer.clear();

	for (auto entity : *_entities)
	{
		SetEntity(entity);
	}
	return false;
}

void MouseDragSys::SetEntity(Engine::Entity::Entity* _entity)
{
	ULONGLONG MouseFlag = 0;
    MouseFlag = MouseDragging::ComponentFlag | Engine::Component::Collider::ComponentFlag;
	if ((_entity->GetComponentFlag() & MouseFlag) == MouseFlag)
	{
		m_Entities.push_back(_entity);
        m_MouseDragContainer.push_back(_entity->GetComponent<MouseDragging>());
	}
}

void MouseDragSys::Update()
{
    // 화면 스크롤
    for (auto entity : m_MouseDragContainer)
    {
        float mouseX = Engine::SingletonManager::GetInstance()->m_Input.GetMousePos()->x;
        float mouseY = Engine::SingletonManager::GetInstance()->m_Input.GetMousePos()->y;
        if (m_pTool->m_Input.IsKeyTap(KEY::LBTN))
        {
            if (entity->GetEntity()->GetComponent<Engine::Component::Collider>()->GetMouseColl())
            {
                IsDragging = true;

            }
        }
        if (Engine::SingletonManager::GetInstance()->m_Input.IsKeyAway(KEY::LBTN))
        {
            IsDragging = false;
            temp = nullptr;
        }

        if (Engine::SingletonManager::GetInstance()->m_Input.IsKeyHold(KEY::LBTN))
        {
            if (IsDragging)
            {
                if (entity->GetEntity()->GetComponent<Engine::Component::Collider>()->GetMouseColl())
                {
                    temp = entity->GetEntity();
                }
            }
        }
        if (temp != nullptr)
        {
            entity->GetEntity()->GetComponent<Engine::Component::Transform>()->SetPosition(m_pTool->m_Input.GetScreenMousePos().x, m_pTool->m_Input.GetScreenMousePos().y);
        }
    }
}
