#pragma once
#include <iostream>
#include "GameObject.h"

namespace divengine
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(GameObject* pObject) = 0;
		virtual void Undo() = 0;
	};
}