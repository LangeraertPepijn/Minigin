#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "Event.h"


class ObserverComponent :public BaseComponent
{
public:

	virtual void Update(float)override;
	ObserverComponent(std::weak_ptr<GameObject> parent, std::shared_ptr<Observer>);
	virtual ~ObserverComponent() = default;
	ObserverComponent(const ObserverComponent& other) = delete;
	ObserverComponent(ObserverComponent&& other) = delete;
	ObserverComponent& operator=(const ObserverComponent& other) = delete;
	ObserverComponent& operator=(ObserverComponent&& other) = delete;
	virtual void Notify(const std::shared_ptr<GameObject> actor, Event event) ;
private:
	std::shared_ptr<Observer> m_Observer;
};

