#pragma once
#include "framework.h"
#include <type_traits>

namespace Engine
{
	namespace Component
	{
		class Component;
		class Transform;
		class ScriptComponent;
	}

	namespace Entity
	{
		class Entity
		{
		public:
			Entity() {}
			~Entity()
			{
				Finalize();
			}

		public:
			// 부모 엔티티 가져오기
			Entity* GetParent() const
			{
				return m_pParent;
			}
			// 부모 엔티티 설정
			void SetParent(Entity* _parent)
			{
				m_pParent = _parent;
				m_pParent->AddChild(this);
			}
			// 자식 엔티티 추가
			void AddChild(Entity* _child)
			{
				m_pChilds.push_back(_child);
				if (m_pChilds.back()->GetParent() == nullptr)
				{
					m_pChilds.back()->SetParent(this);
				}
				delete _child;
				_child = nullptr;
			}

			Entity* MakeChild()
			{
				m_pChilds.emplace_back();
				m_pChilds.back()->SetParent(this);
				return m_pChilds.back();
			}

			const ULONGLONG& GetComponentFlag()
			{
				return m_ComponentFlag;
			}

			const std::vector<Entity*>& GetChilds()
			{
				return m_pChilds;
			}

			void SetDontDestroy()
			{
				m_bDontDestroy = true;
			}

			void SetActive(bool _active)
			{
				m_bActive = _active;
			}

			bool GetActive()
			{
				return m_bActive;
			}

			const std::vector<Component::ScriptComponent*>* GetScripteComponent()
			{
				return &m_Scripts;
			}
		public:
			virtual void Initialize() {};
			virtual void Finalize() final
			{
				for (int i = 0; i < 64; i++)
				{
					if (m_Components[i] != nullptr)
					{
						SAFE_DELETE(m_Components[i]);
					}
				}
				for (auto script : m_Scripts)
				{
					if (script != nullptr)
					{
						SAFE_DELETE(script);
					}
				}
			};

		public:
			// 엔티티 이름
			std::wstring m_EntityName;

		protected:
			ULONGLONG m_ComponentFlag = 0;

			// 부모 엔티티 - 없을수도 있습니다.
			Entity* m_pParent = nullptr;
			std::vector<Entity*> m_pChilds;

			Component::Component* m_Components[64] = { nullptr, };
			std::vector<Component::ScriptComponent*> m_Scripts;

			/// <summary>
			/// 컴포넌트 관련 (가벼운 함수라곤 할 수 없으니 남발 금지)
			/// 해당 컴포넌트에서 자주 쓰이는 다른 컴포넌트라면 포인터로 미리 들고있는게 바람직함
			/// </summary>
		public:

			Component::Component* GetComponent()
			{
				return *m_Components;
			}

			template <typename T>
			T* AddComponent();

			template <typename T>
			void RemoveComponent();

			template <typename T>
			T* GetComponent();

			template <typename T>
			T* GetComponentInParent();
		private:
			bool m_bDontDestroy = false;
			bool m_bActive = true;

			public:
				bool m_bIsSelected = false;

		};
	}

}

template<typename T>
inline T* Engine::Entity::Entity::AddComponent()
{
	// 널 포인터 또는 컴포넌트 클래스를 상속받지 않았는지 확인함
	if (std::is_base_of<Component::Component, T>::value)
	{
		// AddComponent 안에서 생성해주는 이유
		// 1. 씬 단위의 코드의 간소화
		// 2. 생성자를 직접 할당하게 되면 연결을 못했을 때 메모리 누수가 발생함
		// 3. SceneComponent 가 아닐 경우(참조를 하지 않기떄문에), 에러가 발생하지 않아 발견하기 쉽지 않음

		// 생성
		// 게임 오브젝트에 존재하는 컴포넌트인지 확인함
		if (m_Components[T::ComponentType] != nullptr)
		{
			m_ComponentFlag = m_ComponentFlag | T::ComponentFlag;
			m_Components[T::ComponentType]->SetActive(true);
			return (T*)m_Components[T::ComponentType];
		}
		else
		{
			T* component = new T();
			//T* component = new T();
			// 연결
			m_Components[T::ComponentType] = dynamic_cast<Component::Component*>(component);
			// 컴포넌트 플래그 설정
			m_ComponentFlag = m_ComponentFlag | T::ComponentFlag;
			// 주인 설정
			component->SetEntity(this);

			return component;
		}
	}

	if (std::is_base_of<Component::ScriptComponent, T>::value)
	{
		for (Component::ScriptComponent* existingScript : m_Scripts)
		{
			if (dynamic_cast<T*>(existingScript) != nullptr)
			{
				
				return dynamic_cast<T*>(existingScript);
			}
		}

		T* _script = new T();

		m_Scripts.push_back((Component::ScriptComponent*)_script);

		_script->SetEntity(this);
		return _script;
	}

	else
	{
		//ErrorBox(L"Non-Component Error");
	}
	return nullptr;
}

template<typename T>
inline void Engine::Entity::Entity::RemoveComponent()
{
	// 널 포인터 또는 컴포넌트 클래스를 상속받지 않았는지 확인함
	if (!std::is_base_of<Component::Component, T>::value)
	{
		//ErrorBox(L"Non-Component Error");
	}
	else
	{
		// 컴포넌트 존재유무 확인
		if (m_Components[T::ComponentType] == nullptr || m_Components[T::ComponentType]->m_IsComponentActive == false)
		{
			return;
		}
		else
		{
			/*SAFE_DELETE(m_Components[T::ComponentType]);*/
			m_Components[T::ComponentType]->m_IsComponentActive = false;
			m_ComponentFlag -= T::ComponentFlag;
		}
	}
}

template<typename T>
inline T* Engine::Entity::Entity::GetComponent()
{
	// 컴포넌트 클래스를 상속받지 않았는지 확인함
	if (std::is_base_of<Component::Component, T>::value)
	{
		// 게임 오브젝트에 존재하는 컴포넌트인지 확인함
		if (m_Components[T::ComponentType] != nullptr)
		{
			return static_cast<T*>(m_Components[T::ComponentType]);
		}
	}

	return nullptr;
}

template<typename T>
inline T* Engine::Entity::Entity::GetComponentInParent()
{
	// 부모가 널 포인터인지 확인함
	if (m_pParent == nullptr)
	{
		return nullptr;
	}

	return m_pParent->GetComponent<T>();
}
