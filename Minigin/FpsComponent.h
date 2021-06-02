#pragma once
#include "BaseComponent.h"
#include <chrono>
#include"TextComponent.h"


  class FpsComponent final :public BaseComponent
  {
	public:

	virtual void Update(float deltaTime)override;
	//virtual void Render()  override;

	FpsComponent(std::weak_ptr<GameObject> parent);
	virtual ~FpsComponent() = default;
	FpsComponent(const FpsComponent& other) = delete;
	FpsComponent(FpsComponent&& other) = delete;
	FpsComponent& operator=(const FpsComponent & other) = delete;
	FpsComponent& operator=(FpsComponent && other) = delete;
	private:

	float m_SecInterval{1.f};
	float m_AccumulatedTime;
	std::shared_ptr<TextComponent> m_pTextComponent;

  };


