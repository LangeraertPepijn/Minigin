#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)
namespace dae
{
	class TransformComponent final :public BaseComponent
	{
	public:
		TransformComponent(std::weak_ptr<GameObject> parent, const glm::vec3& pos);				// Constructor
		virtual ~TransformComponent() = default;				// Destructor

		// -------------------------
		// Copy/move constructors and assignment operators
		// -------------------------    
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		//-------------------------------------------------
		// Member functions						
		//-------------------------------------------------
		void SetTransform(const glm::vec3& newPos);
		const glm::vec3& GetTransform()const;

		void AddTransform(const glm::vec3& vecToAdd);
		void MulTransform(const glm::vec3& vecToMul);
		void MulTransformScalar(const float scalar);
		virtual void Update(float ) override;

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

