#pragma once
#include <iostream>

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
class DuckCommand : public Command
{
public:
	DuckCommand();
	virtual ~DuckCommand();
	virtual void Execute()override { std::cout << "Duck..." << std::endl; }

private:

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



