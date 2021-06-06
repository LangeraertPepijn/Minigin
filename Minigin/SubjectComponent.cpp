#include "MiniginPCH.h"
#include "SubjectComponent.h"

SubjectComponent::SubjectComponent(std::weak_ptr<GameObject> parent)
	: BaseComponent(parent)
{
}

void SubjectComponent::Update(float)
{
}

void SubjectComponent::SetParent(std::weak_ptr<GameObject> parent)
{
	m_pParent = parent;
}

void SubjectComponent::AddObserver(const std::weak_ptr<ObserverComponent> observer)
{
	m_Observers.push_back(observer);
}

void SubjectComponent::RemoveObserver(const std::weak_ptr<ObserverComponent> observer)
{
	const auto temp = std::find_if(m_Observers.begin(), m_Observers.end(), [&observer](const std::weak_ptr<ObserverComponent>& ptr1) {
		return ptr1.lock() == observer.lock();
		});

	if (m_Observers.end() != temp)
	{
		m_Observers.erase(temp);
	}
}

void SubjectComponent::Notify(Event event)
{
	for (size_t i{}; i < m_Observers.size(); i++)
	{
		if(m_Observers[i].use_count())
			m_Observers[i].lock()->Notify(m_pParent.lock(), event);
	}
}
