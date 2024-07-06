#pragma once
#include "Base.h"


namespace Engine
{
	namespace Entity
	{
		class Entity;
	}

	namespace Component
	{
		/// <summary>
		/// ���ο� ������Ʈ �ۼ��� �̰��� Ÿ�� �߰�
		/// </summary>
		typedef enum class E_ComponentType : ULONGLONG
		{
			GameObject,
			Transform,
			Animator,
			FSM,
			Collider,
			UI,
			Render,
			Camera,
			Rectangle,
			EffectAnimator,
			End
		};

		typedef enum class asda : ULONGLONG
		{
			asd = (int)E_ComponentType::End,
			b,
			c,
			d
		};

		/// <summary>
		/// ������Ʈ Ŭ���� ��Ģ
		/// GameObject->AddComponent<T>() ���¸� �����ϱ� ���ؼ� �����ڿ��� �ƹ��͵� ���� �ʱ�
		/// ��� ������Ʈ���� ������Ʈ �÷��� �� Ÿ���� ���� ����� ���� �� �����Ѵ�.
		/// </summary>

		class Component : public Base
		{
		public:
			Component() {}
			virtual ~Component() {}

		};

		struct Vector3
		{
			FLOAT X;
			FLOAT Y;
			FLOAT Z;
		};

		
	}
}
