#pragma once
namespace dae
{
	class HudObject;

	class HudBaseComponent
	{

	public:
		HudBaseComponent(std::weak_ptr<HudObject> Parent);				// Constructor
		virtual ~HudBaseComponent() = default;				// Destructor

		// -------------------------
		// Copy/move constructors and assignment operators
		// -------------------------    
		HudBaseComponent(const HudBaseComponent& other) = delete;
		HudBaseComponent(HudBaseComponent&& other) = delete;
		HudBaseComponent& operator=(const HudBaseComponent& other) = delete;
		HudBaseComponent& operator=(HudBaseComponent&& other) = delete;

		//-------------------------------------------------
		// Member functions						
		//-------------------------------------------------
		bool m_NeedsUpdate;
		bool m_NeedsRender;
		virtual void Update(float) = 0;
		virtual void Render()const;
	protected:
		std::weak_ptr<HudObject> m_pParent;
		void SetParent(std::weak_ptr<HudObject> parent);

	private:
		//-------------------------------------------------
		// Private member functions								
		//-------------------------------------------------

		//-------------------------------------------------
		// Datamembers								
		//-------------------------------------------------


	};

}
