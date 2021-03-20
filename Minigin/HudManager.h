#pragma once
#include "Singleton.h"
#include "HudObject.h"
namespace dae
{
	class HudManager :public Singleton<HudManager>
	{

	public:
		std::shared_ptr<HudObject> CreateHud();

		void Update(float deltaTime);
		void Render();
	private:
		friend class Singleton<HudManager>;
		HudManager() = default;
		std::vector<std::shared_ptr<HudObject>> m_Huds;


	};
};