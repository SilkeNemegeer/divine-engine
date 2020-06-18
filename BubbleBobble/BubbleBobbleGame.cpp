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
#include "ServiceLocator.h"
#include "FileManager.h"
#include "MaterialManager.h"
#include "Health.h"
#include "PhysicsMaterial2D.h"
#include "ItemBehaviour.h"
#include "HUD.h"
#include "ZenChanBehaviour.h"
#include "MaitaBehaviour.h"
#include "AIController.h"

BubbleBobbleGame::GameMode BubbleBobbleGame::m_GameMode = BubbleBobbleGame::GameMode::solo;

BubbleBobbleGame::BubbleBobbleGame()
{
}

BubbleBobbleGame::~BubbleBobbleGame()
{

}

void LoadDemoLevel()
{
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
	animator->AddAnimation(new AnimationClip(0, 2, 2, "MoveRight", 2), CharacterAnimations::moveRight);
	animator->AddAnimation(new AnimationClip(0, 1, 2, "MoveLeft", 5), CharacterAnimations::moveLeft);
	go->AddComponent(animator);
	animator->Play();
	demoScene.AddObject(go);

	auto menu = new GameObject(Vector3(0, 0, 0));
	menu->AddComponent(new MenuController());
	demoScene.AddObject(menu);

	//Add commands
	//InputManager::GetInstance().AddCommand(new Select(), 1);
	//InputManager::GetInstance().AddCommand(new NavigateDown(), 2);
	//InputManager::GetInstance().AddCommand(new NavigateUp(), 3);

	/*InputManager::GetInstance().AddInputMapping(1, SDL_SCANCODE_RETURN, XINPUT_GAMEPAD_A, TriggerState::pressed, menu);
	InputManager::GetInstance().AddInputMapping(2, SDL_SCANCODE_DOWN, XINPUT_GAMEPAD_DPAD_DOWN, TriggerState::pressed, menu);
	InputManager::GetInstance().AddInputMapping(3, SDL_SCANCODE_UP, XINPUT_GAMEPAD_DPAD_UP, TriggerState::pressed, menu);*/
}

void LoadMainMenu()
{
	//auto& level1Scene = SceneManager::GetInstance().CreateScene("MainMenu");

	//auto menu = new GameObject(Vector3(0, 0, 0));
	//menu->AddComponent(new MenuController());
	//level1Scene.AddObject(menu);

	////ADD bubble bobble main screen
	//RenderComponent* pBubbleBobbleImage = new RenderComponent(true);
	//pBubbleBobbleImage->SetTexture("BubbleBobbleText.png");
	//auto go = new GameObject(Vector3((BaseGame::GetGameSettings().Width /2.f), 100.f, 0.f), 1.f);
	//go->AddComponent(pBubbleBobbleImage);
	//level1Scene.AddObject(go);
	//
	//FileManager::GetInstance().SaveLevel("../Data/MainMenu.div", "MainMenu");

	SceneManager::GetInstance().CreateScene("MainMenu");
	FileManager::GetInstance().LoadLevel("../Data/MainMenu.div", "MainMenu");
}

void LoadLevel1()
{
	auto& level1Scene = SceneManager::GetInstance().CreateScene("Level1");

	//Add background
	RenderComponent* pBubbleBobbleImage = new RenderComponent();
	pBubbleBobbleImage->SetTexture("level1.png");
	auto go = new GameObject(Vector3(0.f, 0.f, 0.f), 2.f);
	go->AddComponent(pBubbleBobbleImage);
	level1Scene.AddObject(go);

	//Create level colliders
	//Add collider & test saving and loading
	GameObject* pBottomWall = new GameObject();
	auto rigidBody = new RigidbodyComponent(true);
    pBottomWall->AddComponent(rigidBody);
	pBottomWall->AddComponent(new BoxColliderComponent(glm::vec2(BaseGame::GetGameSettings().Width,80)));
	level1Scene.AddObject(pBottomWall);

	GameObject* pTopWall = new GameObject(Vector3(0, BaseGame::GetGameSettings().Height - 50.f, 0));
	rigidBody = new RigidbodyComponent(true);
	pTopWall->AddComponent(rigidBody);
	pTopWall->AddComponent(new BoxColliderComponent(glm::vec2(BaseGame::GetGameSettings().Width, 50)));
	level1Scene.AddObject(pTopWall);

	GameObject* pLeftWall = new GameObject(Vector3(0,0,0));
	rigidBody = new RigidbodyComponent(true);
	pLeftWall->AddComponent(rigidBody);
	pLeftWall->AddComponent(new BoxColliderComponent(glm::vec2(35, BaseGame::GetGameSettings().Height)));
	level1Scene.AddObject(pLeftWall);

	GameObject* pRightWall = new GameObject(Vector3(BaseGame::GetGameSettings().Width - 35.f, 0,0));
	rigidBody = new RigidbodyComponent(true);
	pRightWall->AddComponent(rigidBody);
	pRightWall->AddComponent(new BoxColliderComponent(glm::vec2(35, BaseGame::GetGameSettings().Height)));
	level1Scene.AddObject(pRightWall);


	////Add 3 platforms but with change in height
	float height = 382.f;
	for (int i = 0; i < 3; i++)
	{
		//Add the 3 platforms horizontal

		GameObject* pPlatform = new GameObject(Vector3(35, height, 0));
		rigidBody = new RigidbodyComponent(true);
		pPlatform->AddComponent(rigidBody);
		pPlatform->AddComponent(new PlatformColliderComponent(glm::vec2(30.f, 20.f)));
		level1Scene.AddObject(pPlatform);

		pPlatform = new GameObject(Vector3(110, height, 0));
		rigidBody = new RigidbodyComponent(true);
		pPlatform->AddComponent(rigidBody);
		pPlatform->AddComponent(new PlatformColliderComponent(glm::vec2(290.f, 20.f)));
		level1Scene.AddObject(pPlatform);

		pPlatform = new GameObject(Vector3(445, height, 0));
		rigidBody = new RigidbodyComponent(true);
		pPlatform->AddComponent(rigidBody);
		pPlatform->AddComponent(new PlatformColliderComponent(glm::vec2(35.f, 20.f)));
		level1Scene.AddObject(pPlatform);

		height -= 80.f;
	}

	//Create player
	GameObject* pPlayer = new GameObject(Vector3(200, 200, 0), 2);
	auto renderComp = new RenderComponent("sprites.png");
	pPlayer->AddComponent(renderComp);
	auto animator = new Animator("sprites.png", 16, 16);

	pPlayer->AddComponent(animator);
	pPlayer->AddComponent(new RigidbodyComponent());

	//ADD materials
	MaterialManager::GetInstance().AddMaterial(new PhysicsMaterial2D(4.f, 0.f), 0);
	MaterialManager::GetInstance().AddMaterial(new PhysicsMaterial2D(0.f, 0.f), 1);


	pPlayer->AddComponent(new BoxColliderComponent(glm::vec2(32, 32), glm::vec2(), false, 0));
	pPlayer->AddComponent(new PlayerController());
	pPlayer->AddComponent(new Health(1));
	level1Scene.AddObject(pPlayer);

	//Add pickup
	GameObject* pPickUp = new GameObject(Vector3(250, 250, 0), 0.5f);
	pPickUp->AddComponent(new RenderComponent("Items/Bubble_Bobble_item_french_fries.png"));
	pPickUp->AddComponent(new RigidbodyComponent(true));
	pPickUp->AddComponent(new BoxColliderComponent(glm::vec2(36,36), glm::vec2(), true));
	pPickUp->AddComponent(new ItemBehaviour(200));
	level1Scene.AddObject(pPickUp);

	//ADD hud
	GameObject* pHud = new GameObject(Vector3(60, 20, 0));
	auto font = ServiceLocator::GetResourceManager()->LoadFont("Fonts/Airstream.ttf", 30);
	auto hudComp = new HUD(font, {0,0,0});
	hudComp->LinkPlayer(pPlayer->GetComponent<PlayerController>());
	pHud->AddComponent(hudComp);
	level1Scene.AddObject(pHud);

	//Add enemies
	GameObject* pZenChan = new GameObject(Vector3(60, 200, 0),2);
	pZenChan->AddComponent(new RigidbodyComponent());
	pZenChan->AddComponent(new BoxColliderComponent(glm::vec2(32, 32)));
	renderComp = new RenderComponent("sprites.png");
	pZenChan->AddComponent(renderComp);
	animator = new Animator("sprites.png", 16, 16);
	animator->AddAnimation(new AnimationClip(2, 4, 2, "WalkingLeft"), CharacterAnimations::moveLeft);
	animator->AddAnimation(new AnimationClip(0, 4, 2, "WalkingRight"), CharacterAnimations::moveRight);
	animator->AddAnimation(new AnimationClip(4, 4, 2, "WalkingRight"), CharacterAnimations::inBubble);
	animator->Play();
	pZenChan->AddComponent(animator);
	auto zenChanBehaviour = new ZenChanBehaviour();
	pZenChan->AddComponent(zenChanBehaviour);
	pZenChan->AddComponent(new AIController(zenChanBehaviour));

	//has ai controller -> so it moves to the enemy
	level1Scene.AddObject(pZenChan);

	//Add Maita
	GameObject* pMaita = new GameObject(Vector3(150, 50, 0),2);
	pMaita->AddComponent(new RigidbodyComponent());
	pMaita->AddComponent(new BoxColliderComponent(glm::vec2(32, 32)));
	renderComp = new RenderComponent("sprites.png");
	pMaita->AddComponent(renderComp);
	animator = new Animator("sprites.png", 16, 16);
	animator->AddAnimation(new AnimationClip(4, 15, 2, "WalkingLeft"), CharacterAnimations::moveLeft);
	animator->AddAnimation(new AnimationClip(2, 15, 2, "WalkingRight"), CharacterAnimations::moveRight);
	animator->AddAnimation(new AnimationClip(6, 15, 4, "WalkingRight"), CharacterAnimations::inBubble);
	animator->Play();
	pMaita->AddComponent(animator);
	auto maitaBehviour = new MaitaBehaviour();
	pMaita->AddComponent(maitaBehviour);
	pMaita->AddComponent(new AIController(maitaBehviour));

	//has ai controller -> so it moves to the enemy
	level1Scene.AddObject(pMaita);

	//animator->Play();
	//If works -> add all colliders

	//Add rigidbody & test saving and loading

	//CREATE PLAYERS OUTSIDE OF LEVEL LOADING (create them according to the game mode)

	//ENEMIES OUTSIDE FILE or inside (check what is best)
	//SAVE ENEMY COUNT IN FILE (so you can check when there are no enemies left in the level)

	//If works -> start on player controller & movement (create player)
		//Create player input

	divengine::InputManager::GetInstance().AddInputMapping(BubbleBobbleGame::CommandId::moveleft, SDL_SCANCODE_LEFT, XINPUT_GAMEPAD_DPAD_LEFT, divengine::TriggerState::down, pPlayer);
	divengine::InputManager::GetInstance().AddInputMapping(BubbleBobbleGame::CommandId::moveright, SDL_SCANCODE_RIGHT, XINPUT_GAMEPAD_DPAD_RIGHT, divengine::TriggerState::down, pPlayer);
	divengine::InputManager::GetInstance().AddInputMapping(BubbleBobbleGame::CommandId::jump, SDL_SCANCODE_UP, XINPUT_GAMEPAD_X, divengine::TriggerState::pressed, pPlayer);
	divengine::InputManager::GetInstance().AddInputMapping(BubbleBobbleGame::CommandId::attack, SDL_SCANCODE_P, XINPUT_GAMEPAD_A, divengine::TriggerState::pressed, pPlayer);

	//ADD SOUND
	SoundManager *sound = ServiceLocator::GetSoundManager();
	sound->LoadSound("Sounds/03_Room Theme.mp3", "BackGroundMusic", FMOD_2D | FMOD_LOOP_NORMAL);
	sound->AddChannel(0);
	//sound.AddChannel(1);
	//sound.LoadSound("Sounds/Aggressive_Zombie_Snarls.mp3", "testSound2", FMOD_2D | FMOD_LOOP_NORMAL);
	sound->StartSound("BackGroundMusic", 0);
	sound->GetChannel(0)->setVolume(0.05f);
	//sound.StartSound("testSound2", 1);
	//sound.SetMasterVolume(0.08f);


	//FileManager::GetInstance().SaveLevel("../Data/Level1.div", "Level1");

	/*SceneManager::GetInstance().CreateScene("Level1");
	FileManager::GetInstance().LoadLevel("../Data/Level1.div", "Level1");*/

}

void BubbleBobbleGame::Initialize()
{
	using namespace divengine;

	//Init managers
	ServiceLocator::Init();
	ServiceLocator::GetResourceManager()->Init("../Data/");	// tell the resource manager where he can find the game data

	//--- Add commands ---
	//Menu
	InputManager::GetInstance().AddCommand(new Select(), CommandId::select);
	InputManager::GetInstance().AddCommand(new NavigateDown(), CommandId::navigatedown);
	InputManager::GetInstance().AddCommand(new NavigateUp(), CommandId::navigateup);

	//Players
	InputManager::GetInstance().AddCommand(new MoveLeft(), CommandId::moveleft);
	InputManager::GetInstance().AddCommand(new MoveRight(), CommandId::moveright);
	InputManager::GetInstance().AddCommand(new JumpCommand(), CommandId::jump);
	InputManager::GetInstance().AddCommand(new Attack(), CommandId::attack);

	//Load scenes
	LoadMainMenu();
	LoadLevel1();
	//LoadDemoLevel();

	SceneManager::GetInstance().SetAsCurrentScene("MainMenu");
	//SceneManager::GetInstance().SetAsCurrentScene("Level1");

}
