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
	m_pCoilyGrid = coily->GetComponent<GridComponent>();
	m_pCoilyMoveComp=coily->GetComponent<CoilyMoveComponent>();

}

MoveCoily::~MoveCoily()
{
}

void MoveCoily::Execute()
{

	

		if (m_pCoilyMoveComp->CanPlayerControll())
		{
			if (m_pCoilyMoveComp->CanMove())
			{
				auto pos = m_pCoilyGrid->UpdatePos(m_Step);
				m_pCoilyMoveComp->SetMoved(true);

				m_pCoilyMoveComp->Move(pos);
			}
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
	if (m_QbertMove->GetCanMove())
	{
		auto pos = m_QbertGrid->UpdatePos(m_Step);
		if (pos.z >= 0)
		{
			
			if (BlockManager::GetInstance().ChangeBlock(m_QbertGrid->GetIndex()))
			{
				m_QbertGrid->IncreaseScore(25);
				
			}
			pos.z = 0;
		}
		m_QbertMove->Move(pos);
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
	
	if (m_QbertMove->GetCanMove())
	{
		auto pos = m_QbertGrid->UpdatePos(m_Step);
		if (pos.z >= 0)
		{
			if (BlockManager::GetInstance().ChangeBlock(m_QbertGrid->GetIndex()))
				m_QbertGrid->IncreaseScore(25);
			pos.z = 0;
		}
		m_QbertMove->Move(pos);
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
	if (m_QbertMove->GetCanMove())
	{

		auto pos = m_QbertGrid->UpdatePos(m_Step);
		if (pos.z >= 0)
		{
			if (BlockManager::GetInstance().ChangeBlock(m_QbertGrid->GetIndex()))
				m_QbertGrid->IncreaseScore(25);
			pos.z = 0;
		}

		m_QbertMove->Move(pos);
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
	if (m_QbertMove->GetCanMove())
	{
		auto pos = m_QbertGrid->UpdatePos(m_Step);
		if (pos.z >= 0)
		{
			if (BlockManager::GetInstance().ChangeBlock(m_QbertGrid->GetIndex()))
				m_QbertGrid->IncreaseScore(25);

			pos.z = 0;
		}

		m_QbertMove->Move(pos);
	}
}

