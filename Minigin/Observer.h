#pragma once
#include "Component.h"

namespace dae
{
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;
		virtual void OnNotify(Component* component, unsigned event) = 0;
		virtual void OnNotify(unsigned event) = 0;
	};
}