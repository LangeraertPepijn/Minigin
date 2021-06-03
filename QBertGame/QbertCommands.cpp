#include "QBertPCH.h"
#include "QbertCommands.h"
#include "GridComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "BlockManager.h"


Move::Move(std::shared_ptr<GameObject> qbert, glm::vec3 posFix)
	: m_PosFix(posFix)
{
	m_Qbert = qbert->GetComponent<TextureComponent>();
	m_QbertGrid = qbert->GetComponent<GridComponent>();
}

Move::~Move()
{
}

void Move::Execute()
{
		auto temp = m_QbertGrid->UpdatePos(m_Step);
	if(temp.z>=0)
	{
		if (BlockManager::GetInstance().ChangeBlock(m_QbertGrid->GetIndex()))
			m_QbertGrid->IncreaseScore();
		temp.z = 0;
	}
	m_Qbert->Translate(temp+m_PosFix);
	
}

MoveRightDown::MoveRightDown(std::shared_ptr<GameObject> qbert, glm::vec3 posFix)
	: m_PosFix(posFix)
{
	m_Qbert = qbert->GetComponent<TextureComponent>();
	m_QbertGrid = qbert->GetComponent<GridComponent>();
}

MoveRightDown::~MoveRightDown()
{
}

void MoveRightDown::Execute()
{
	auto temp = m_QbertGrid->UpdatePos(m_Step);
	if(temp.z>=0)
	{
		if (BlockManager::GetInstance().ChangeBlock(m_QbertGrid->GetIndex()))
			m_QbertGrid->IncreaseScore();
		temp.z = 0;
	}
	m_Qbert->Translate(temp+m_PosFix);
	
}

MoveLeftDown::MoveLeftDown(std::shared_ptr<GameObject> qbert, glm::vec3 posFix)
	: m_PosFix(posFix)
{
	m_Qbert = qbert->GetComponent<TextureComponent>();
	m_QbertGrid = qbert->GetComponent<GridComponent>();
}

MoveLeftDown::~MoveLeftDown()
{
}

void MoveLeftDown::Execute()
{
	auto temp = m_QbertGrid->UpdatePos(m_Step);
	if (temp.z >= 0)
	{
		if (BlockManager::GetInstance().ChangeBlock(m_QbertGrid->GetIndex()))
			m_QbertGrid->IncreaseScore();
		temp.z = 0;
	}
	m_Qbert->Translate(temp + m_PosFix);

}


MoveLeftUp::MoveLeftUp(std::shared_ptr<GameObject> qbert, glm::vec3 posFix)
	: m_PosFix(posFix)
{
	m_Qbert = qbert->GetComponent<TextureComponent>();
	m_QbertGrid = qbert->GetComponent<GridComponent>();
}

MoveLeftUp::~MoveLeftUp()
{
}

void MoveLeftUp::Execute()
{
	auto temp = m_QbertGrid->UpdatePos(m_Step);
	if (temp.z >= 0)
	{
		if (BlockManager::GetInstance().ChangeBlock(m_QbertGrid->GetIndex()))
			m_QbertGrid->IncreaseScore();
		temp.z = 0;
	}
	m_Qbert->Translate(temp + m_PosFix);
}

MoveRightUp::MoveRightUp(std::shared_ptr<GameObject> qbert, glm::vec3 posFix)
	: m_PosFix(posFix)
{
	m_Qbert = qbert->GetComponent<TextureComponent>();
	m_QbertGrid = qbert->GetComponent<GridComponent>();
}

MoveRightUp::~MoveRightUp()
{
}

void MoveRightUp::Execute()
{
	auto temp = m_QbertGrid->UpdatePos(m_Step);
	if (temp.z >= 0)
	{
		if (BlockManager::GetInstance().ChangeBlock(m_QbertGrid->GetIndex()))
			m_QbertGrid->IncreaseScore();
		
		temp.z = 0;
	}
	m_Qbert->Translate(temp + m_PosFix);
}

