#include "MiniginPCH.h"
#include "PlayerObserver.h"

#include "TextComponent.h"
#include "HealthComponent.h"

dae::PlayerObserver::PlayerObserver(std::shared_ptr<GameObject> objectToObserve,std::shared_ptr<TextComponent> textComponent)
	:m_ObservedObject(objectToObserve)
	,m_pTextComponent(textComponent)
{
}

dae::PlayerObserver::~PlayerObserver()
{
}

void dae::PlayerObserver::Notify(const std::shared_ptr<GameObject> actor, Event event)
{
	if(actor==m_ObservedObject)
	{
		switch (event)
		{
		case Event::Died:
			{
			m_pTextComponent->SetText("You Died");
			break;
			}
		case Event::Damaged:
			{
			auto temp = m_ObservedObject->GetComponent<HealthComponent>();
			if(temp)
			{
				m_pTextComponent->SetText(std::to_string(temp->GetHealth()));
					
			}
			break;
			}
		}
	}
}
