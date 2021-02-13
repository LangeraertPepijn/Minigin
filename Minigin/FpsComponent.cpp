#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

void dae::FpsComponent::Update(float deltaTime)
{
	m_Frames++;
	m_AccumulatedTime += deltaTime;
	if (m_AccumulatedTime > 1.f)
	{
		m_FPS = m_Frames;
		m_Frames = 0;
		m_pParent->GetComponent<TextComponent>()->SetText(std::to_string(m_FPS)+" FPS");
		m_AccumulatedTime -= 1;
	}


}
int dae::FpsComponent::GetFps()
{
	return m_FPS;
}
dae::FpsComponent::FpsComponent(std::shared_ptr<GameObject> parent)
	: BaseComponent(parent)
	, m_AccumulatedTime{}
	, m_FPS{}
	, m_Frames{}
{
	m_NeedsUpdate = true;
}

