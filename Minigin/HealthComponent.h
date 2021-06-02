#pragma once
#include "BaseComponent.h"

class TextComponent;
class SubjectComponent;
class HealthComponent :public BaseComponent
{
public:

	virtual void Update(float)override;


	HealthComponent(std::weak_ptr<GameObject> parent, int maxHealth);
	void Damage(const int damageAmount);
	int GetHealth()const;
	void Heal(const int healAmount);
	virtual ~HealthComponent() = default;
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) = delete;
private:

	int m_Health;
	int m_MaxHealt;
	std::weak_ptr<SubjectComponent> m_Subject;
};

