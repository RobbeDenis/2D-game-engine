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

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

	protected:
		void Notify(Component* component, unsigned event);

	private:
		std::vector<Observer*> m_pObservers;
	};
}