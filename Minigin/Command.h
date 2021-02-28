#pragma once
#include <iostream>
#include "GameObject.h"

namespace dae
{
	class TextComponent;
	
}


class Command
{
public:
	Command()=default;
	virtual ~Command()=default;
	virtual void Execute() = 0;
	bool isQuit{};
private:
protected:
};
class JumpCommand: public Command
{
public:
	JumpCommand();
	virtual ~JumpCommand();
	virtual void Execute()override {  }

private:

};
class FireCommand : public Command
{
public:
	FireCommand();
	virtual ~FireCommand();
	virtual void Execute()override { std::cout << "Fire..." << std::endl; }

private:

};
class DieCommand : public Command
{
public:
	DieCommand(std::shared_ptr<dae::GameObject> object);
	virtual ~DieCommand();
	virtual void Execute()override;


private:
	std::shared_ptr<dae::GameObject> m_ObjectThatDies;

};
class FartCommand : public Command
{
public:
	FartCommand();
	virtual ~FartCommand();
	virtual void Execute()override { std::cout << "Fart..." << std::endl; }

private:

};
class QuitCommand : public Command
{
public:
	QuitCommand(bool* quit);
	virtual ~QuitCommand();
	virtual void Execute()override { *m_Quit=true; }

private:
	bool* m_Quit;
};
class DamageCommand : public Command
{
public:
	DamageCommand(std::shared_ptr<dae::GameObject> object,float damage);
	virtual ~DamageCommand();
	virtual void Execute()override;


private:
	std::shared_ptr<dae::GameObject> m_ObjectThatsDamaged;
	float m_Damage;

};



