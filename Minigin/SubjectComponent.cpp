#include "MiniginPCH.h"
#include "SubjectComponent.h"

void dae::SubjectComponent::Update(float)
{
}

void dae::SubjectComponent::AddObserver(const std::weak_ptr<ObserverComponent> observer)
{
	m_Observers.push_back(observer);
}

void dae::SubjectComponent::RemoveObserver(const std::weak_ptr<ObserverComponent> observer)
{
	auto temp = std::find(m_Observers.begin(), m_Observers.end(), observer);
	if (m_Observers.end() != temp)
	{
		m_Observers.erase(temp);
	}
}

void dae::SubjectComponent::Notify(Event event)
{
	for (size_t i{}; i < m_Observers.size(); i++)
	{
		m_Observers[i].lock()->Notify(m_pParent.lock(), event);
	}
}
