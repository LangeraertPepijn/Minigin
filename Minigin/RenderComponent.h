#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
namespace dae
{
	class RenderComponent final :public BaseComponent
	{
	public:

		RenderComponent(std::weak_ptr<GameObject> parent);				// Constructor
		virtual ~RenderComponent() = default;				// Destructor

		// -------------------------
		// Copy/move constructors and assignment operators
		// -------------------------    
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		//-------------------------------------------------
		// Member functions						
		//-------------------------------------------------

		virtual void Update(float ) override;
		void Render() const override ;
	

	private:
		//-------------------------------------------------
		// Private member functions								
		//-------------------------------------------------


		//-------------------------------------------------
		// Datamembers								
		//-------------------------------------------------;
	};
}

