#pragma once
#include "BaseComponent.h"

namespace  dae
{
	enum class Event : int
	{
		Scored,
		Damaged,
		Died
	};
	class ObserverComponent :public BaseComponent
	{
	public:

		virtual void Update(float)override;
		ObserverComponent(std::weak_ptr<GameObject> parent);
		virtual ~ObserverComponent() = default;
		ObserverComponent(const ObserverComponent& other) = delete;
		ObserverComponent(ObserverComponent&& other) = delete;
		ObserverComponent& operator=(const ObserverComponent& other) = delete;
		ObserverComponent& operator=(ObserverComponent&& other) = delete;
		virtual void Notify(const std::shared_ptr<GameObject> actor, Event event) ;
	private:
	};
}
