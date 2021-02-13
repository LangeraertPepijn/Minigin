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

		RenderComponent(std::shared_ptr<GameObject> parent, std::shared_ptr<Texture2D> texture);				// Constructor
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

		//virtual void Update(float deltaTime) override;
		void Render() const;
		void SetTexture(const std::string& filename);

	private:
		//-------------------------------------------------
		// Private member functions								
		//-------------------------------------------------


		//-------------------------------------------------
		// Datamembers								
		//-------------------------------------------------
		std::shared_ptr<dae::Texture2D> m_Texture{};
	};
}

