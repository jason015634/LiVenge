#pragma once
// D2D header
#include <d2d1.h>
#include <d2d1_1helper.h>
#include <dwrite.h>
#include <wincodec.h>

namespace Engine
{
	namespace System
	{
		class D2DRenderer
		{
		public:
			D2DRenderer() :
				m_hInstance(NULL),
				m_hWnd(NULL)
			{

			}
			~D2DRenderer()
			{
				// 각 자원들의 명시적인 릴리즈 타이밍을 Finalize()로 옮겼음.
				// 명시적인 Finalize() 호출 이후에 엔진 소멸 시 필요한 처리
			}


		public:
			/// 초기화, 그리기, 끝내기

			// 초기화 관련
			bool Initialize(HINSTANCE _hinst, HWND _hWnd, int _screenWidth, int _screenHeight);
			void ChangeDisplay(int _screenWidth, int _screenHeight);
			void RestoreDisplay();
			///--------------------------------------------------------------------------------
			void DrawBitmap(ID2D1Bitmap* _bitmap, const D2D1_RECT_F& _destinationRectangle, const D2D1_RECT_F& _sourceRectangle, D2D1_MATRIX_3X2_F _transform = D2D1::Matrix3x2F(D2D1::Matrix3x2F::Identity()), FLOAT _opacity = 1.0f, D2D1_BITMAP_INTERPOLATION_MODE _interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
			void DrawFillRect(const D2D1_RECT_F& _rect, D2D1_COLOR_F _color, FLOAT _opacity = 1.0f, D2D1_MATRIX_3X2_F _transform = D2D1::Matrix3x2F(D2D1::Matrix3x2F::Identity()));
			void DrawFillEllipse(const D2D1_ELLIPSE& _ellipse, D2D1_COLOR_F _color, FLOAT _opacity = 1.0f, D2D1_MATRIX_3X2_F _matrix = D2D1::Matrix3x2F(D2D1::Matrix3x2F::Identity()));
			void DrawPolygon(const D2D1_POINT_2F* _point, D2D1_MATRIX_3X2_F _matrix = D2D1::Matrix3x2F(D2D1::Matrix3x2F::Identity()));

			// Render 시작
			void BeginRender();

			// Render 끝
			void EndRender();

			// 엔진을 종료한다.
			void Finalize();
			///--------------------------------------------------------------------------------
		public:
			// 비트맵 생성
			HRESULT CreateD2DBitmapFromFile(const WCHAR* _filePath, ID2D1Bitmap** _bitmap);

			//ID2D1HwndRenderTarget* GetRenderTarger() { return m_pRenderTarget; }

			//size_t GetUsedVRAM();

		private:
			// windows handle
			HINSTANCE m_hInstance;
			HWND m_hWnd;

			// 화면출력을 위한 렌더타겟
			ID2D1HwndRenderTarget* m_pRenderTarget = nullptr;
			// 재활용 가능한 브러시 객체의 포인터
			ID2D1SolidColorBrush* m_pBrush = nullptr;;

			//-------------------------------
			// 기본 D2D사용을 위한 Factory의 인터페이스 포인터
			ID2D1Factory* m_pD2DFactory = nullptr;;
			//문자열 사용을 위한 factory의 인터페이스 포인터
			IDWriteFactory* m_pDWriteFactory = nullptr;;
			// 비트맵 D2D 사용을 위한 FACTORY의 인터페이스 포인터
			IWICImagingFactory* m_pImageFactory = nullptr;;
			//-----------------------------

			// 문자열 출력을 위한 객체 인터페이스 포인터
			IDWriteTextFormat* m_pDWriteTextFormat = nullptr;;
			//----------------------------------------------

		public:
			
			static ID2D1HwndRenderTarget* m_pStaticRenderTarget;
			static IWICImagingFactory* m_pStaticImageFactory;
			static ID2D1HwndRenderTarget* GetRenderTarget() { return m_pStaticRenderTarget; }
			static IWICImagingFactory* GetImageFactory() { return m_pStaticImageFactory; }
		};
	}
}


