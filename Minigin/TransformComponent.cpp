#include "MiniginPCH.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(std::weak_ptr<GameObject> parent, const glm::vec3& pos)
	: BaseComponent(parent)
	, m_Pos{pos}
{
}



void TransformComponent::SetTransform(const glm::vec3& newPos)
{
	m_Pos = newPos;
}

const glm::vec3& TransformComponent::GetTransform()const
{
	return m_Pos;
}

void TransformComponent::AddTransform(const glm::vec3& vecToAdd)
{
	m_Pos += vecToAdd;
}

void TransformComponent::MulTransform(const glm::vec3& vecToMul)
{
	m_Pos *= vecToMul;
}

void TransformComponent::MulTransformScalar(const float scalar)
{
	m_Pos *= scalar;
}

void TransformComponent::Update(float)
{
}




