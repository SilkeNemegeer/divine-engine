#pragma once
#include <map>

namespace divengine
{
	class Command;

	class InputMap
	{
		InputMap();
		~InputMap() {};
		std::map<int, Command*> m_pCommands;

	};
}