#include "QBertPCH.h"
#include "JsonLevelReader.h"
#include "LevelInfo.h"
#include "fstream"
#include "nlohmann/json.hpp"
JsonLevelReader::JsonLevelReader(const std::string& file)
	: m_File(file)
{
}

void JsonLevelReader::ReadFile(std::vector<LevelInfo>& levels) const
{
	
	std::ifstream fStream{m_File} ;
	nlohmann::json json;
	fStream >> json;
	for (auto jLevel : json["Levels"])
	{
		LevelInfo level;
		level.levelNo =  jLevel["LevelNo"] ;
		level.gridSize = { jLevel["GridSize"][0], jLevel["GridSize"][1] };
		level.offset = { jLevel["Offset"][0], jLevel["Offset"][1] };
		level.blockSize = { jLevel["BlockSize"][0], jLevel["BlockSize"][1] };
		level.activeTex =  jLevel["BlockTexActive"] ;
		level.InBetweenTex = jLevel["BlockTexInBetween"];
		level.inActiveTex = jLevel["BlockTexInActive"];
		level.canRevert = jLevel["CanRevert"];
		level.needsDoubleTouch = jLevel["NeedsDoubleTouch"];
		level.posFix = { jLevel["PosFix"][0],jLevel["PosFix"][1],jLevel["PosFix"][2] };
		levels.push_back(level);

	}
	



}
