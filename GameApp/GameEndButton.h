#pragma once
#include "Button.h"
class GameEndButton : public Button
{
public:
	GameEndButton() {}
	~GameEndButton() {}

public:
	void Initialize() override;
};

