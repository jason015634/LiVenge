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
		/// 새로운 컴포넌트 작성시 이곳에 타입 추가
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
		/// 컴포넌트 클래스 규칙
		/// GameObject->AddComponent<T>() 형태를 유지하기 위해서 생성자에는 아무것도 넣지 않기
		/// 모든 컴포넌트들은 컴포넌트 플래그 및 타입을 정적 상수로 선언 및 정의한다.
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
