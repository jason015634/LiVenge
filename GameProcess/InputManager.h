#pragma once
#include "framework.h"
#include "IManager.h"
// KeyManager가 필요한 이유
// 1. 프레임 동기화
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가져간다.

// 2. 키 입력 이벤트 처리
// tap. hold, away ex) 점프

enum class KEY_STATE
{
	NONE, // 눌리지 않고, 이전에도 눌리지 않은 상태
	TAP, // 막 누른 시점
	HOLD, // 누르고 있는
	AWAY, // 막 뗀 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,

	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST,
};

struct tKeyInfo
{
	KEY_STATE eState; // 키의 상태값
	bool bPrevPush; // 이전 프레임에서 눌렸는지 여부
};

namespace Engine
{
	class InputManager
	{
		friend class SingletonManager;
	private:
		std::vector<tKeyInfo> m_vecKey;
		POINT mouse;
		POINT m_MouseOffset;
	private:
		InputManager();
		~InputManager();

		// 	KEY_STATE ClearKey();
	private:
		bool Initialize(HWND _hWnd);
		void Finalize();

	private:
		void SetMousePos();
		KEY_STATE GetKeyState(KEY _eKey)
		{
			return m_vecKey[(int)_eKey].eState;
		}
	private:
		HWND m_hWnd;

	public:
		void Update();
		POINT* GetMousePos()
		{
			SetMousePos();
			return &mouse;
		}
		POINT GetScreenMousePos()
		{
			SetMousePos();
			return { mouse.x + m_MouseOffset.x,mouse.y + m_MouseOffset.y };
		}

		void SetMouseOffset(LONG _x, LONG _y)
		{
			m_MouseOffset.x = _x;
			m_MouseOffset.y = _y;
		}

		bool IsKeyHold(KEY _eKey)
		{
			return GetKeyState(_eKey) == KEY_STATE::HOLD;
		}

		bool IsKeyTap(KEY _eKey)
		{
			return GetKeyState(_eKey) == KEY_STATE::TAP;
		}

		bool IsKeyAway(KEY _eKey)
		{
			return GetKeyState(_eKey) == KEY_STATE::AWAY;
		}

		void SetKeyUnable(KEY _eKey)
		{
			m_vecKey[(int)_eKey].eState = KEY_STATE::NONE;
		}

		void SetAllKeyUnable()
		{
			for (UINT i = 0; i < (UINT)KEY::LAST; i++)
			{
				m_vecKey[(int)i].eState = KEY_STATE::NONE;
			}
		}
		
	};
}
