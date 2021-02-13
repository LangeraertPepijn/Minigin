#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject : public SceneObject
	{
	public:
		
		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		virtual void Update(float deltaTime)override;
		virtual void Render()  override ;
	
		template <typename T>
		T* GetComponent()const;

		const std::vector<BaseComponent*> GetComponents();

		BaseComponent* AddComponent(BaseComponent* newComponent);


		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		

	private:
		std::vector<BaseComponent*> m_Components{};
	
		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};
	};


	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		for (BaseComponent* component : m_Components)
		{
			auto temp = dynamic_cast<T*>(component) ;
			if (temp!=nullptr)
			{
				return temp;
			}
		}
		return nullptr;
	}

}

