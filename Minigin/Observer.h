#pragma once
#include "Component.h"

namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(Component* component, unsigned event) = 0;
	};
}