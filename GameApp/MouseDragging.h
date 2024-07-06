#pragma once
#include "CustomComponent.h"
class MouseDragging : public CustomComponent
{
public:
	MouseDragging() {}
	~MouseDragging() {}

public:
	static const ULONGLONG ComponentType = (ULONGLONG)E_CustomComponent::MouseDragging;

	static const ULONGLONG ComponentFlag = 1 << ComponentType;
};

