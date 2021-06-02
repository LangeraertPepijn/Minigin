#include "MiniginPCH.h"
#include "HudManager.h"

std::shared_ptr<HudObject> HudManager::CreateHud()
{
	const auto hud = std::shared_ptr<HudObject>(std::make_shared< HudObject>());
	m_Huds.push_back(hud);
	return hud;
}

void HudManager::Update(float deltaTime)
{
	for (const auto & hud: m_Huds)
	{
		hud->Update(deltaTime);
	}
}

void HudManager::Render()
{
	for (const auto& hud : m_Huds)
	{
		hud->Render();
	}
}
