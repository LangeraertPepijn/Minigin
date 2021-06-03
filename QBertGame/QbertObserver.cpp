#include "QBertPCH.h"
#include "QbertObserver.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "QbertEvents.h"

QbertObserver::QbertObserver()
{
}

QbertObserver::~QbertObserver()
{
}

void QbertObserver::Notify(const std::shared_ptr<GameObject> actor, Event event, const std::weak_ptr<GameObject> parent)
{

	switch (Event::Events(event.CurrentEvent))
	{
	case Event::Events::Scored:
	{
		auto temp = actor->GetComponent<ScoreComponent>();
		if (temp)
		{
			auto textComponents = parent.lock()->GetComponentsType<TextComponent>();
			if (textComponents.size() >= size_t(event.CurrentEvent) + 1)
				textComponents[size_t(event.CurrentEvent)]->SetText(std::to_string(temp->GetScore()));
		}
		break;
	}
	case Event::Events::Died:
	{
		auto textComponents = parent.lock()->GetComponentsType<TextComponent>();
		if (textComponents.size() >= size_t(Event::Events::Damaged) + 1)
			textComponents[size_t(Event::Events::Damaged)]->SetText("You Died");
		break;
	}
	case Event::Events::Damaged:
	{
		auto temp = actor->GetComponent<HealthComponent>();
		if (temp)
		{
			auto textComponents = parent.lock()->GetComponentsType<TextComponent>();
			if (textComponents.size() >= size_t(event.CurrentEvent) + 1)
				textComponents[size_t(event.CurrentEvent)]->SetText(std::to_string(temp->GetHealth()));


		}
		break;
	}
	}
}
