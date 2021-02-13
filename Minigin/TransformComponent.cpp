#include "MiniginPCH.h"
#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(std::shared_ptr<GameObject> parent, const glm::vec3& pos)
	: BaseComponent(parent)
	, m_Pos{pos}
{
}



void dae::TransformComponent::SetTransform(const glm::vec3& newPos)
{
	m_Pos = newPos;
}

const glm::vec3& dae::TransformComponent::GetTransform()const
{
	return m_Pos;
}

void dae::TransformComponent::AddTransform(const glm::vec3& vecToAdd)
{
	m_Pos += vecToAdd;
}

void dae::TransformComponent::MulTransform(const glm::vec3& vecToMul)
{
	m_Pos *= vecToMul;
}

void dae::TransformComponent::MulTransformScalar(const float scalar)
{
	m_Pos *= scalar;
}




