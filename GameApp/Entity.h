#pragma once
#include "../Entity/Entity.h"
#include "ComponentList.h"

class Entity : public Engine::Entity::Entity
{
public:
	Entity()
	{
	}
	virtual ~Entity() {}

public:
	int px, py;

};