#pragma once
#include "Entity.h"
class Button : public Entity
{
public:
	Button() {}
	virtual ~Button() {}

public:
	virtual void Initialize();
};

