#include "pch.h"
#include "InputManager.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,//LEFT,
	VK_RIGHT,//RIGHT,
	VK_UP,//UP,
	VK_DOWN,//DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',

	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	//
	VK_MENU,//ALT,
	VK_CONTROL,//CTRL,
	VK_LSHIFT,//LSHIFT,
	VK_SPACE,//SPACE,
	VK_RETURN,//ENTER,
	VK_ESCAPE,//ESC,
	//
	VK_LBUTTON,//좌클릭,
	VK_RBUTTON,
	//
	//LAST,
};

Engine::InputManager::InputManager()
{
}
Engine::InputManager::~InputManager()
{
}

void Engine::InputManager::SetMousePos()
{
	if (m_hWnd != ::GetActiveWindow())
	{
		return;
	}
	RECT rc;
	POINT p1;
	GetClientRect(m_hWnd, &rc);

	p1.x = rc.left;
	p1.y = rc.top;
	mouse.x = rc.right;
	mouse.y = rc.bottom;
	ClientToScreen(m_hWnd, &p1);
	ClientToScreen(m_hWnd, &mouse);
	rc.left = p1.x;
	rc.top = p1.y;
	rc.right = mouse.x;
	rc.bottom = mouse.y;

	//ClipCursor(&rc);

	GetCursorPos(&mouse);
	ScreenToClient(m_hWnd, &mouse);

	
}

bool Engine::InputManager::Initialize(HWND _hWnd)
{
	m_hWnd = _hWnd;
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
	return true;
}

void Engine::InputManager::Finalize()
{
}

void Engine::InputManager::Update()
{
	//윈도우 포커싱 알아내기
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	if (m_hWnd != ::GetActiveWindow())
	{
		return;
	}
	SetMousePos();
	if (nullptr != m_hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)//키가 눌려있다
			{
				if (m_vecKey[i].bPrevPush)//이전에도 눌려있었다
				{
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else//이전에 눌려있지 않았다
				{
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}
			else//키가 안눌려있다
			{
				if (m_vecKey[i].bPrevPush)//이전에 눌려있었다.
				{
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else//이전에 안눌려있었다.
				{
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}
	}

	else// 해당 윈도우가 포커싱 되어있지 않을 때 오브젝트가 움직이지 않게 해줌
	{
		for (size_t i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}


// KEY_STATE CKeyMgr::ClearKey()
// {
// 	return KEY_STATE::NONE;
// }