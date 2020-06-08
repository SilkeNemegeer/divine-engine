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
	auto& demoScene = SceneManager::GetInstance().CreateScene("Demo");

	//Add background
	auto go = std::make_shared<GameObject>(Vector3(0.f, 0.f,0.f));
	RenderComponent* pRenderComp = new RenderComponent();
	pRenderComp->SetTexture("background.jpg");
	go->AddComponent(pRenderComp);
	demoScene.AddObject(go);

	//Add logo dae
	go = std::make_shared<GameObject>(Vector3(216, 180, 0));
	go->AddComponent(new RenderComponent("logo.png"));
	go->AddComponent(new RigidbodyComponent(true));
	ColliderComponent* collider = new BoxColliderComponent(glm::vec2(210, 55),glm::vec2(0,10));
	go->AddComponent(collider);
	//collider->SetTrigger(true);
	demoScene.AddObject(go);

	go = std::make_shared<GameObject>(Vector3(216, 0, 0));
	auto rigidBody = new RigidbodyComponent();
	//rigidBody->AddForce(glm::vec2(2, 0));
	go->AddComponent(rigidBody);
	ColliderComponent* colliderCircle = new CircleColliderComponent(50, glm::vec2(50, 50), false, new PhysicsMaterial2D(0.1f, 0.5f));
	//ColliderComponent* collider2 = new BoxColliderComponent(glm::vec2(210, 55), glm::vec2(0,10), false, new PhysicsMaterial2D(0.1f, 0.5f));
	go->SetTriggerCallback([](GameObject* trigger, GameObject* other, GameObject::TriggerFlag flag)
	{
			UNREFERENCED_PARAMETER(trigger);
			UNREFERENCED_PARAMETER(other);
		switch (flag)
		{
		case GameObject::TriggerFlag::enter:
			std::cout << "Entered\n";
			break;

		case GameObject::TriggerFlag::leave:
			std::cout << "Left\n";
			break;

		case GameObject::TriggerFlag::stay:	
			std::cout << "Staying\n";
			break;
		}
	});
	
	//go->AddComponent(collider2);
	go->AddComponent(colliderCircle);
	go->AddComponent(new RenderComponent("logo.png"));
	demoScene.AddObject(go);

	//Add Programming 4 Assignment text
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>(Vector3(80, 20, 0));
	go->AddComponent(new RenderComponent());
	go->AddComponent(new TextComponent("Programming 4 Assignment", font));
	demoScene.AddObject(go);

	//Add fps counter
	auto FPSCounter = std::make_shared<GameObject>(Vector3(10, 10, 0));
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	SDL_Color color = { 0, 255, 0 };
	FPSCounter->AddComponent(new RenderComponent());
	FPSCounter->AddComponent(new TextComponent("0", font, color));
	FPSCounter->AddComponent(new FPSComponent());
	demoScene.AddObject(FPSCounter);

	//Test sprite component
	auto sprite = std::make_shared<GameObject>(Vector3(100, 50, 0), 5.f);
	sprite->AddComponent(new SpriteComponent("sprites0.png", 34,16,8, 0.006f));
	demoScene.AddObject(sprite);
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
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();
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

	Cleanup();
}

divengine::Minigin::GameSettings::GameSettings()
	:m_Height{}
	,m_Width{}
{
}
