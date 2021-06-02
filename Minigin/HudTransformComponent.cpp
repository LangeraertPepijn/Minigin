#include "MiniginPCH.h"
#include "HudTransformComponent.h"

HudTransformComponent::HudTransformComponent(std::weak_ptr<HudObject> parent, const glm::vec3& pos)
	: HudBaseComponent(parent)
	, m_Pos{ pos }
{
}



void HudTransformComponent::SetTransform(const glm::vec3& newPos)
{
	m_Pos = newPos;
}

const glm::vec3& HudTransformComponent::GetTransform()const
{
	return m_Pos;
}

void HudTransformComponent::AddTransform(const glm::vec3& vecToAdd)
{
	m_Pos += vecToAdd;
}

void HudTransformComponent::MulTransform(const glm::vec3& vecToMul)
{
	m_Pos *= vecToMul;
}

void HudTransformComponent::MulTransformScalar(const float scalar)
{
	m_Pos *= scalar;
}

void HudTransformComponent::Update(float)
{
}




