#pragma once
#include "Entity.h"
class UnitStatUI : public Entity
{
public:
	UnitStatUI();
	~UnitStatUI() {}

public:
	void Initialize() override;
	void SetUnitStatUI(int _ID);
	int m_UnitID;
};

