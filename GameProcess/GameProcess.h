#pragma once

#include "framework.h"
#include "GameManager.h"

namespace Engine
{
#define MAX_LOADSTRING 100
	class GameProcess
	{
	public:
		GameProcess(HINSTANCE _hInstance);
		virtual ~GameProcess();

		static HWND m_hWnd;
		static GameProcess* m_pInstance;

	public:
		virtual bool Initialize(UINT _width, UINT _height);
		virtual void GameLoop();
		virtual void Finalize();

	private:

	public:
		const D2D_SIZE_U& GetClientSize() { return m_ClientSize; }
		BOOL GetClientRect(LPRECT _lpRect);
		int MessageBoxComError(HRESULT _hr);
		void CalculateFrameStats();

		virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	protected:
		GameManager m_GameManager;

	protected:
		// 윈도우용 변수
		HACCEL m_hAccelTable;
		MSG m_msg;
		HINSTANCE m_hInstance;                                // 현재 인스턴스입니다.
		WCHAR m_szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
		WCHAR m_szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
		WNDCLASSEXW m_wcex;

		int  m_nCmdShow;
		D2D_SIZE_U m_ClientSize;

	};
}