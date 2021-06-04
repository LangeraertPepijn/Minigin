#pragma once
#include "Command.h"

class TextureComponent;
class GridComponent;
class TransformComponent;



class Move : public Command
{

public:
	Move(std::shared_ptr<GameObject> qbert, glm::vec3 posFix);
	virtual ~Move();
	virtual void Execute()override;

private:
	std::shared_ptr<TextureComponent> m_Qbert;
	std::shared_ptr<GridComponent> m_QbertGrid;
	glm::ivec3 m_Step={0,0,0};
	glm::vec3 m_PosFix;
};


class MoveRightDown : public Command
{

	public:
		MoveRightDown(std::shared_ptr<GameObject> qbert, glm::vec3 posFix);
		virtual ~MoveRightDown();
		virtual void Execute()override;

	private:
		std::shared_ptr<TextureComponent> m_Qbert;
		std::shared_ptr<GridComponent> m_QbertGrid;
		glm::ivec3 m_Step{1,1,0};
		glm::vec3 m_PosFix;
};

class MoveLeftDown : public Command
{

public:
	MoveLeftDown(std::shared_ptr<GameObject> qbert, glm::vec3 posFix);
	virtual ~MoveLeftDown();
	virtual void Execute()override;

private:
	std::shared_ptr<TextureComponent> m_Qbert;
	std::shared_ptr<GridComponent> m_QbertGrid;
	glm::ivec3 m_Step{ 0,1,0 };
	glm::vec3 m_PosFix;
};

class MoveRightUp : public Command
{

public:
	MoveRightUp(std::shared_ptr<GameObject> qbert, glm::vec3 posFix);
	virtual ~MoveRightUp();
	virtual void Execute()override;

private:
	std::shared_ptr<TextureComponent> m_Qbert;
	std::shared_ptr<GridComponent> m_QbertGrid;
	glm::ivec3 m_Step{ 0,-1,0 };
	glm::vec3 m_PosFix;
};
class MoveLeftUp : public Command
{

public:
	MoveLeftUp(std::shared_ptr<GameObject> qbert, glm::vec3 posFix);
	virtual ~MoveLeftUp();
	virtual void Execute() override;

private:
	std::shared_ptr<TextureComponent> m_Qbert;
	std::shared_ptr<GridComponent> m_QbertGrid;
	glm::ivec3 m_Step{ -1,-1,0 };
	glm::vec3 m_PosFix;
};
