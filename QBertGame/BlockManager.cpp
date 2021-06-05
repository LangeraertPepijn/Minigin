#include "QBertPCH.h"
#include "BlockManager.h"
#include "GameObject.h"
#include "TextureComponent.h"

void BlockManager::AddBlock(int index,std::shared_ptr<TextureComponent>block)
{
	m_Blocks.insert(std::pair<int,std::shared_ptr<TextureComponent>>(index, block));
	m_BlockChanged.insert(std::pair<int,bool>(index, 0));
}

bool BlockManager::ChangeBlock(int index)
{
	auto temp = m_Blocks.find(index);
	if (temp != m_Blocks.end())
	{
		if (!(m_CanRevert && m_BlockChanged[index] % 2 == 1))
		{
			
			
			if (!m_NeedsDoubleTouch)
			{

				if (m_BlockChanged[index] == 0)
				{
					m_BlockChanged[index]++;
					m_Blocks[index]->SetTexture(m_TexActive);
					++m_BlocksChanged;
					if (m_BlocksChanged == m_Blocks.size())
						*m_LevelDone = true;
					return true;
				}
			}
			else if(m_BlockChanged[index] == 0)
			{
				m_BlockChanged[index]++;
				m_Blocks[index]->SetTexture(m_TexInBetween);
				
				return true;
				
			}
			else
			{
				if (m_BlockChanged[index] == 1)
				{
					m_BlockChanged[index]++;
					m_Blocks[index]->SetTexture(m_TexActive);
					m_BlocksChanged++;
					if (m_BlocksChanged == m_Blocks.size())
						*m_LevelDone = true;
					return true;
				}
			}

		}
		else
		{
			m_Blocks[index]->SetTexture(m_TexInActive);
			if (m_BlockChanged[index] == 1)
				--m_BlocksChanged;
			m_BlockChanged[index] = m_BlockChanged[index]--;
		}


	}
	return false;
}

void BlockManager::SetCanRevert(bool canRevert)
{
	m_CanRevert = canRevert;
}

void BlockManager::SetNeedsDoubleTouch(bool needsDoubleTouch)
{
	m_NeedsDoubleTouch = needsDoubleTouch;
}

void BlockManager::SetActiveTex(const std::string& newTex)
{
	m_TexActive = newTex;
}

void BlockManager::SetInActiveTex(const std::string& newTex)
{
	m_TexInActive = newTex;
}

void BlockManager::SetInBetweenTex(const std::string& newTex)
{
	m_TexInBetween = newTex;
}

void BlockManager::LinkLevelDone(bool& levelDone)
{
	m_LevelDone = &levelDone;
}

void BlockManager::Clear()
{
	m_BlockChanged.clear();
	m_Blocks.clear();
	m_BlocksChanged = 0;
}
