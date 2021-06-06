#pragma once
#include "Command.h"
class QBertMoveComponent;
class CoilyMoveComponent;
class TextureComponent;
class GridComponent;
class TransformComponent;


class MoveCoily : public Command
{

public:
	MoveCoily(std::shared_ptr<GameObject>coily ,const glm::ivec3& step);
	virtual ~MoveCoily();
	virtual void Execute()override;

private:
	std::shared_ptr<GridComponent> m_pCoilyGrid;
	std::shared_ptr<CoilyMoveComponent> m_pCoilyMoveComp;
	glm::ivec3 m_Step={0,0,0};
};


class MoveRightDown : public Command
{

	public:
		MoveRightDown(std::shared_ptr<GameObject> qbert);
		virtual ~MoveRightDown();
		virtual void Execute()override;

	private:
		std::shared_ptr<TextureComponent> m_Qbert;
		std::shared_ptr<GridComponent> m_QbertGrid;
		std::shared_ptr<QBertMoveComponent> m_QbertMove;
		glm::ivec3 m_Step{1,1,0};
	
};

class MoveLeftDown : public Command
{

public:
	MoveLeftDown(std::shared_ptr<GameObject> qbert);
	virtual ~MoveLeftDown();
	virtual void Execute()override;

private:
	std::shared_ptr<TextureComponent> m_Qbert;
	std::shared_ptr<GridComponent> m_QbertGrid;
	std::shared_ptr<QBertMoveComponent> m_QbertMove;
	glm::ivec3 m_Step{ 0,1,0 };
};

class MoveRightUp : public Command
{

public:
	MoveRightUp(std::shared_ptr<GameObject> qbert);
	virtual ~MoveRightUp();
	virtual void Execute()override;

private:
	std::shared_ptr<TextureComponent> m_Qbert;
	std::shared_ptr<GridComponent> m_QbertGrid;
	std::shared_ptr<QBertMoveComponent> m_QbertMove;
	glm::ivec3 m_Step{ 0,-1,0 };

};
class MoveLeftUp : public Command
{

public:
	MoveLeftUp(std::shared_ptr<GameObject> qbert);
	virtual ~MoveLeftUp();
	virtual void Execute() override;

private:
	std::shared_ptr<TextureComponent> m_Qbert;
	std::shared_ptr<GridComponent> m_QbertGrid;
	std::shared_ptr<QBertMoveComponent> m_QbertMove;
	glm::ivec3 m_Step{ -1,-1,0 };
};

