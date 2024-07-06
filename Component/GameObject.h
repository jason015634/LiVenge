#pragma once
#include "Component.h"
#include "framework.h"

namespace Engine
{
	namespace Component
	{
		class GameObject : public Component
		{
		public:
			GameObject() {};
			~GameObject() {};

			// 필수 작성부
		public:
			static const ULONGLONG ComponentType = (ULONGLONG)E_ComponentType::GameObject;
			static const ULONGLONG ComponentFlag = 1 << ComponentType;
		
			//-------------------------------

			void SetTag(std::wstring _tag) { m_Tag = _tag; }
			std::wstring GetTag() { return m_Tag; }
		private:
			std::wstring m_Tag;
		};
	}
}

