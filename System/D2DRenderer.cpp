#include "pch.h"
#include "D2DRenderer.h"
#include <comdef.h>
#include <dxgi1_4.h>
#include "Macro.h"

#pragma comment(lib,"dxgi.lib")
// d2d lib
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"windowscodecs.lib")

ID2D1HwndRenderTarget* Engine::System::D2DRenderer::m_pStaticRenderTarget = nullptr;
IWICImagingFactory* Engine::System::D2DRenderer::m_pStaticImageFactory = nullptr;


bool Engine::System::D2DRenderer::Initialize(HINSTANCE hinst, HWND hWnd, int screenWidth, int screenHeight)
{
    m_hInstance = hinst;
    m_hWnd = hWnd;
    HRESULT hr;

    // COM���
    hr = CoInitialize(NULL);
    if (SUCCEEDED(hr))
    {
        // ����Ÿ���� ������ִ����丮��ü�� �����ϰ� �������̽� �����͸����´�.
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
    }

    if (SUCCEEDED(hr))
    {
        // ���ڿ� ����� ���� ���丮 ����
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(m_pDWriteFactory),
            reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
        );
    }

    if (SUCCEEDED(hr))
    {
        //  ��Ʈ�� ���丮 ����
        hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory));
    }
    m_pStaticImageFactory = m_pImageFactory;

    if (SUCCEEDED(hr))
    {
        // �̹� �����찡������� ���¿��� ������ ����� ���Ѵ�.
        RECT rc;
        GetClientRect(hWnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(
            static_cast<UINT>(rc.right - rc.left),
            static_cast<UINT>(rc.bottom - rc.top)
        );

        // ���丮�� �������ڵ�,����� �Ѱ� ����Ÿ���� �����.
        hr = m_pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hWnd, size),
            &m_pRenderTarget
        );
        m_pStaticRenderTarget = m_pRenderTarget;

    }


    if (SUCCEEDED(hr))
    {
        // (������) �귯�� ����
        hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush);
    }


    if (SUCCEEDED(hr))
    {
        // ���ڿ� ���� ����
        hr = m_pDWriteFactory->CreateTextFormat(
            L"Bernard MT Condensed",
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            50.0f,
            L"", //locale
            &m_pDWriteTextFormat
        );

        // Center the text horizontally and vertically.
        m_pDWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        m_pDWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

    if (FAILED(hr))
    {
        _com_error err(hr);
        ::MessageBox(hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
        return false;
    }
    return true;
}

void Engine::System::D2DRenderer::ChangeDisplay(int screenWidth, int screenHeight)
{
}

void Engine::System::D2DRenderer::RestoreDisplay()
{
}


///--------------------------------------------------------------------------------

void Engine::System::D2DRenderer::DrawBitmap(ID2D1Bitmap* _bitmap, const D2D1_RECT_F& _destinationRectangle, const D2D1_RECT_F& _sourceRectangle, D2D1_MATRIX_3X2_F _transform, FLOAT _opacity, D2D1_BITMAP_INTERPOLATION_MODE _interpolationMode)
{
    m_pRenderTarget->SetTransform(_transform);
    m_pRenderTarget->DrawBitmap(_bitmap, _destinationRectangle, _opacity, _interpolationMode, _sourceRectangle);
    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Engine::System::D2DRenderer::DrawFillRect(const D2D1_RECT_F& _rect, D2D1_COLOR_F _color, FLOAT _opacity, D2D1_MATRIX_3X2_F _transform)
{
    m_pBrush->SetColor(_color);
    m_pBrush->SetOpacity(_opacity);
    m_pRenderTarget->SetTransform(_transform);
    m_pRenderTarget->FillRectangle(_rect, m_pBrush);


    m_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
    /*m_pRenderTarget->DrawRectangle(_rect, m_pBrush);
    m_pRenderTarget->DrawRectangle({_rect.left+1,_rect.top - 1,_rect.right - 1,_rect.bottom + 1 }, m_pBrush);*/

    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Engine::System::D2DRenderer::DrawFillEllipse(const D2D1_ELLIPSE& _ellipse, D2D1_COLOR_F _color, FLOAT _opacity, D2D1_MATRIX_3X2_F _matrix)
{
    m_pBrush->SetColor(_color);
    m_pBrush->SetOpacity(_opacity);
    m_pRenderTarget->SetTransform(_matrix);


    m_pRenderTarget->FillEllipse(_ellipse, m_pBrush);
    m_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));

    D2D1_POINT_2F _point = _ellipse.point;
    _point.y -= _ellipse.radiusY;

    m_pRenderTarget->DrawLine(_ellipse.point, _point, m_pBrush);
    m_pRenderTarget->DrawEllipse(_ellipse, m_pBrush);
    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Engine::System::D2DRenderer::DrawPolygon(const D2D1_POINT_2F* _point, D2D1_MATRIX_3X2_F _matrix)
{
}

void Engine::System::D2DRenderer::BeginRender()
{
    m_pRenderTarget->BeginDraw();
    m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::FloralWhite));
    m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Engine::System::D2DRenderer::EndRender()
{
    m_pRenderTarget->EndDraw();
}

void Engine::System::D2DRenderer::Finalize()
{
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pBrush);
    SafeRelease(&m_pD2DFactory);
    SafeRelease(&m_pDWriteFactory);
    SafeRelease(&m_pImageFactory);
    SafeRelease(&m_pDWriteTextFormat);

    CoUninitialize();
}

HRESULT Engine::System::D2DRenderer::CreateD2DBitmapFromFile(const WCHAR* _filePath, ID2D1Bitmap** _bitmap)
{
    HRESULT hr;

    IWICBitmapDecoder* m_pBitmapDecoder = NULL;
    IWICBitmapFrameDecode* m_pFrame = NULL;
    IWICFormatConverter* m_pConverter = NULL;

    // ��Ʈ�� ���ڴ� ����
    hr = m_pImageFactory->CreateDecoderFromFilename(
        _filePath,
        NULL,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &m_pBitmapDecoder
    );

    if (SUCCEEDED(hr))
    {
        // ������ ����
        hr = m_pImageFactory->CreateFormatConverter(&m_pConverter);
    }

    if (SUCCEEDED(hr))
    {
        // �̹��� 0��° ������ ���
        hr = m_pBitmapDecoder->GetFrame(0, &m_pFrame);
    }


    if (SUCCEEDED(hr))
    {
        // �̹��� d2d�̹����� ������
        hr = m_pConverter->Initialize(
            m_pFrame,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            NULL,
            0.0f,
            WICBitmapPaletteTypeCustom
        );
    }

    if (SUCCEEDED(hr))
    {
        // �����õ� �̹��� ����
        hr = m_pRenderTarget->CreateBitmapFromWicBitmap(m_pConverter, NULL, _bitmap);
    }


    if (m_pBitmapDecoder != NULL)
    {
        m_pBitmapDecoder->Release();
    }

    if (m_pConverter != NULL)
    {
        m_pConverter->Release();
    }

    if (m_pFrame != NULL)
    {
        m_pFrame->Release();
    }

    return hr;
}
