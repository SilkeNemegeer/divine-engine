#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Time.h"
#include "RigidbodyComponent.h"
#include "ColliderComponent.h"
#include "BoxColliderComponent.h"
#include "CircleColliderComponent.h"
#include "DebugRenderer.h"

using namespace std;
using namespace std::chrono;


void divengine::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_GameSettings.m_Height = 480;
	m_GameSettings.m_Width = 640;

	//m_GameSettings.m_Height = 1080;
	//m_GameSettings.m_Width = 1920;

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_GameSettings.m_Width,
		m_GameSettings.m_Height,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}


	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void divengine::Minigin::LoadGame() const
{
	//Load levels & components
}

void divengine::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void divengine::Minigin::Run()
{
	//Initialize();

	// tell the resource manager where he can find the game data
	//ResourceManager::GetInstance().Init("../Data/");

	//LoadGame();
	SceneManager::GetInstance().Initialize();

#ifdef _DEBUG
	DebugRenderer::EnableDebugRendering(true);
#endif // DEBUG

	try
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		float timeSinceLastFixedUpdate = 0.f;	//update time using fixed timestep (MsPerUpdate = timestep) (lag = totalTime)

		Time::GetInstance().Start();
		while (doContinue)
		{
			//Time::GetInstance().StartFrame();
		
			Time::GetInstance().Update();
			timeSinceLastFixedUpdate += Time::GetInstance().GetDeltaTime();

			doContinue = input.ProcessInput();
			while (timeSinceLastFixedUpdate >= Time::MS_PER_UPDATE)
			{
				//fixed update triggered
				sceneManager.FixedUpdate();
				timeSinceLastFixedUpdate -= Time::MS_PER_UPDATE;
			}
			sceneManager.Update();
			renderer.Render(); //Will always render
			//Time::GetInstance().EndFrame();
		}
	}
	catch(const std::exception& exception)
	{
		std::cout << exception.what() << "\n";
	}

	//Cleanup();
}

divengine::Minigin::~Minigin()
{
	Cleanup();
}

divengine::Minigin::GameSettings::GameSettings()
	:m_Height{}
	,m_Width{}
{
}
