#pragma once
#include "HudBaseComponent.h"
namespace dae
{

	class HudRenderComponent :public HudBaseComponent
	{
	public:
		HudRenderComponent(std::weak_ptr<HudObject> parent);				// Constructor
		virtual ~HudRenderComponent() = default;				// Destructor

		// -------------------------
		// Copy/move constructors and assignment operators
		// -------------------------    
		HudRenderComponent(const HudRenderComponent& other) = delete;
		HudRenderComponent(HudRenderComponent&& other) = delete;
		HudRenderComponent& operator=(const HudRenderComponent& other) = delete;
		HudRenderComponent& operator=(HudRenderComponent&& other) = delete;

		//-------------------------------------------------
		// Member functions						
		//-------------------------------------------------

		virtual void Update(float) override;
		void Render() const override;
	private:
	};

}
