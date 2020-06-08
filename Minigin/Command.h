#pragma once
#include <iostream>
#include "GameObject.h"

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
	virtual void Undo() = 0;
};

class JumpCommand : public Command
{
public:
	void Execute() override { Jump(); }
	void Undo() override {}
private:
	void Jump()
	{
		std::cout << "Jump called.\n";
	}
};

