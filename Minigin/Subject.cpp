#include "Subject.h"
#include <stdexcept>
#include "Observer.h"

void dae::Subject::AddObserver(Observer* observer)
{
	if(observer == nullptr)
		throw std::runtime_error("observer is nullptr");

	auto it = std::find(begin(m_pObservers), end(m_pObservers), observer);

	if (it != end(m_pObservers))
		throw std::runtime_error("Tried adding duplicate observer");

	m_pObservers.push_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	if (observer == nullptr)
		throw std::runtime_error("observer is nullptr");

	auto it = std::find(begin(m_pObservers), end(m_pObservers), observer);

	if (it == end(m_pObservers))
		throw std::runtime_error("Tried removing observer that doesn't exist");

	m_pObservers.erase(it);
}

void dae::Subject::Notify(Component* component, unsigned event)
{
	if (component == nullptr)
		throw std::runtime_error("component is nullptr");

	for (Observer* observer : m_pObservers)
	{
		observer->OnNotify(component, event);
	}
}

void dae::Subject::Notify(unsigned event)
{
	for (Observer* observer : m_pObservers)
	{
		observer->OnNotify(event);
	}
}