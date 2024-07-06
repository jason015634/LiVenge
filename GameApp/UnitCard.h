#pragma once
#include "Entity.h"
#include "framework.h"
class UnitCard : public Entity
{
public:
	UnitCard();
	~UnitCard() {}

public:
	void Initialize() override;
	void SetUnitID(int _unitID);
	int GetUnitManaCost() { return m_UnitManaCost; }

	int m_UnitID;
	int m_UnitManaCost;
	bool m_bIsActive = true;
};

