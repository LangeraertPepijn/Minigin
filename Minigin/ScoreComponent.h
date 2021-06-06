#pragma once
#include "BaseComponent.h"



class HudTextComponent;
class SubjectComponent;
class ScoreComponent :public BaseComponent
{
public:

	virtual void Update(float )override;
	//virtual void Render()  override;

	int GetScore()const;
	void SetParent(std::weak_ptr<GameObject> parent);
	void SetScore(int score);
	void IncreaseScore(int diff);
	void DecreaseScore(int diff);
	ScoreComponent(std::weak_ptr<GameObject> parent);
	virtual ~ScoreComponent() = default;
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) = delete;
private:

	int m_Score{ 0 };
	std::shared_ptr<SubjectComponent> m_Subject;

};


