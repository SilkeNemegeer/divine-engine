#pragma once
#include "InputComponent.h"
class Player1InputComponent : divengine::InputComponent //Process input for player 1
{
public:
	enum Actions
	{
		left, right, jump
	};

private:
	Actions m_CurrentAction;
};

