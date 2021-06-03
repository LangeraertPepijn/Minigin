#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "SubjectComponent.h"

void HealthComponent::Update(float )
{
	
}

HealthComponent::HealthComponent(std::weak_ptr<GameObject> parent, int maxHealth)
	:BaseComponent(parent)
	,m_MaxHealt(maxHealth)
	,m_Health(maxHealth)
{
}

void HealthComponent::Damage(const int damageAmount)
{
	if (damageAmount < 0)
	{
		return;
	}

	m_Health -= damageAmount;
	if (m_Health > 0)
	{
		if (m_Subject.lock()!=nullptr)
		{
			m_Subject.lock()->Notify(Event{ int(Event::Events::Damaged) });
		}
		else
		{
			m_Subject = m_pParent.lock()->GetComponent<SubjectComponent>();
			m_Subject.lock()->Notify(Event{ int(Event::Events::Damaged) });
			
		}
	}
	else
	{
		if (m_Subject.lock() != nullptr)
		{
			m_Subject.lock()->Notify(Event{ int(Event::Events::Died) });
		}
		else
		{
			m_Subject = m_pParent.lock()->GetComponent<SubjectComponent>();
			m_Subject.lock()->Notify(Event{ int(Event::Events::Died) });

		}

	}
}

int HealthComponent::GetHealth() const
{
	return m_Health;
}

void HealthComponent::Heal(const int healAmount)
{
	if(healAmount <0)
	{
		return;
	}
	m_Health += healAmount;
}
