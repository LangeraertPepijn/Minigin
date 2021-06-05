#include "QBertPCH.h"
#include "QbertHealthObserver.h"



#include "CoilyMoveComponent.h"


QbertHealthObserver::QbertHealthObserver()
{
}

QbertHealthObserver::~QbertHealthObserver()
{
}

void QbertHealthObserver::Notify(const std::shared_ptr<GameObject> actor, Event event,
                                 const std::weak_ptr<GameObject> parent)
{
	if( event.CurrentEvent==int(Event::Events::Damaged))
	{
		parent.lock()->GetComponent<CoilyMoveComponent>()->Reset();
	}
}
