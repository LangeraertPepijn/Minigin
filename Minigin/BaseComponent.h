#pragma once
namespace dae
{
class GameObject;

	class BaseComponent
	{


	public:
		BaseComponent();				// Constructor
		BaseComponent(std::shared_ptr<GameObject> Parent);				// Constructor
		virtual ~BaseComponent() = default;				// Destructor

		// -------------------------
		// Copy/move constructors and assignment operators
		// -------------------------    
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		//-------------------------------------------------
		// Member functions						
		//-------------------------------------------------
		bool m_NeedsUpdate;
		bool m_NeedsRender;
		virtual void Update(float deltaTime);
		virtual void Render()const ;
	protected:
		std::shared_ptr<GameObject> m_pParent;
		void SetParent(std::shared_ptr<GameObject> parent);


	private:
		//-------------------------------------------------
		// Private member functions								
		//-------------------------------------------------

		//-------------------------------------------------
		// Datamembers								
		//-------------------------------------------------


	};
}
