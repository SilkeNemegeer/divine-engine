#include "MiniginPCH.h"
#include "BaseGame.h"

divengine::GameSettings divengine::BaseGame::m_GameSettings = divengine::GameSettings();

divengine::BaseGame::BaseGame()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_GameSettings.Height = 480;
	m_GameSettings.Width = 640;

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_GameSettings.Width,
		m_GameSettings.Height,
		SDL_WINDOW_OPENGL
	);

	m_GameSettings.Window = m_Window;

	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
	m_Engine.Initialize();
}

divengine::BaseGame::~BaseGame()
{
	//m_Engine.Cleanup();

	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void divengine::BaseGame::Run()
{
	Initialize();
	m_Engine.Run();
}

//Fullscreen settings:
//m_Window = SDL_CreateWindow(
//	"Programming 4 assignment",
//	SDL_WINDOWPOS_CENTERED,
//	SDL_WINDOWPOS_CENTERED,
//	m_GameSettings.m_Width,
//	m_GameSettings.m_Height,
//	SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN
//);