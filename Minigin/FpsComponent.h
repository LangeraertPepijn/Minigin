#pragma once
#include "BaseComponent.h"
#include <chrono>
#include"TextComponent.h"
namespace dae
{

    class FpsComponent :public BaseComponent
    {
	public:

		virtual void Update(float deltaTime)override;
		//virtual void Render()  override;
		int GetFps();

		FpsComponent(std::weak_ptr<GameObject> parent);
		virtual ~FpsComponent() = default;
		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) = delete;
		FpsComponent& operator=(const FpsComponent & other) = delete;
		FpsComponent& operator=(FpsComponent && other) = delete;
	private:

		int m_FPS;
		int m_Frames;
		float m_SecInterval{1.f};
		float m_AccumulatedTime;
		std::shared_ptr<TextComponent> m_pTextComponent;

    };


}