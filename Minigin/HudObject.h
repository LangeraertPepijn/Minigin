#pragma once
#include "HudBaseComponent.h"
#include "TransformComponent.h"


namespace dae
{
	class Font;
	class RenderComponent;
	class HudObject final: public std::enable_shared_from_this<HudObject>
	{
	public:
		HudObject( );
		~HudObject();
		HudObject(const HudObject& other) = delete;
		HudObject(HudObject&& other) = delete;
		HudObject& operator=(const HudObject& other) = delete;
		HudObject& operator=(HudObject&& other) = delete;
		
		template <typename T>
		std::shared_ptr <T> GetComponent()const;
		const std::vector<std::shared_ptr<HudBaseComponent>>& GetComponents() const;
		std::shared_ptr<HudBaseComponent> AddComponent(std::shared_ptr<HudBaseComponent> newComponent);
		void Update(float deltaTime);
		void Render() ;
	
	private:
		std::vector<std::shared_ptr<HudBaseComponent>> m_Components{};

	};
	template<typename T>
	inline std::shared_ptr <T> HudObject::GetComponent() const
	{
		for (std::shared_ptr<HudBaseComponent> component : m_Components)
		{
			auto temp = std::dynamic_pointer_cast<T>(component);
			if (temp != nullptr)
			{
				return temp;
			}
		}
		return nullptr;
	}
}
