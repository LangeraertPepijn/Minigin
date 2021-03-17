#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"


namespace dae
{
	class Subject;
	class Observer;
	class Texture2D;
	class GameObject final: public  std::enable_shared_from_this<GameObject>
	{
	public:
		


		virtual void Update(float deltaTime);
		virtual void Render()   ;
	
		template <typename T>
		std::shared_ptr <T> GetComponent()const;
		
		std::shared_ptr<Subject> GetSubject()const;
		void SetSubject(std::shared_ptr<Subject>subject);
		const std::vector<std::shared_ptr<BaseComponent>>& GetComponents() const;

		std::shared_ptr<BaseComponent> AddComponent(std::shared_ptr<BaseComponent> newComponent);


		GameObject();
		GameObject(const glm::vec3& pos);
		virtual ~GameObject();
		GameObject(const GameObject& other) ;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_Components{};
		std::shared_ptr<Subject> m_ActorChanged;
	};


	template<typename T>
	inline std::shared_ptr <T> GameObject::GetComponent() const
	{
		for (std::shared_ptr<BaseComponent> component : m_Components)
		{
			auto temp = std::dynamic_pointer_cast<T>(component) ;
			if (temp!=nullptr)
			{
				return temp;
			}
		}
		return nullptr;
	}

}

