#pragma once
#include "System.h"
#include "Entity.h"
#include "framework.h"
#include "MouseDragging.h"
class MouseDragSys : public System
{
public:
	MouseDragSys() {}
	~MouseDragSys() {}
public:
	bool Initialize(const std::vector<Engine::Entity::Entity*>* _entities);
	void Finalize() {}
	void SetEntity(Engine::Entity::Entity* _entity);

public:
	void Update() override;

private:
	std::vector<MouseDragging*> m_MouseDragContainer;

private:
	bool IsDragging = false;
	POINT prevMousePos;
	Engine::Entity::Entity* temp;
};

