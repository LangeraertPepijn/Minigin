#include "QBertPCH.h"
#include "CoilyMoveComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "ServiceLocator.h"

void CoilyMoveComponent::Update(float dt)
{
	if (!m_CanMove)
	{
		m_MoveTimer += dt;
		if (m_MoveTimer >= 1.f / m_MoveSpeed)
		{
			m_CanMove = true;
			m_MoveTimer = 0;
		}
	}
	Move(dt);
}

void CoilyMoveComponent::SetParent(std::weak_ptr<GameObject> parent)
{
	m_pParent = parent;
	m_pTexture = parent.lock()->GetComponent<TextureComponent>();
}

bool CoilyMoveComponent::CanPlayerControll()
{
	return !m_LockUpDir;
}

bool CoilyMoveComponent::CanMove()
{
	return m_CanMove;
}

void CoilyMoveComponent::SetMoved(bool moved)
{
	m_Moved = moved;
	m_CanMove = false;
}

void CoilyMoveComponent::Move(const glm::vec3& move)
{
	if (m_pTexture.use_count())
		m_pTexture->SetPosition(move + m_OffsetActive);
	m_Moved = true;
}


void CoilyMoveComponent::Reset()
{
		m_pGrid->ResetGridLocation();
		m_pTexture->SetTexture(m_InActiveTex);
		auto pos = m_pGrid->CalcGridPos();
		m_pTexture->SetPosition(pos + m_Offset);
		m_LockUpDir = true;
		m_MoveTimer = 0;
	
}

CoilyMoveComponent::CoilyMoveComponent(std::weak_ptr<GameObject> parent, float moveSpeed, const glm::vec3& offset,
	const glm::vec3& activeOffset,std::shared_ptr<GameObject> qbert1, std::shared_ptr<GameObject> qbert2,
	const std::string& inActiveTex, const std::string& activeTex, bool isControlled, unsigned short soundId)
	: BaseComponent(parent)
	, m_MoveSpeed(moveSpeed)
	, m_Offset(offset)
	, m_MoveTimer(0)
	, m_ActiveTex(activeTex)
	, m_InActiveTex(inActiveTex)
    , m_OffsetActive(activeOffset)
	, m_IsControlled(isControlled)
	, m_Moved(false)
	, m_LockUpDir(true)
	, m_SoundId(soundId)
{
	m_NeedsUpdate=true;

	m_pTexture = parent.lock()->GetComponent<TextureComponent>();
	m_pGrid = parent.lock()->GetComponent<GridComponent>();
	if (qbert1.use_count())
	{
		m_pTargetQ1 = qbert1->GetComponent<GridComponent>();
		m_pTextureTargetQ1 = qbert1->GetComponent<TextureComponent>();
	}
	if (qbert2.use_count())
	{
		m_pTargetQ2 = qbert2->GetComponent<GridComponent>();
		m_pTextureTargetQ2 = qbert2->GetComponent<TextureComponent>();
	}

	m_Dirs.push_back({ 1,1 });
	m_Dirs.push_back({ 0,1 });
	m_Dirs.push_back({ 0,-1 });
	m_Dirs.push_back({ -1,-1 });
}


void CoilyMoveComponent::Move(float dt)
{
	m_MoveTimer += dt;
	
	if(m_Moved)
	{
		auto target = m_pTargetQ1->GetGridLocation();
		auto loc = m_pGrid->GetGridLocation();
		
		if (target == loc)
		{
			auto temp = m_pTargetQ1->GridTaken();
			m_pTextureTargetQ1->SetPosition(temp + m_Offset);
		}
		m_Moved = false;
	}
	if (m_IsControlled && !m_LockUpDir)
		return;
	if (m_MoveTimer >= 1.f / m_MoveSpeed)
	{

		if (m_LockUpDir)
		{
			glm::ivec2 dir;
			if (rand() % 2 == 0)
				dir = { 0,1 };
			else
				dir = { 1,1 };
			if (m_pGrid->CheckForDanger(dir))
			{
				m_LockUpDir = !m_LockUpDir;
				m_pTexture->SetTexture(m_ActiveTex);
				auto pos = m_pGrid->UpdatePos(glm::ivec2{ 0,0 });
				m_pTexture->SetPosition(pos + m_OffsetActive);
				Move(0);
				return;
			}
			else
			{

				auto pos = m_pGrid->UpdatePos(dir);
				m_pTexture->SetPosition(pos + m_Offset);
				const auto soundSystem = ServiceLocator::GetSoundSystem();
				if (soundSystem)
				{
					soundSystem->Play(m_SoundId, 15.f);
				}
			}
		}
		else
		{

			auto target = m_pTargetQ1->GetGridLocation();
			auto loc = m_pGrid->GetGridLocation();
			glm::ivec2 dir;
			auto diff = target - loc;
			if (m_pTargetQ2.get())
			{

				auto target2 = m_pTargetQ2->GetGridLocation();
				auto diff2 = target2 - loc;
				if (abs(diff.x) + abs(diff.y) > abs(diff2.x) + abs(diff2.y))
				{
					target = target2;
					diff = diff2;
				}
			}
			std::vector<int> costs;
			int currentCost = 1000;
			int currentCostId = 0;
			for (size_t i = 0; i < m_Dirs.size(); ++i)
			{
				auto costSplit = abs(target - (loc + m_Dirs[i]));
				auto cost = costSplit.x + costSplit.y;
				if (cost < currentCost)
				{
					currentCostId = int(i);
					currentCost = cost;
				}

				costs.push_back(cost);
			}


			while (m_pGrid->CheckForDanger(m_Dirs[currentCostId]))
			{
				currentCost = 1000;
				costs[currentCostId] = 1000;
				for (size_t i{}; i < costs.size(); i++)
				{
					if (costs[i] < currentCost)
					{
						currentCost = costs[i];
						currentCostId = int(i);
					}

				}

			}
			dir = m_Dirs[currentCostId];
			if (diff.x - dir.x == 0 && diff.y - dir.y == 0)
			{
				if (m_pTargetQ2.use_count())
				{
					if (target == m_pTargetQ2->GetGridLocation())
					{
						auto temp = m_pTargetQ2->GridTaken();
						m_pTextureTargetQ2->SetPosition(temp + m_Offset);
					}

				}
				else
				{
					if (m_pTargetQ1.use_count())
					{
						auto temp = m_pTargetQ1->GridTaken();
						m_pTextureTargetQ1->SetPosition(temp + m_Offset);
					}
				}
			}

			auto pos = m_pGrid->UpdatePos(dir);
			m_pTexture->SetPosition(pos + m_OffsetActive);
			const auto soundSystem = ServiceLocator::GetSoundSystem();
			if (soundSystem)
			{
				soundSystem->Play(m_SoundId, 15.f);
			}

		}
		m_MoveTimer -= 1.f / m_MoveSpeed;
	}
}
