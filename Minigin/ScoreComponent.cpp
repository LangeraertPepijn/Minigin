#include "MiniginPCH.h"
#include "ScoreComponent.h"

#include "GameObject.h"
//#include "Observer.h"
#include "SubjectComponent.h"
#include "HudTextComponent.h"

void ScoreComponent::Update(float )
{

}

int ScoreComponent::GetScore() const
{
	return m_Score;
}

void ScoreComponent::SetScore(int score)
{
	m_Score = score;

}

void ScoreComponent::IncreaseScore(int diff)
{
	if (diff > 0)
	{
		m_Score += diff;
		if (m_Subject.lock() != nullptr)
		{
			m_Subject.lock()->Notify(Event{int(Event::Events::Scored)});
		}
		else
		{
			m_Subject = m_pParent.lock()->GetComponent<SubjectComponent>();
			m_Subject.lock()->Notify(Event{ int(Event::Events::Scored) });

		}
		
	}
}

void ScoreComponent::DecreaseScore(int diff)
{
	if (diff > 0)
	{
		m_Score -= diff;
	}
}

ScoreComponent::ScoreComponent(std::weak_ptr<GameObject> parent)
	: BaseComponent(parent)
{

}
