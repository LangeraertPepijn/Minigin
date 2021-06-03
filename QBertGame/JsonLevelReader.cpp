#include "QBertPCH.h"
#include "JsonLevelReader.h"
#include "filereadstream.h"
#include "document.h"
#include "LevelInfo.h"

JsonLevelReader::JsonLevelReader(const std::string& file)
	: m_File(file)
{
}

void JsonLevelReader::ReadFile(std::vector<LevelInfo>& levels) const
{
	
	FILE* pIFile = nullptr;
	fopen_s(&pIFile, m_File.c_str(), "rb");
	if (pIFile != nullptr)
	{
		fseek(pIFile, 0, SEEK_END);
		size_t size = ftell(pIFile);
		fseek(pIFile, 0, SEEK_SET);

		char* buffer = new char[size];

		rapidjson::FileReadStream stream(pIFile, buffer, size);
		rapidjson::Document doc;
		doc.ParseStream(stream);
	
		const rapidjson::Value& fileLevels = doc["Levels"];
		for (auto layerIt = fileLevels.Begin();  layerIt != fileLevels.End(); ++layerIt)
		{
			const rapidjson::Value& layer = *layerIt;
			const rapidjson::Value& offset = layer["Offset"];
			const rapidjson::Value& levelNo = layer["LevelNo"];
			const rapidjson::Value& blockSize = layer["BlockSize"];
			const rapidjson::Value& posfix = layer["PosFix"];
			const rapidjson::Value& gridSize = layer["GridSize"];
			const rapidjson::Value& blockTexActive = layer["BlockTexActive"];
			const rapidjson::Value& blockTexInActive = layer["BlockTexInActive"];
			const rapidjson::Value& canRevert = layer["CanRevert"];

			LevelInfo level;
			level.levelNo = { levelNo.GetInt() };
			level.gridSize = { gridSize[0].GetInt(),gridSize[1].GetInt() };
			level.offset = { offset[0].GetInt(),offset[1].GetInt() };
			level.blockSize = { blockSize[0].GetInt(),blockSize[1].GetInt() };
			level.activeTex = blockTexActive.GetString();
			level.canRevert = canRevert.GetBool();
			level.inActiveTex = blockTexInActive.GetString();
			level.posFix = { posfix[0].GetInt(),posfix[1].GetInt(),posfix[2].GetInt() };
			levels.push_back(level);

		}
        fclose(pIFile);
	}

}
