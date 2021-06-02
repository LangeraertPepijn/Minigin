#include "MiniginPCH.h"
#include "PlayerObserver.h"

#include "TextComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "HudObject.h"
PlayerObserver::PlayerObserver()

{
}

PlayerObserver::~PlayerObserver()
{
}

void PlayerObserver::Notify(const std::shared_ptr<GameObject> actor, Event event,const std::weak_ptr<GameObject> parent)
{

	switch (event)
	{
	case Event::Scored:
	{
		auto temp = actor->GetComponent<ScoreComponent>();
		if (temp)
		{
			auto textComponents = parent.lock()->GetComponentsType<TextComponent>();
			if (textComponents.size() >= size_t(event) + 1)
				textComponents[size_t(event)]->SetText(std::to_string(temp->GetScore()) );
		}
		break;
	}
	case Event::Died:
	{
		auto textComponents = parent.lock()->GetComponentsType<TextComponent>();
		if (textComponents.size() >= size_t(Event::Damaged) + 1)
		textComponents[size_t(Event::Damaged)]->SetText("You Died");
		break;
	}
	case Event::Damaged:
	{
		auto temp = actor->GetComponent<HealthComponent>();
		if (temp)
		{
			auto textComponents = parent.lock()->GetComponentsType<TextComponent>();
			if(textComponents.size()>=size_t(event)+1)
				textComponents[size_t(event)]->SetText(std::to_string(temp->GetHealth()) );
		

		}
		break;
	}
	}
	
}
