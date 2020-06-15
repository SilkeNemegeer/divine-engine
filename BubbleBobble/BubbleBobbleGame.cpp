#include "MiniginPCH.h"
#include "BubbleBobbleGame.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Components.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "TextObject.h"
#include "Debug.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "Animator.h"
#include "AnimationClip.h"
#include "Commands.h"
#include "Timer.h"
#include "MenuController.h"

BubbleBobbleGame::BubbleBobbleGame()
{
}

BubbleBobbleGame::~BubbleBobbleGame()
{
}

void BubbleBobbleGame::Initialize()
{
	using namespace divengine;

	//Init managers
	ServiceLocator::Init();
	ServiceLocator::GetResourceManager()->Init("../Data/");	// tell the resource manager where he can find the game data

	//Load scenes
	auto& demoScene = SceneManager::GetInstance().CreateScene("Demo");

	//Add background
	//auto go = new GameObject(Vector3(0.f, 0.f, 0.f));
	//RenderComponent* pRenderComp = new RenderComponent();
	//pRenderComp->SetTexture("background.jpg");
	//go->AddComponent(pRenderComp);
	//demoScene.AddObject(go);

	//ADD bubble bobble main screen
	RenderComponent* pBubbleBobbleImage = new RenderComponent();
	pBubbleBobbleImage->SetTexture("BubbleBobbleText.png");
	float halfWidth = pBubbleBobbleImage->GetTextureDimensions().x / 2.f;
	auto go = new GameObject(Vector3(320.f - halfWidth, 50.f, 0.f), 1.f);

	go->AddComponent(pBubbleBobbleImage);
	demoScene.AddObject(go);

	////Add logo dae
	//go = new GameObject(Vector3(216, 180, 0));
	//go->AddComponent(new RenderComponent("logo.png"));
	//go->AddComponent(new RigidbodyComponent(true));
	//ColliderComponent* collider = new BoxColliderComponent(glm::vec2(210, 55), glm::vec2(0, 10));
	//go->AddComponent(collider);
	////collider->SetTrigger(true);
	//demoScene.AddObject(go);

	auto font = ServiceLocator::GetResourceManager()->LoadFont("Lingua.otf", 36);

	//go = new GameObject(Vector3(216, 0, 0));
	//auto rigidBody = new RigidbodyComponent();
	////rigidBody->AddForce(glm::vec2(2, 0));
	//go->AddComponent(rigidBody);
	//ColliderComponent* colliderCircle = new CircleColliderComponent(50, glm::vec2(50, 50), false, new PhysicsMaterial2D(0.1f, 0.5f));
	////ColliderComponent* collider2 = new BoxColliderComponent(glm::vec2(210, 55), glm::vec2(0,10), false, new PhysicsMaterial2D(0.1f, 0.5f));
	//go->SetTriggerCallback([](GameObject* trigger, GameObject* other, GameObject::TriggerFlag flag)
	//	{
	//		UNREFERENCED_PARAMETER(trigger);
	//		UNREFERENCED_PARAMETER(other);
	//		switch (flag)
	//		{
	//		case GameObject::TriggerFlag::enter:
	//			std::cout << "Entered\n";
	//			break;

	//		case GameObject::TriggerFlag::leave:
	//			std::cout << "Left\n";
	//			break;

	//		case GameObject::TriggerFlag::stay:
	//			std::cout << "Staying\n";
	//			break;
	//		}
	//	});

	////go->AddComponent(collider2);
	//go->AddComponent(colliderCircle);
	//go->AddComponent(new RenderComponent("logo.png"));
	//demoScene.AddObject(go);

	//Add Programming 4 Assignment text
	//go = new GameObject(Vector3(80, 20, 0));
	//go->AddComponent(new RenderComponent());
	//go->AddComponent(new TextComponent("Programming 4 Assignment", font));
	//demoScene.AddObject(go);

	//Add fps counter
	auto FPSCounter = new GameObject(Vector3(10, 10, 0));
	font = ServiceLocator::GetResourceManager()->LoadFont("Lingua.otf", 20);
	//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	SDL_Color color = { 0, 255, 0 };
	FPSCounter->AddComponent(new RenderComponent());
	FPSCounter->AddComponent(new TextComponent("0", font, color));
	FPSCounter->AddComponent(new FPSComponent());
	demoScene.AddObject(FPSCounter);

	//Test sprite component
	//auto sprite = std::make_shared<GameObject>(Vector3(100, 50, 0), 5.f);
	//sprite->AddComponent(new SpriteComponent("sprites0.png", 34, 16, 8, 0.006f));
	//demoScene.AddObject(sprite);

	//SoundManager &sound = ServiceLocator::GetSoundManager();
	//sound.LoadSound("Sounds/Apprehensive_at_Best.mp3", "testSound", FMOD_2D | FMOD_LOOP_NORMAL);
	//sound.AddChannel(0);
	//sound.AddChannel(1);
	//sound.LoadSound("Sounds/Aggressive_Zombie_Snarls.mp3", "testSound2", FMOD_2D | FMOD_LOOP_NORMAL);
	//sound.StartSound("testSound", 0);
	//sound.StartSound("testSound2", 1);
	//sound.SetMasterVolume(0.08f);

	////sound.GetChannel(0)->setVolume(0.08f);
	//auto zombiechannel = sound.GetChannel(1); //->setVolume(0.4f);
	//zombiechannel->setVolume(0.f);
	//InputManager::GetInstance().AddCommand(new JumpCommand(), 0);
	//InputManager::GetInstance().AddInputMapping(0, SDL_SCANCODE_A, XINPUT_GAMEPAD_B, TriggerState::down);

	/*InputManager::GetInstance().SetVibration(0.5, 0);
	Timer* t = new Timer(2.f, []()
	{
		InputManager::GetInstance().SetVibration(0, 0);
	});
	t->Start();
	demoScene.AddObject(static_cast<std::shared_ptr<GameObject>>(t));*/

	go = new GameObject(Vector3(100, 50, 0), 5.f);
	auto animator = new Animator("sprites.png", 16, 16);
	animator->AddAnimation(new AnimationClip(0, 2, 2, "MoveRight", 2));
	animator->AddAnimation(new AnimationClip(0, 1, 2, "MoveLeft", 5));
	go->AddComponent(animator);
	animator->Play();
	demoScene.AddObject(go);

	auto menu = new GameObject(Vector3(0, 0, 0));
	menu->AddComponent(new MenuController());
	demoScene.AddObject(menu);

	//Add commands
	InputManager::GetInstance().AddCommand(new Select(), 1);
	InputManager::GetInstance().AddCommand(new NavigateDown(), 2);
	InputManager::GetInstance().AddCommand(new NavigateUp(), 3);

	InputManager::GetInstance().AddInputMapping(1, SDL_SCANCODE_RETURN, XINPUT_GAMEPAD_A, TriggerState::pressed, menu);
	InputManager::GetInstance().AddInputMapping(2, SDL_SCANCODE_DOWN, XINPUT_GAMEPAD_DPAD_DOWN, TriggerState::pressed, menu);
	InputManager::GetInstance().AddInputMapping(3, SDL_SCANCODE_UP, XINPUT_GAMEPAD_DPAD_UP, TriggerState::pressed, menu);
}
