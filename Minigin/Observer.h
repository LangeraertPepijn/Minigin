#pragma once
#include "GameObject.h"
#include "Event.h"
namespace  dae
{

	class Observer
	{
	public:
		Observer() = default;
		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
		virtual ~Observer() = default;
		virtual void Notify(const std::shared_ptr<GameObject> actor, Event event,const std::weak_ptr<GameObject> parent) = 0;
	};

}
