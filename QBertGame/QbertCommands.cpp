#include "QBertPCH.h"
#include "QbertCommands.h"
#include "GridComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "BlockManager.h"
#include  "CoilyMoveComponent.h"
#include "QBertMoveComponent.h"

MoveCoily::MoveCoily(std::shared_ptr<GameObject> coily,const glm::ivec3& step)
	: m_Step(step)
{
	m_CoilyGrid = coily->GetComponent<GridComponent>();
	m_CoilyMoveComp=coily->GetComponent<CoilyMoveComponent>();

}

MoveCoily::~MoveCoily()
{
}

void MoveCoily::Execute()
{
	if (m_CoilyMoveComp.lock()->CanMove())
	{
		auto pos = m_CoilyGrid.lock()->UpdatePos(m_Step);
		m_CoilyMoveComp.lock()->SetMoved(true);

		m_CoilyMoveComp.lock()->Move(pos);
	}
	
}

MoveRightDown::MoveRightDown(std::shared_ptr<GameObject> qbert)
{
	m_Qbert = qbert->GetComponent<TextureComponent>();
	m_QbertGrid = qbert->GetComponent<GridComponent>();
	m_QbertMove = qbert->GetComponent<QBertMoveComponent>();
}

MoveRightDown::~MoveRightDown()
{
}

void MoveRightDown::Execute()
{
	if (m_QbertMove.lock()->GetCanMove())
	{
		auto pos = m_QbertGrid.lock()->UpdatePos(m_Step);
		if (pos.z >= 0)
		{
			if (BlockManager::GetInstance().ChangeBlock(m_QbertGrid.lock()->GetIndex()))
				m_QbertGrid.lock()->IncreaseScore(25);
			pos.z = 0;
		}
		m_QbertMove.lock()->Move(pos);
	}
	
}

MoveLeftDown::MoveLeftDown(std::shared_ptr<GameObject> qbert)
{
	m_Qbert = qbert->GetComponent<TextureComponent>();
	m_QbertGrid = qbert->GetComponent<GridComponent>();
	m_QbertMove = qbert->GetComponent<QBertMoveComponent>();
}

MoveLeftDown::~MoveLeftDown()
{
}

void MoveLeftDown::Execute()
{
	
	if (m_QbertMove.lock()->GetCanMove())
	{
		auto pos = m_QbertGrid.lock()->UpdatePos(m_Step);
		if (pos.z >= 0)
		{
			if (BlockManager::GetInstance().ChangeBlock(m_QbertGrid.lock()->GetIndex()))
				m_QbertGrid.lock()->IncreaseScore(25);
			pos.z = 0;
		}
		m_QbertMove.lock()->Move(pos);
	}


}


MoveLeftUp::MoveLeftUp(std::shared_ptr<GameObject> qbert)

{
	m_Qbert = qbert->GetComponent<TextureComponent>();
	m_QbertGrid = qbert->GetComponent<GridComponent>();
	m_QbertMove = qbert->GetComponent<QBertMoveComponent>();
}

MoveLeftUp::~MoveLeftUp()
{
}

void MoveLeftUp::Execute()
{
	if (m_QbertMove.lock()->GetCanMove())
	{
		
	auto pos = m_QbertGrid.lock()->UpdatePos(m_Step);
	if (pos.z >= 0)
	{
		if (BlockManager::GetInstance().ChangeBlock(m_QbertGrid.lock()->GetIndex()))
			m_QbertGrid.lock()->IncreaseScore(25);
		pos.z = 0;
	}

	m_QbertMove.lock()->Move(pos);
	}
}

MoveRightUp::MoveRightUp(std::shared_ptr<GameObject> qbert)

{
	m_Qbert = qbert->GetComponent<TextureComponent>();
	m_QbertGrid = qbert->GetComponent<GridComponent>();
	m_QbertMove = qbert->GetComponent<QBertMoveComponent>();
}

MoveRightUp::~MoveRightUp()
{
}

void MoveRightUp::Execute()
{
	if (m_QbertMove.lock()->GetCanMove())
	{
		auto pos = m_QbertGrid.lock()->UpdatePos(m_Step);
		if (pos.z >= 0)
		{
			if (BlockManager::GetInstance().ChangeBlock(m_QbertGrid.lock()->GetIndex()))
				m_QbertGrid.lock()->IncreaseScore(25);

			pos.z = 0;
		}

		m_QbertMove.lock()->Move(pos);
	}
}

