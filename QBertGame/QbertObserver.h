#pragma once
#include <Observer.h>

class QbertObserver final :public Observer
{
public:
	QbertObserver();
	~QbertObserver();
	QbertObserver(const QbertObserver& other) = delete;
	QbertObserver(QbertObserver&& other) = delete;
	QbertObserver& operator=(const QbertObserver& other) = delete;
	QbertObserver& operator=(QbertObserver&& other) = delete;
	void Notify(const std::shared_ptr<GameObject> actor, Event event, const std::weak_ptr<GameObject> parent) override;
private:
	
};

