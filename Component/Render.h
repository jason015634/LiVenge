#pragma once
#include "RenderingComponent.h"
#include <string>

namespace Engine
{
	namespace Component
	{
		class Render : public RenderingComponent
		{
		public:
			Render()
			{
				m_BitmapPath.clear();
			}
		public:
			ID2D1Bitmap* GetBitmap() override { return m_pBitmap; }
			void SetBitmap(ID2D1Bitmap* _bitmap) override { m_pBitmap = _bitmap; }
			const std::wstring* GetBitmapPath() { return &m_BitmapPath; }
			Render* SetBitmapPath(std::wstring _path) { m_BitmapPath = _path; return this; };
			
			D2D1_SIZE_F GetBitmapSize()
			{
				if (m_pBitmap == nullptr)
				{
					return { 0,0 };
				}
				return m_pBitmap->GetSize();
			};

		public:

			static const ULONGLONG ComponentType = (ULONGLONG)E_ComponentType::Render;

			static const ULONGLONG ComponentFlag = 1 << ComponentType;

			// --------------필수 구현부---------------------
		private:
			ID2D1Bitmap* m_pBitmap = nullptr;
			std::wstring m_BitmapPath;
			
		};
	}
}

