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
			// �θ� ��ƼƼ ��������
			Entity* GetParent() const
			{
				return m_pParent;
			}
			// �θ� ��ƼƼ ����
			void SetParent(Entity* _parent)
			{
				m_pParent = _parent;
				m_pParent->AddChild(this);
			}
			// �ڽ� ��ƼƼ �߰�
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
			// ��ƼƼ �̸�
			std::wstring m_EntityName;

		protected:
			ULONGLONG m_ComponentFlag = 0;

			// �θ� ��ƼƼ - �������� �ֽ��ϴ�.
			Entity* m_pParent = nullptr;
			std::vector<Entity*> m_pChilds;

			Component::Component* m_Components[64] = { nullptr, };
			std::vector<Component::ScriptComponent*> m_Scripts;

			/// <summary>
			/// ������Ʈ ���� (������ �Լ���� �� �� ������ ���� ����)
			/// �ش� ������Ʈ���� ���� ���̴� �ٸ� ������Ʈ��� �����ͷ� �̸� ����ִ°� �ٶ�����
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
	// �� ������ �Ǵ� ������Ʈ Ŭ������ ��ӹ��� �ʾҴ��� Ȯ����
	if (std::is_base_of<Component::Component, T>::value)
	{
		// AddComponent �ȿ��� �������ִ� ����
		// 1. �� ������ �ڵ��� ����ȭ
		// 2. �����ڸ� ���� �Ҵ��ϰ� �Ǹ� ������ ������ �� �޸� ������ �߻���
		// 3. SceneComponent �� �ƴ� ���(������ ���� �ʱ⋚����), ������ �߻����� �ʾ� �߰��ϱ� ���� ����

		// ����
		// ���� ������Ʈ�� �����ϴ� ������Ʈ���� Ȯ����
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
			// ����
			m_Components[T::ComponentType] = dynamic_cast<Component::Component*>(component);
			// ������Ʈ �÷��� ����
			m_ComponentFlag = m_ComponentFlag | T::ComponentFlag;
			// ���� ����
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
	// �� ������ �Ǵ� ������Ʈ Ŭ������ ��ӹ��� �ʾҴ��� Ȯ����
	if (!std::is_base_of<Component::Component, T>::value)
	{
		//ErrorBox(L"Non-Component Error");
	}
	else
	{
		// ������Ʈ �������� Ȯ��
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
	// ������Ʈ Ŭ������ ��ӹ��� �ʾҴ��� Ȯ����
	if (std::is_base_of<Component::Component, T>::value)
	{
		// ���� ������Ʈ�� �����ϴ� ������Ʈ���� Ȯ����
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
	// �θ� �� ���������� Ȯ����
	if (m_pParent == nullptr)
	{
		return nullptr;
	}

	return m_pParent->GetComponent<T>();
}
