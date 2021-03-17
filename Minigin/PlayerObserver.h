#pragma once
#include "Observer.h"

namespace dae
{
	class TextComponent;
	class PlayerObserver : public Observer
	{
	public:
		PlayerObserver(std::shared_ptr<GameObject> objectToObserve, std::shared_ptr<GameObject> textComponent);
		~PlayerObserver();
		PlayerObserver(const PlayerObserver& other) = delete;
		PlayerObserver(PlayerObserver&& other) = delete;
		PlayerObserver& operator=(const PlayerObserver& other) = delete;
		PlayerObserver& operator=(PlayerObserver&& other) = delete;
		void Notify(const std::shared_ptr<GameObject> actor, Event event) override;
	private:
		std::weak_ptr<GameObject> m_ObservedObject;
		std::weak_ptr<GameObject> m_TextObject;
	};
}
