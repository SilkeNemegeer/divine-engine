#pragma once
struct SDL_Window;
#include "GeneralStructs.h"

namespace divengine
{
	class Minigin
	{
	public:
		void Initialize();
		void Cleanup();
		void Run();
		static void Quit();
		Minigin();
		~Minigin();
	
	private:
		static bool m_IsRunning;
	};
}

//MsPerFrame 16 for 60 fps, 33 for 30 fps