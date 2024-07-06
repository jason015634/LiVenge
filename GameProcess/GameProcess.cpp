// GameProcess.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "GameProcess.h"
#include "SingletonManager.h"
#include <vector>



HWND Engine::GameProcess::m_hWnd;
Engine::GameProcess* Engine::GameProcess::m_pInstance = nullptr;

LRESULT CALLBACK DefaultWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return  Engine::GameProcess::m_pInstance->WndProc(hWnd, message, wParam, lParam);
	
}

Engine::GameProcess::GameProcess(HINSTANCE _hInstance) :
	m_hInstance(_hInstance),
	m_szWindowClass(L"DefaultWindowCalss"),
	m_szTitle(L"GameApp"),
	m_ClientSize({ 1024,768 })
{
	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());

	m_pInstance = this;

	m_wcex.hInstance = _hInstance;
	m_wcex.cbSize = sizeof(WNDCLASSEX);
	m_wcex.style = CS_HREDRAW | CS_VREDRAW;
	m_wcex.lpfnWndProc = DefaultWndProc;
	m_wcex.cbClsExtra = 0;
	m_wcex.cbWndExtra = 0;
	m_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	m_wcex.lpszClassName = m_szWindowClass;
}

Engine::GameProcess::~GameProcess()
{
	std::wstring str(__FUNCTIONW__);
	str += L"\n";
	OutputDebugString(str.c_str());
}

bool Engine::GameProcess::Initialize(UINT _width, UINT _height)
{


	m_ClientSize.width = _width;
	m_ClientSize.height = _height;

	// 등록
	RegisterClassExW(&m_wcex);

	// 원하는 크기가 조정되어 리턴
	RECT rcClient = { 0, 0, (LONG)m_ClientSize.width, (LONG)m_ClientSize.height };
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	//생성
	m_hWnd = CreateWindowW(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW,
		100, 100,	// 시작 위치
		rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
		nullptr, nullptr, m_hInstance, nullptr);

	if (!m_hWnd)
	{
		return false;
	}

	// 윈도우 보이기
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	m_GameManager.Initialize(m_hWnd, m_hInstance, m_ClientSize.width, m_ClientSize.height);
	SingletonManager::GetInstance()->Initialize(m_hWnd);
	return true;
}

void Engine::GameProcess::GameLoop()
{
	while (true)
	{
		if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (m_msg.message == WM_QUIT)
				break;

			//윈도우 메시지 처리 
			TranslateMessage(&m_msg); // 키입력관련 메시지 변환  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&m_msg);
		}
		else
		{
			// 게임 일시정지
			
			SingletonManager::GetInstance()->Update();
			
				m_GameManager.Physics();
				m_GameManager.Logic();
			
			m_GameManager.Render();


		}
	}

}

void Engine::GameProcess::Finalize()
{
}


LRESULT Engine::GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}