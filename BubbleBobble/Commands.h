#pragma once
#include "Command.h"
#include "InputManager.h"
using namespace divengine;

class JumpCommand : public Command
{
public:
	JumpCommand() {}; //Can pass extra values here if needed
	void Execute(GameObject* pObject) override 
	{
		if (pObject)
		{
			//if (pObject->GetTag() == "BubbleDragon");
		}
		Jump(); 
	
	}
	void Undo() override {}
private:
	void Jump()
	{
		//Check tag to see if it is a character -> make it jump if so
		//InputManager::GetInstance().SetVibration(0, 0);
		std::cout << "Jump called.\n";
	}
};