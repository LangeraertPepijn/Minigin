#pragma once
#include "BaseComponent.h"
#include "ObserverComponent.h"
namespace dae
{

	class SubjectComponent :public BaseComponent
	{
	public:
		SubjectComponent(std::weak_ptr<GameObject> parent);
		virtual ~SubjectComponent()= default;
		SubjectComponent(const SubjectComponent& other) = delete;
		SubjectComponent(SubjectComponent&& other) = delete;
		SubjectComponent& operator=(const SubjectComponent& other) = delete;
		SubjectComponent& operator=(SubjectComponent&& other) = delete;

		virtual void Update(float)override;
		
		void AddObserver(const std::weak_ptr<ObserverComponent> observer);
		void RemoveObserver(const std::weak_ptr<ObserverComponent> observer);
		void Notify(Event event);
	private:
		std::vector< std::weak_ptr<ObserverComponent>> m_Observers;
	};


}