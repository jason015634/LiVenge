#pragma once
#include "framework.h"
#include "IManager.h"
// KeyManager�� �ʿ��� ����
// 1. ������ ����ȭ
// ���� ������ ������ ���� Ű�� ����, ������ �̺�Ʈ�� ��������.

// 2. Ű �Է� �̺�Ʈ ó��
// tap. hold, away ex) ����

enum class KEY_STATE
{
	NONE, // ������ �ʰ�, �������� ������ ���� ����
	TAP, // �� ���� ����
	HOLD, // ������ �ִ�
	AWAY, // �� �� ����
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
	KEY_STATE eState; // Ű�� ���°�
	bool bPrevPush; // ���� �����ӿ��� ���ȴ��� ����
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
