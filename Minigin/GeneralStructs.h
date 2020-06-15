#pragma once
#include <string>
struct SDL_Window;
namespace divengine
{
	struct GameSettings
	{
		GameSettings()
			:Width(640),
			Height(480),
			Title("Programming 4 assignment"),
			Window(nullptr)
		{
		}
		
		int Width;
		int Height;
		std::string Title;
		SDL_Window* Window;
	};
}