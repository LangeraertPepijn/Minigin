#include "MiniginPCH.h"
#include "PlayerObserver.h"

#include "TextComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

dae::PlayerObserver::PlayerObserver(std::shared_ptr<GameObject> objectToObserve,std::shared_ptr<GameObject> textComponent)
	:m_ObservedObject(objectToObserve)
	,m_TextObject(textComponent)
{
}

dae::PlayerObserver::~PlayerObserver()
{
}

void dae::PlayerObserver::Notify(const std::shared_ptr<GameObject> actor, Event event)
{
	if(actor==m_ObservedObject.lock())
	{
		switch (event)
		{
		case Event::Scored:
			{
			auto temp = m_ObservedObject.lock()->GetComponent<ScoreComponent>();
			m_TextObject.lock()->GetComponent<TextComponent>()->SetText(std::to_string(temp->GetScore())+ " Score");
			break;
			}
		case Event::Died:
			{
			m_ObservedObject.lock()->GetComponent<TextComponent>()->SetText("You Died");
			break;
			}
		case Event::Damaged:
			{
			auto temp = m_ObservedObject.lock()->GetComponent<HealthComponent>();
			if(temp)
			{
				m_ObservedObject.lock()->GetComponent<TextComponent>()->SetText(std::to_string(temp->GetHealth()) +" Hp");
					
			}
			break;
			}
		}
	}
}
