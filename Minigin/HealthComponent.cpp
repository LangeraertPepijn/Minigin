#include "MiniginPCH.h"
#include "HealthComponent.h"

#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"

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

		m_pParent.lock()->GetSubject()->Notify(m_pParent.lock(), Event::Damaged);
	}
	else
	{
		m_pParent.lock()->GetSubject()->Notify(m_pParent.lock(), Event::Died);
		
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
