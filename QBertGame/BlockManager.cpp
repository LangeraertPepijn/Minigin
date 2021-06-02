#include "QBertPCH.h"
#include "BlockManager.h"
#include "GameObject.h"
#include "TextureComponent.h"

void BlockManager::AddBlock(int index,std::shared_ptr<TextureComponent>block)
{
	m_Blocks.insert(std::pair<int,std::shared_ptr<TextureComponent>>(index, block));
}

void BlockManager::ChangeBlock(int index, const std::string& newTex)
{
	m_Blocks[index]->SetTexture(newTex);
}
