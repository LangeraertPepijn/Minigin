#pragma once
#include "GameObject.h"

namespace  dae
{
	enum class Event: int
	{
		Scored,
		Damaged,
		Died
	};

	class Observer
	{
	public:
		Observer() = default;
		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
		virtual ~Observer() = default;
		virtual void Notify(const std::shared_ptr<GameObject> actor, Event event) = 0;
	};

}
