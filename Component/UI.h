#pragma once
#include "RenderingComponent.h"

namespace Engine
{
	namespace Component
	{
		class UI : public RenderingComponent
		{
		public:
			ID2D1Bitmap* GetBitmap() override { return m_pBitmap; }
			void SetBitmap(ID2D1Bitmap* _bitmap) override { m_pBitmap = _bitmap; }
			const std::wstring* GetBitmapPath() { return &m_BitmapPath; }
			UI* SetBitmapPath(std::wstring _path) { m_BitmapPath = _path; return this; };

			UI* ChangeBitmapPath(std::wstring _OldPath, std::wstring _NewPath)
			{
				if (m_BitmapPath == _OldPath)
				{
					m_BitmapPath = L"";
					m_BitmapPath = _NewPath;
					return this;
				}
			}

			void SetCameraAffect(bool _cameraAffect) { m_bIsCameraAffect = _cameraAffect; }
			bool GetCameraAffect() { return m_bIsCameraAffect; }
			
			D2D1_SIZE_F GetBitmapSize();

			void SetScale(float _x, float _y, float _z)
			{
				m_Scale.X = _x;
				m_Scale.Y = _y;
				m_Scale.Z = _z;
			}

			Vector3 GetScale()
			{
				return m_Scale;
			}

		public:

			static const ULONGLONG ComponentType = (ULONGLONG)E_ComponentType::UI;

			static const ULONGLONG ComponentFlag = 1 << ComponentType;

			// --------------필수 구현부---------------------
			Vector3 m_Scale = { 1,1,1 };
		private:
			ID2D1Bitmap* m_pBitmap = nullptr;
			std::wstring m_BitmapPath;
			bool m_bIsCameraAffect = false;

		};
	}
}


