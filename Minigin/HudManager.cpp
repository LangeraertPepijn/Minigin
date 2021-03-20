#include "MiniginPCH.h"
#include "HudManager.h"

std::shared_ptr<dae::HudObject> dae::HudManager::CreateHud()
{
	const auto hud = std::shared_ptr<HudObject>(std::make_shared< HudObject>());
	m_Huds.push_back(hud);
	return hud;
}

void dae::HudManager::Update(float deltaTime)
{
	for (const auto & hud: m_Huds)
	{
		hud->Update(deltaTime);
	}
}

void dae::HudManager::Render()
{
	for (const auto& hud : m_Huds)
	{
		hud->Render();
	}
}
