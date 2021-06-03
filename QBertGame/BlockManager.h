#pragma once
#include <Singleton.h>
#include "map"

class TextureComponent;

class BlockManager final : public Singleton<BlockManager>
{
public:
	void AddBlock(int index,std::shared_ptr<TextureComponent> block);
	bool ChangeBlock(int index);
	void SetCanRevert(bool canRevert);
	void SetNeedsDoubleTouch(bool needsDoubleTouch);
	void SetActiveTex(const std::string& newTex);
	void SetInActiveTex(const std::string& newTex);
	void SetInBetweenTex(const std::string& newTex);
	void LinkLevelDone(bool& levelDone);
	void Clear();
private:
	friend class Singleton<BlockManager>;
	BlockManager() = default;
	std::map<int,std::shared_ptr<TextureComponent>> m_Blocks;
	std::map<int,int> m_BlockChanged;
	bool m_CanRevert=false;
	bool m_NeedsDoubleTouch=false;
	std::string m_TexActive;
	std::string m_TexInBetween;
	std::string m_TexInActive;
	bool* m_LevelDone;
};



