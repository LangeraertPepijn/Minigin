#include "MiniginPCH.h"
#include "HudTransformComponent.h"

dae::HudTransformComponent::HudTransformComponent(std::weak_ptr<HudObject> parent, const glm::vec3& pos)
	: HudBaseComponent(parent)
	, m_Pos{ pos }
{
}



void dae::HudTransformComponent::SetTransform(const glm::vec3& newPos)
{
	m_Pos = newPos;
}

const glm::vec3& dae::HudTransformComponent::GetTransform()const
{
	return m_Pos;
}

void dae::HudTransformComponent::AddTransform(const glm::vec3& vecToAdd)
{
	m_Pos += vecToAdd;
}

void dae::HudTransformComponent::MulTransform(const glm::vec3& vecToMul)
{
	m_Pos *= vecToMul;
}

void dae::HudTransformComponent::MulTransformScalar(const float scalar)
{
	m_Pos *= scalar;
}

void dae::HudTransformComponent::Update(float)
{
}




