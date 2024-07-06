#pragma once

#include "resource.h"
#include "../GameProcess/GameProcess.h"

class GameApp : public Engine::GameProcess
{
public:
	GameApp(HINSTANCE _hInstance);
	virtual ~GameApp();
	bool Initialize(UINT _Width, UINT _Height) override;
};
