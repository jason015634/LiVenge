// GameApp.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "GameApp.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "TestScene2.h"
#include "TestScene3.h"
#include "RoundBase.h"
#include "System.h"
#include "DataManager.h"

#include "../System/RenderingSystem.h"

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#define MAX_LOADSTRING 100


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    GameApp App(hInstance);

    if (App.Initialize(1920, 1080) == false)
    {
        return 0;
    }
    App.GameLoop();
    App.Finalize();
    return 0;
  
}

GameApp::GameApp(HINSTANCE _hInstance) :
    Engine::GameProcess::GameProcess(_hInstance)
{
    std::wstring str(__FUNCTIONW__);
    str += L"\n";
    OutputDebugString(str.c_str());

    // 윈도우 클래스 준비하는 작업을 다른 함수로 만들고 싶지 않아 생성자에서 한다.
    // 실행파일에 합쳐진 데이터 영역에서 DemoApp에 관한 아이콘이나 문자를 가져와 윈도우 클래스 정보를 준비한다.

    LoadStringW(m_hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
    LoadStringW(m_hInstance, IDC_GAMEAPP, m_szWindowClass, MAX_LOADSTRING);
    m_wcex.hInstance = m_hInstance;
    m_wcex.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_GAMEAPP));
    //m_wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEMOAPP);                  //게임이므로 메뉴는 없앤다
    m_wcex.hIconSm = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_SMALL));
    m_hAccelTable = LoadAccelerators(m_hInstance, MAKEINTRESOURCE(IDC_GAMEAPP));
}

GameApp::~GameApp()
{
    std::wstring str(__FUNCTIONW__);
    str += L"\n";
    OutputDebugString(str.c_str());
}

bool GameApp::Initialize(UINT _Width, UINT _Height)
{
    if (__super::Initialize(_Width, _Height) == false)
    {
        MessageBox(m_hWnd, L"WindowInitialize Failed!", L"Error", MB_OK);
        return false;
    }
    DataManager::GetInstance().LoadData();


    //m_GameManager.GetRenderSystem()->CreateSharingAnimationAsset(L"fsa",nullptr);
    //L"..\\Resource/UI_card_image.png"
    m_GameManager.GetRenderSystem()->GetSharingBitmap(L"..\\Resource/UI_card_image.png",&DataManager::GetInstance().m_Card[101]);
    m_GameManager.GetRenderSystem()->GetSharingBitmap(L"..\\Resource/UI_card_image5.png", &DataManager::GetInstance().m_Card[102]);
    m_GameManager.GetRenderSystem()->GetSharingBitmap(L"..\\Resource/UI_card_image4.png", &DataManager::GetInstance().m_Card[103]);
    m_GameManager.GetRenderSystem()->GetSharingBitmap(L"..\\Resource/UI_card_image2.png", &DataManager::GetInstance().m_Card[104]);
    m_GameManager.GetRenderSystem()->GetSharingBitmap(L"..\\Resource/UI_card_image3.png", &DataManager::GetInstance().m_Card[105]);

    m_GameManager.GetRenderSystem()->GetSharingBitmap(L"..\\Resource/UI_store_level_1_image.png", &DataManager::GetInstance().m_Shop[1]);
    m_GameManager.GetRenderSystem()->GetSharingBitmap(L"..\\Resource/UI_store_level_2_image.png", &DataManager::GetInstance().m_Shop[2]);
    m_GameManager.GetRenderSystem()->GetSharingBitmap(L"..\\Resource/UI_store_level_3_image.png", &DataManager::GetInstance().m_Shop[3]);

    m_GameManager.RegisterScene(L"TitleScene", new TitleScene);
    m_GameManager.RegisterScene(L"TestScene", new TestScene);
    m_GameManager.RegisterScene(L"TestScene2", new TestScene2);
    m_GameManager.RegisterScene(L"TestScene3", new TestScene3);
    m_GameManager.RegisterScene(L"Round1", new RoundBase(1));
    m_GameManager.RegisterScene(L"Round2", new RoundBase(2));
    m_GameManager.RegisterScene(L"Round3", new RoundBase(3));
    m_GameManager.RegisterScene(L"Round4", new RoundBase(4));
    m_GameManager.RegisterScene(L"Round5", new RoundBase(5));





    return m_GameManager.GameStart(L"Round1");
}
