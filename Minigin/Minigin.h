#pragma once

#pragma warning(push)
#pragma warning(disable : 4201)
#pragma warning(disable : 26812)
#pragma warning(disable : 26495)
#include "glm/glm.hpp"
#pragma warning(pop)
struct SDL_Window;

namespace divengine
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

		struct GameSettings
		{
			GameSettings();
			GameSettings(int screenWidth, int screenHeight):m_Width{screenWidth}, m_Height{screenHeight}{}
			int m_Width;
			int m_Height;
		};
		
	private:
	//	static const int MsPerFrame = 16; //MsPerFrame 16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};	
		GameSettings m_GameSettings;


	};
}