#include "QBertPCH.h"
#pragma once
struct LevelInfo
{
	glm::vec2 offset = { 288,40 };
	glm::vec2 blockSize = { 64,45 };
	glm::vec3 posFix{ 20, -10,0 };
	glm::ivec2 gridSize{ 6,6 };
	std::string activeTex = "Cube2.png";
	std::string inActiveTex = "Cube1.png";
	int levelNo = -1;
	bool canRevert = false;
};