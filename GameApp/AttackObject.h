#pragma once
#include "Entity.h"

class AttackObject : public Entity
{
public:
	AttackObject();
	virtual ~AttackObject() {};
public:
	void Initialize() override;
	int m_ObjectNum;
	double m_Damage;

};

