#include "MiniginPCH.h"
//#include "Game.h"
//
//#include "MiniginPCH.h"
//#include <chrono>
//#include <thread>
//#include "InputManager.h"
//#include "SceneManager.h"
//#include "Renderer.h"
//#include "ResourceManager.h"
//#include "TextObject.h"
//#include "GameObject.h"
//#include "Scene.h"
//#include "RenderComponent.h"
//#include "TextComponent.h"
//#include "FPSComponent.h"
//#include "TransformComponent.h"
//#include "Time.h"
//
//using namespace std;
//using namespace std::chrono;
//using namespace dae;
//
//void Game::InitializeGame()
//{
//	if (SDL_Init(SDL_INIT_VIDEO) != 0)
//	{
//		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
//	}
//
//	m_Window = SDL_CreateWindow(
//		"Programming 4 assignment",
//		SDL_WINDOWPOS_UNDEFINED,
//		SDL_WINDOWPOS_UNDEFINED,
//		640,
//		480,
//		SDL_WINDOW_OPENGL
//	);
//	if (m_Window == nullptr)
//	{
//		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
//	}
//
//	Renderer::GetInstance().Init(m_Window);
//	SceneManager::GetInstance().Initialize();
//	Initialize();
//}
//
///**
// * Code constructing the scene world starts here
// */
////void Game::LoadGame() const
////{
////	auto& demoScene = SceneManager::GetInstance().CreateScene("Demo");
////
////	//Add background
////	auto go = std::make_shared<GameObject>(Vector3(0.f, 0.f, 0.f));
////	RenderComponent* pRenderComp = new RenderComponent();
////	pRenderComp->SetTexture("background.jpg");
////	go->AddComponent(pRenderComp);
////	demoScene.AddObject(go);
////
////	//Add logo dae
////	go = std::make_shared<GameObject>(Vector3(216, 180, 0));
////	go->AddComponent(new RenderComponent("logo.png"));
////	demoScene.AddObject(go);
////
////	//Add Programming 4 Assignment text
////	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
////	go = std::make_shared<GameObject>(Vector3(80, 20, 0));
////	go->AddComponent(new RenderComponent());
////	go->AddComponent(new TextComponent("Programming 4 Assignment", font));
////	demoScene.AddObject(go);
////
////	//Add fps counter
////	auto FPSCounter = std::make_shared<GameObject>(Vector3(10, 10, 0));
////	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
////	SDL_Color color = { 0, 255, 0 };
////	FPSCounter->AddComponent(new RenderComponent());
////	FPSCounter->AddComponent(new TextComponent("0", font, color));
////	FPSCounter->AddComponent(new FPSComponent());
////	demoScene.AddObject(FPSCounter);
////}
//
//void Game::Cleanup()
//{
//	Renderer::GetInstance().Destroy();
//	SDL_DestroyWindow(m_Window);
//	m_Window = nullptr;
//	SDL_Quit();
//}
//
//void Game::Run()
//{
//	InitializeGame();
//
//	// tell the resource manager where he can find the game data
//	ResourceManager::GetInstance().Init("../Data/");
//
//	LoadGame();
//	SceneManager::GetInstance().Initialize();
//
//	try
//	{
//		auto& renderer = Renderer::GetInstance();
//		auto& sceneManager = SceneManager::GetInstance();
//		auto& input = InputManager::GetInstance();
//
//		bool doContinue = true;
//		float timeSinceLastFixedUpdate = 0.f;	//update time using fixed timestep (MsPerUpdate = timestep) (lag = totalTime)
//
//		Time::GetInstance().Start();
//		while (doContinue)
//		{
//			//Time::GetInstance().StartFrame();
//
//			Time::GetInstance().Update();
//			timeSinceLastFixedUpdate += Time::GetInstance().GetDeltaTime();
//
//			doContinue = input.ProcessInput();
//			while (timeSinceLastFixedUpdate >= Time::MS_PER_UPDATE)
//			{
//				//fixed update triggered
//				timeSinceLastFixedUpdate -= Time::MS_PER_UPDATE;
//			}
//			sceneManager.Update();
//
//			renderer.Render(); //Will always render
//
//			//Time::GetInstance().EndFrame();
//		}
//	}
//	catch (const std::exception & exception)
//	{
//		std::cout << exception.what() << "\n";
//	}
//
//	Cleanup();
//}
