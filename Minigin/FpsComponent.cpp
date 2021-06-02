#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

void FpsComponent::Update(float deltaTime)
{

	m_AccumulatedTime += deltaTime;
	if (m_AccumulatedTime > m_SecInterval)
	{
		m_pTextComponent->SetText(std::to_string(int(1/deltaTime))+" FPS");
		m_AccumulatedTime -= m_SecInterval;
	}


}

FpsComponent::FpsComponent(std::weak_ptr<GameObject> parent)
	: BaseComponent(parent)
	, m_AccumulatedTime{}
	, m_SecInterval{1.f}
{
	m_pTextComponent = m_pParent.lock()->GetComponent<TextComponent>();
	m_NeedsUpdate = true;
}

