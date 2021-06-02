#pragma once
#include "Observer.h"


class TextComponent;
class PlayerObserver : public Observer
{
public:
	PlayerObserver();
	~PlayerObserver();
	PlayerObserver(const PlayerObserver& other) = delete;
	PlayerObserver(PlayerObserver&& other) = delete;
	PlayerObserver& operator=(const PlayerObserver& other) = delete;
	PlayerObserver& operator=(PlayerObserver&& other) = delete;
	void Notify(const std::shared_ptr<GameObject> actor, Event event,const std::weak_ptr<GameObject> parent) override;
private:
};

