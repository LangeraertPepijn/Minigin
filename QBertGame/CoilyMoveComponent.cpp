#include "QBertPCH.h"
#include "CoilyMoveComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "GridComponent.h"

void CoilyMoveComponent::Update(float dt)
{
	Move(dt);
}

void CoilyMoveComponent::SetParent(std::weak_ptr<GameObject> parent)
{
	m_pParent = parent;
	m_pTexture = parent.lock()->GetComponent<TextureComponent>();
}

bool* CoilyMoveComponent::GetCanMove()
{
	return &m_LockUpDir;
}

void CoilyMoveComponent::SetMoved(bool moved)
{
	m_Moved = moved;
}



void CoilyMoveComponent::Reset()
{
	m_pGrid.lock()->ResetGridLocation();
	m_pTexture.lock()->SetTexture(m_InActiveTex);
	auto pos = m_pGrid.lock()->CalcGridPos();
	m_pTexture.lock()->SetPosition(pos + m_Offset);
	m_LockUpDir = true;
	m_MoveTimer = 0;
}

CoilyMoveComponent::CoilyMoveComponent(std::weak_ptr<GameObject> parent, float moveSpeed, const glm::vec3& offset,
                                       const glm::vec3& activeOffset,std::weak_ptr<GameObject> qbert, const std::string& inActiveTex, const std::string& activeTex, bool isControlled)
	: BaseComponent(parent)
	, m_MoveSpeed(moveSpeed)
	, m_Offset(offset)
	, m_MoveTimer(0)
	, m_ActiveTex(activeTex)
	, m_InActiveTex(inActiveTex)
    , m_OffsetActive(activeOffset)
	, m_IsControlled(isControlled)
	, m_Moved(false)
{
	m_NeedsUpdate=true;

	m_pTexture = parent.lock()->GetComponent<TextureComponent>();
	m_pGrid = parent.lock()->GetComponent<GridComponent>();
	m_pTarget = qbert.lock()->GetComponent<GridComponent>();
	m_pTextureTarget = qbert.lock()->GetComponent<TextureComponent>();

	m_Dirs.push_back({ 1,1 });
	m_Dirs.push_back({ 0,1 });
	m_Dirs.push_back({ 0,-1 });
	m_Dirs.push_back({ -1,-1 });
}


void CoilyMoveComponent::Move(float dt)
{
	if(m_Moved)
	{
		auto target = m_pTarget.lock()->GetGridLocation();
		auto loc = m_pGrid.lock()->GetGridLocation();
		if (target == loc)
		{
			auto temp = m_pTarget.lock()->GridTaken();
			m_pTextureTarget.lock()->SetPosition(temp + m_Offset);
		}
		m_Moved = false;
	}
	if (m_IsControlled && !m_LockUpDir)
		return;
	m_MoveTimer += dt;
	if(m_MoveTimer>=1.f/m_MoveSpeed)
	{
		if(m_LockUpDir)
		{
			glm::ivec2 dir;
			if (rand() % 2 == 0)
				dir = { 0,1 };
			else
				dir = { 1,1};
			if (m_pGrid.lock()->CheckForDanger(dir))
			{
				m_LockUpDir = !m_LockUpDir;
				m_pTexture.lock()->SetTexture(m_ActiveTex);
				auto pos = m_pGrid.lock()->UpdatePos(glm::ivec2{ 0,0 });
				m_pTexture.lock()->SetPosition(pos + m_OffsetActive);
				Move(0);
				return;
			}
			else
			{

				auto pos = m_pGrid.lock()->UpdatePos(dir);
				m_pTexture.lock()->SetPosition(pos + m_Offset);
			}
		}
		else
		{
			auto target =m_pTarget.lock()->GetGridLocation();
			auto loc =m_pGrid.lock()->GetGridLocation();
			glm::ivec2 dir;
			auto diff = target-loc;
	
			std::vector<int> costs;
			int currentCost=1000;
			int currentCostId=0;
			for (size_t i = 0; i < m_Dirs.size(); ++i)
			{
				auto costSplit = abs(target - (loc+m_Dirs[i]));
				auto cost = costSplit.x+costSplit.y;
				if (cost < currentCost)
				{
					currentCostId =int( i);
					currentCost = cost;
				}
					
				costs.push_back(cost);
			}

			
			while (m_pGrid.lock()->CheckForDanger(m_Dirs[currentCostId]))
			{
				currentCost = 1000;
				costs[currentCostId] = 1000;
				for (size_t i{};i<costs.size(); i++)
				{
					if (costs[i] < currentCost)
					{
						currentCost = costs[i];
						currentCostId = int(i);
					}

				}
				
			}
			dir = m_Dirs[currentCostId];
			if (diff.x-dir.x==0&& diff.y - dir.y == 0)
			{
				auto temp =m_pTarget.lock()->GridTaken();
				m_pTextureTarget.lock()->SetPosition(temp + m_Offset);
			}
			auto pos = m_pGrid.lock()->UpdatePos(dir);
			m_pTexture.lock()->SetPosition(pos + m_OffsetActive);
		}
		m_MoveTimer -= 1.f / m_MoveSpeed;
	}
}