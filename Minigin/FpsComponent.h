#pragma once
#include "BaseComponent.h"
#include <chrono>
namespace dae
{

    class FpsComponent :public BaseComponent
    {
	public:
		virtual void Update(float deltaTime)override;
		//virtual void Render()  override;
		int GetFps();

		FpsComponent(std::shared_ptr<GameObject> parent);
		virtual ~FpsComponent() = default;
		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) = delete;
		FpsComponent& operator=(const FpsComponent & other) = delete;
		FpsComponent& operator=(FpsComponent && other) = delete;
	private:

		int m_FPS;
		int m_Frames;
		float m_AccumulatedTime;


    };


}