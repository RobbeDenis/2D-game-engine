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

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
	};
}