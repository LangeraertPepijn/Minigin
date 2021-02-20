#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

void dae::FpsComponent::Update(float deltaTime)
{
	m_Frames++;
	m_AccumulatedTime += deltaTime;
	if (m_AccumulatedTime > m_SecInterval)
	{
		m_FPS = m_Frames;
		m_Frames = 0;
		m_pTextComponent->SetText(std::to_string(m_FPS)+" FPS");

		m_AccumulatedTime -= m_SecInterval;
	}


}
int dae::FpsComponent::GetFps()
{
	return m_FPS;
}
dae::FpsComponent::FpsComponent(std::weak_ptr<GameObject> parent)
	: BaseComponent(parent)
	, m_AccumulatedTime{}
	, m_FPS{}
	, m_Frames{}
	, m_SecInterval{1.f}
{
	m_pTextComponent = m_pParent.lock()->GetComponent<TextComponent>();
	m_NeedsUpdate = true;
}

