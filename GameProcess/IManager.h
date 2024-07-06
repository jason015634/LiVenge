#pragma once

namespace Engine
{
	class IManager
	{
	public:
		IManager() {}
		virtual ~IManager() {}

	public:
		virtual bool Initialize() abstract;
		virtual void Finalize() abstract;
	};
}