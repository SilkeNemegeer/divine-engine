#pragma once
#include "InputComponent.h"
#include "GameObject.h"
#include <iostream>

class BubbleDragonState
{
public:
	virtual ~BubbleDragonState() {};
	virtual BubbleDragonState* HandleInput(divengine::GameObject* pObject, divengine::InputComponent* input) {};// Is done by command pattern?
	virtual void Update(divengine::GameObject* pObject) {};
};

class MovingLeftState
{
public:
	virtual ~MovingLeftState() {};
	virtual BubbleDragonState* HandleInput(divengine::GameObject* pObject, divengine::InputComponent* input)
	{
		//input->Update();
		return nullptr;
	}
	//The state can change because of input as well

	virtual void Update(divengine::GameObject* pObject) 
	{
		//Check here if you need to go to another state or if you stay in the same state

		std::cout << "Moving left\n"; 
	}; 
};



