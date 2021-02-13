#pragma once
namespace dae
{
	class SceneObject
	{
	public:
		virtual void Update(float deltaTime)=0;
		virtual void Render()=0 ;

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;

	};
}
