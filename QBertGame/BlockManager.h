#pragma once
#include <Singleton.h>
#include "map"

class TextureComponent;

class BlockManager final : public Singleton<BlockManager>
{
public:
	void AddBlock(int index,std::shared_ptr<TextureComponent> block);
	void ChangeBlock(int index, const std::string& newTex);
private:
	friend class Singleton<BlockManager>;
	BlockManager() = default;
	std::map<int,std::shared_ptr<TextureComponent>> m_Blocks;
};

