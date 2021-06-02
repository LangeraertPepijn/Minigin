#include "MiniginPCH.h"
#include "ObserverComponent.h"

#include "GameObject.h"
#include "ScoreComponent.h"
#include "HealthComponent.h"
#include "TextComponent.h"
void ObserverComponent::Update(float)
{
}
ObserverComponent::ObserverComponent(std::weak_ptr<GameObject> parent, std::shared_ptr<Observer> observer)
	: BaseComponent(parent)
	, m_Observer(observer)

{
}

void ObserverComponent::Notify(const std::shared_ptr<GameObject> actor, Event event)
{

	//m_Observer->Notify(actor, event);
	m_Observer->Notify(actor, event,m_pParent);

}
