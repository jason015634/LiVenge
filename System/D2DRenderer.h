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
				// �� �ڿ����� ������� ������ Ÿ�̹��� Finalize()�� �Ű���.
				// ������� Finalize() ȣ�� ���Ŀ� ���� �Ҹ� �� �ʿ��� ó��
			}


		public:
			/// �ʱ�ȭ, �׸���, ������

			// �ʱ�ȭ ����
			bool Initialize(HINSTANCE _hinst, HWND _hWnd, int _screenWidth, int _screenHeight);
			void ChangeDisplay(int _screenWidth, int _screenHeight);
			void RestoreDisplay();
			///--------------------------------------------------------------------------------
			void DrawBitmap(ID2D1Bitmap* _bitmap, const D2D1_RECT_F& _destinationRectangle, const D2D1_RECT_F& _sourceRectangle, D2D1_MATRIX_3X2_F _transform = D2D1::Matrix3x2F(D2D1::Matrix3x2F::Identity()), FLOAT _opacity = 1.0f, D2D1_BITMAP_INTERPOLATION_MODE _interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
			void DrawFillRect(const D2D1_RECT_F& _rect, D2D1_COLOR_F _color, FLOAT _opacity = 1.0f, D2D1_MATRIX_3X2_F _transform = D2D1::Matrix3x2F(D2D1::Matrix3x2F::Identity()));
			void DrawFillEllipse(const D2D1_ELLIPSE& _ellipse, D2D1_COLOR_F _color, FLOAT _opacity = 1.0f, D2D1_MATRIX_3X2_F _matrix = D2D1::Matrix3x2F(D2D1::Matrix3x2F::Identity()));
			void DrawPolygon(const D2D1_POINT_2F* _point, D2D1_MATRIX_3X2_F _matrix = D2D1::Matrix3x2F(D2D1::Matrix3x2F::Identity()));

			// Render ����
			void BeginRender();

			// Render ��
			void EndRender();

			// ������ �����Ѵ�.
			void Finalize();
			///--------------------------------------------------------------------------------
		public:
			// ��Ʈ�� ����
			HRESULT CreateD2DBitmapFromFile(const WCHAR* _filePath, ID2D1Bitmap** _bitmap);

			//ID2D1HwndRenderTarget* GetRenderTarger() { return m_pRenderTarget; }

			//size_t GetUsedVRAM();

		private:
			// windows handle
			HINSTANCE m_hInstance;
			HWND m_hWnd;

			// ȭ������� ���� ����Ÿ��
			ID2D1HwndRenderTarget* m_pRenderTarget = nullptr;
			// ��Ȱ�� ������ �귯�� ��ü�� ������
			ID2D1SolidColorBrush* m_pBrush = nullptr;;

			//-------------------------------
			// �⺻ D2D����� ���� Factory�� �������̽� ������
			ID2D1Factory* m_pD2DFactory = nullptr;;
			//���ڿ� ����� ���� factory�� �������̽� ������
			IDWriteFactory* m_pDWriteFactory = nullptr;;
			// ��Ʈ�� D2D ����� ���� FACTORY�� �������̽� ������
			IWICImagingFactory* m_pImageFactory = nullptr;;
			//-----------------------------

			// ���ڿ� ����� ���� ��ü �������̽� ������
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


