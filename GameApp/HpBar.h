#pragma once
#include "Entity.h"
class HpBar : public Entity
{
public:
	HpBar() {}
	~HpBar() {}

public:
	void Initialize() override;
};

