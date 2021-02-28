#pragma once


namespace dae
{
	class Observer;
	enum class Event;
	class GameObject;

	class Subject
	{
	public:
		Subject();
		~Subject();
		
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;
		void AddObserver(const std::shared_ptr<Observer > observer);
		void RemoveObserver(const std::shared_ptr<Observer > observer);
		void Notify(const std::shared_ptr<GameObject> actor, Event event);
	protected:
	
	private:
		std::vector< std::shared_ptr<Observer>> m_Observers;
	};

}