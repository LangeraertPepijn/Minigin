#pragma once
#include"LevelInfo.h"

class JsonLevelReader final
{
public:
	JsonLevelReader(const std::string& file);
	void ReadFile(std::vector<LevelInfo>& levels) const;
private:
	std::string m_File;
};

