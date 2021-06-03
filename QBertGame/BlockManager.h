#pragma once
#include <Singleton.h>
#include "map"

class TextureComponent;

class BlockManager final : public Singleton<BlockManager>
{
public:
	void AddBlock(int index,std::shared_ptr<TextureComponent> block);
	void ChangeBlock(int index);
	void SetCanRevert(bool canRevert);
	void SetActiveTex(const std::string& newTex);
	void SetInActiveTex(const std::string& newTex);
private:
	friend class Singleton<BlockManager>;
	BlockManager() = default;
	std::map<int,std::shared_ptr<TextureComponent>> m_Blocks;
	std::map<int,bool> m_BlockChanged;
	bool m_CanRevert;
	std::string m_TexActive;
	std::string m_TexInActive;
};

