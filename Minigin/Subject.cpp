#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"
dae::Subject::Subject()
{
	
}

dae::Subject::~Subject()
{
}

void dae::Subject::AddObserver(const std::shared_ptr<Observer> observer)
{
	m_Observers.push_back(observer);
}


void dae::Subject::RemoveObserver(const std::shared_ptr<Observer> observer)
{
	auto temp = std::find(m_Observers.begin(), m_Observers.end(), observer);
	if(m_Observers.end()!= temp)
	{
		m_Observers.erase(temp);
	}
}

void dae::Subject::Notify(const std::shared_ptr<GameObject> actor, Event event)
{
	for (size_t i{};i< m_Observers.size();i++)
	{
		m_Observers[i]->Notify(actor, event);
	}
}
