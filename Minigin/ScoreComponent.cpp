#include "MiniginPCH.h"
#include "ScoreComponent.h"

#include "GameObject.h"
//#include "Observer.h"
#include "SubjectComponent.h"
#include "HudTextComponent.h"

void dae::ScoreComponent::Update(float )
{

}

int dae::ScoreComponent::GetScore() const
{
	return m_Score;
}

void dae::ScoreComponent::SetScore(int score)
{
	m_Score = score;

}

void dae::ScoreComponent::IncreaseScore(int diff)
{
	if (diff > 0)
	{
		m_Score += diff;
		if (m_Subject.lock() != nullptr)
		{
			m_Subject.lock()->Notify(Event::Scored);
		}
		else
		{
			m_Subject = m_pParent.lock()->GetComponent<SubjectComponent>();
			m_Subject.lock()->Notify(Event::Scored);

		}
		
	}
}

void dae::ScoreComponent::DecreaseScore(int diff)
{
	if (diff > 0)
	{
		m_Score -= diff;
	}
}

dae::ScoreComponent::ScoreComponent(std::weak_ptr<GameObject> parent)
	: BaseComponent(parent)
{

}
