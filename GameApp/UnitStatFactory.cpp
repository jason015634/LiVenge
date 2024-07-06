#include "UnitStatFactory.h"
#include "Entity.h"
#include "UnitStatUI.h"
UnitStatUI* UnitStatFactory::CreateUnitCard(int _unitID)
{
    UnitStatUI* entity = new UnitStatUI();
    entity->m_UnitID = _unitID;
    entity->SetUnitStatUI(_unitID);
    return entity;
}
