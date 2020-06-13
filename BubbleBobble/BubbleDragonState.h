#pragma once
#include "GameObject.h"
#include <iostream>

class BubbleDragonState
{
public:
	virtual ~BubbleDragonState() {};
	virtual void Update(divengine::GameObject* pObject) {};
};

class MovingLeftState
{
public:
	virtual ~MovingLeftState() {};

	//The state can change because of input as well

	virtual void Update(divengine::GameObject* pObject) 
	{
		//Check here if you need to go to another state or if you stay in the same state

		std::cout << "Moving left\n"; 
	}; 
};



