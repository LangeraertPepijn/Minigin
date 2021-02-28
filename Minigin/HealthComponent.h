#pragma once
#include "BaseComponent.h"
namespace dae
{
	class TextComponent;

	class HealthComponent :public BaseComponent
	{
	public:

		virtual void Update(float deltaTime)override;


		HealthComponent(std::weak_ptr<GameObject> parent,float maxHealth);
		void Damage(const float damageAmount);
		float GetHealth()const;
		void Heal(const float healAmount);
		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;
	private:

		float m_Health;
		float m_MaxHealt;
	};
}
