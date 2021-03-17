#include "MiniginPCH.h"
#include "ObserverComponent.h"

#include "GameObject.h"
#include "ScoreComponent.h"
#include "HealthComponent.h"
#include "TextComponent.h"
void dae::ObserverComponent::Update(float)
{
}

dae::ObserverComponent::ObserverComponent(std::weak_ptr<GameObject> parent)
	: BaseComponent(parent)

{
}

void dae::ObserverComponent::Notify(const std::shared_ptr<GameObject> actor, Event event)
{

	switch (event)
	{
	case Event::Scored:
	{
		const auto temp = actor->GetComponent<ScoreComponent>();
		if (temp)
		{
			m_pParent.lock()->GetComponent<TextComponent>()->SetText(std::to_string(temp->GetScore()) + " Score");
		}
		break;
	}
	case Event::Died:
	{
		m_pParent.lock()->GetComponent<TextComponent>()->SetText("You Died");
		break;
	}
	case Event::Damaged:
	{
		const auto temp = actor->GetComponent<HealthComponent>();
		if (temp)
		{
			m_pParent.lock()->GetComponent<TextComponent>()->SetText(std::to_string(temp->GetHealth()) + " Hp");
		}
		break;
	}
	}

}
