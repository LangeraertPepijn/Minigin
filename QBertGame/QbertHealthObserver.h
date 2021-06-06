#pragma once
#include <Observer.h>
class QbertHealthObserver final:
    public Observer
{
	public:
		QbertHealthObserver();
		~QbertHealthObserver();
		QbertHealthObserver(const QbertHealthObserver& other) = delete;
		QbertHealthObserver(QbertHealthObserver&& other) = delete;
		QbertHealthObserver& operator=(const QbertHealthObserver& other) = delete;
		QbertHealthObserver& operator=(QbertHealthObserver&& other) = delete;
		void Notify(const std::shared_ptr<GameObject> actor, Event event, const std::weak_ptr<GameObject> parent) override;
	private:

};

