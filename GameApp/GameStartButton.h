#pragma once
#include "Button.h"
class GameStartButton : public Button
{
public:
	GameStartButton() {}
	~GameStartButton() {}

public:
	void Initialize() override;
};

