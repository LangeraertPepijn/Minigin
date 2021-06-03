#pragma once
#include "rapidjson.h"
#include"LevelInfo.h"

class JsonLevelReader
{
public:
	JsonLevelReader(const std::string& file);
	void ReadFile(LevelInfo& game) const;
private:
	std::string m_File;
};

