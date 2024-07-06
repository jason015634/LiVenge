#pragma once
#include "Base.h"
#include "ComponentList.h"

namespace Engine
{

	namespace Component
	{

		class ScriptComponent : public Base
		{
		public:
			ScriptComponent() {}
			virtual ~ScriptComponent() {}
		public:
			virtual void Start() {};
			virtual void FixedUpdate() {};
			virtual void Update() {};
			virtual void LateUpdate() {};
			virtual void Finalize() {};

		};
	}
}