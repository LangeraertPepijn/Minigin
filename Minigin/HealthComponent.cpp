#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "SubjectComponent.h"

void dae::HealthComponent::Update(float )
{
	
}

dae::HealthComponent::HealthComponent(std::weak_ptr<GameObject> parent, int maxHealth)
	:BaseComponent(parent)
	,m_MaxHealt(maxHealth)
	,m_Health(maxHealth)
{
}

void dae::HealthComponent::Damage(const int damageAmount)
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
			m_Subject.lock()->Notify(Event::Damaged);
		}
		else
		{
			m_Subject = m_pParent.lock()->GetComponent<SubjectComponent>();
			m_Subject.lock()->Notify(Event::Damaged);
			
		}
	}
	else
	{
		if (m_Subject.lock() != nullptr)
		{
			m_Subject.lock()->Notify(Event::Died);
		}
		else
		{
			m_Subject = m_pParent.lock()->GetComponent<SubjectComponent>();
			m_Subject.lock()->Notify(Event::Died);

		}

	}
}

int dae::HealthComponent::GetHealth() const
{
	return m_Health;
}

void dae::HealthComponent::Heal(const int healAmount)
{
	if(healAmount <0)
	{
		return;
	}
	m_Health += healAmount;
}
