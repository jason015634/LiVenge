#include "pch.h"
#include "UI.h"

#pragma 



D2D1_SIZE_F Engine::Component::UI::GetBitmapSize()
{
	if (m_pBitmap == nullptr)
	{
		return { 0,0 };
	}
	return m_pBitmap->GetSize();
}
