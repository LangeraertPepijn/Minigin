#pragma once
#include "HudBaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)
namespace dae
{
	class HudTransformComponent final :public HudBaseComponent
	{
	public:
		HudTransformComponent(std::weak_ptr<HudObject> parent, const glm::vec3& pos);				// Constructor
		virtual ~HudTransformComponent() = default;				// Destructor

		// -------------------------
		// Copy/move constructors and assignment operators
		// -------------------------    
		HudTransformComponent(const HudTransformComponent& other) = delete;
		HudTransformComponent(HudTransformComponent&& other) = delete;
		HudTransformComponent& operator=(const HudTransformComponent& other) = delete;
		HudTransformComponent& operator=(HudTransformComponent&& other) = delete;

		//-------------------------------------------------
		// Member functions						
		//-------------------------------------------------
		void SetTransform(const glm::vec3& newPos);
		const glm::vec3& GetTransform()const;

		void AddTransform(const glm::vec3& vecToAdd);
		void MulTransform(const glm::vec3& vecToMul);
		void MulTransformScalar(const float scalar);
		virtual void Update(float) override;

	private:
		//-------------------------------------------------
		// Private member functions								
		//-------------------------------------------------


		//-------------------------------------------------
		// Datamembers								
		//-------------------------------------------------
		glm::vec3 m_Pos;
	};
}

