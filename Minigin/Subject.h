#pragma once
#include <vector>
#include "Component.h"

namespace dae
{
	class Observer;
	class Subject
	{
	public:
		Subject() = default;
		virtual ~Subject() = default;

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

	protected:
		void Notify(Component* component, unsigned event);
		void Notify(unsigned event);

	private:
		std::vector<Observer*> m_pObservers;
	};
}