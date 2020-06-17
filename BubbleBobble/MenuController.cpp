#include "MenuController.h"
#include "MiniginPCH.h"
#include "Debug.h"
#include "Button.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "ServiceLocator.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Minigin.h"
#include "BaseGame.h"
#include "GameComponentType.h"
#include "InputManager.h"
#include "BubbleBobbleGame.h"

MenuController::MenuController()
	:m_CurrentButtonId{0}
	,m_pButtons{}
	,m_OffsetIcon(20,-2)
	,m_pSelectIcon{nullptr}
{
	m_TypeId = unsigned int(GameComponentType::menucontroller);
}

MenuController::~MenuController()
{
}

void MenuController::NavigateUp()
{
	divengine::Debug::Log("navUp");
	int oldId = m_CurrentButtonId;
	m_CurrentButtonId -= 1;
	if (m_CurrentButtonId < 0)
	{
		m_CurrentButtonId = ButtonType::COUNT - 1;
	}
	SelectButton(m_CurrentButtonId, oldId);
}

void MenuController::NavigateDown()
{
	divengine::Debug::Log("navDown");
	int oldId = m_CurrentButtonId;
	m_CurrentButtonId += 1;
	m_CurrentButtonId %= ButtonType::COUNT;
	SelectButton(m_CurrentButtonId, oldId);
}

void MenuController::Select()
{
	divengine::Debug::Log("Select");

	switch (m_CurrentButtonId)
	{
	case ButtonType::singleplayer:
		//Start game
		divengine::Debug::Log("Start 1P game");
		//Set the gamemode
		BubbleBobbleGame::m_GameMode = BubbleBobbleGame::GameMode::solo;
		//Load the scene with the right gamemode
		

		divengine::SceneManager::GetInstance().SetAsCurrentScene("Level1");

		//Load first scene
		break;

	case ButtonType::coop:
		divengine::Debug::Log("Start coop game");
		BubbleBobbleGame::m_GameMode = BubbleBobbleGame::GameMode::coop;
		break;

	case ButtonType::exit:
		//Exit game
		divengine::Debug::Log("Exit game");
		divengine::Minigin::Quit();
		break;

	case ButtonType::pvp:
		divengine::Debug::Log("Start pvp game");
		BubbleBobbleGame::m_GameMode = BubbleBobbleGame::GameMode::versus;
		divengine::SceneManager::GetInstance().SetAsCurrentScene("Demo");
		break;
	}
}

void MenuController::Update()
{

}

void MenuController::Initialize()
{
	CreateButtons();

	divengine::InputManager::GetInstance().AddInputMapping(BubbleBobbleGame::CommandId::select, SDL_SCANCODE_RETURN, XINPUT_GAMEPAD_A, divengine::TriggerState::pressed, m_pGameObject);
	divengine::InputManager::GetInstance().AddInputMapping(BubbleBobbleGame::CommandId::navigatedown, SDL_SCANCODE_DOWN, XINPUT_GAMEPAD_DPAD_DOWN, divengine::TriggerState::pressed, m_pGameObject);
	divengine::InputManager::GetInstance().AddInputMapping(BubbleBobbleGame::CommandId::navigateup, SDL_SCANCODE_UP, XINPUT_GAMEPAD_DPAD_UP, divengine::TriggerState::pressed, m_pGameObject);
}

void MenuController::Load(divengine::BinaryReader& )
{

	//No need 
}

void MenuController::Save(divengine::BinaryWriter& )
{
	//No need
}

divengine::GameObject* MenuController::CreateButton(const std::string& text, const glm::vec2& pos)
{
	using namespace divengine;
	GameObject* pButton = new GameObject(divengine::Vector3(pos.x, pos.y ,0));
	auto s = ServiceLocator::GetResourceManager()->LoadFont("Lingua.otf", 20);

	//pButton->AddComponent(new RenderComponent(true));
	pButton->AddComponent(new TextComponent(text, s, SDL_Color{ 50, 50, 50 }));
	pButton->AddComponent(new Button(SDL_Color{ 255, 0, 0 }, SDL_Color{ 50, 50, 50 }));
	return pButton;
}

void MenuController::CreateButtons()
{
	//Create buttons
	glm::vec2 pos;
	pos.x = divengine::BaseGame::GetGameSettings().Width / 2.f;
	pos.y = 220.f;
	divengine::GameObject* pStartButton = CreateButton("1P - START", pos);
	m_pButtons.push_back(pStartButton);

	pos.x = divengine::BaseGame::GetGameSettings().Width / 2.f;
	pos.y = 250.f;
	divengine::GameObject* pCoopButton = CreateButton("2P COOP - START", pos);
	m_pButtons.push_back(pCoopButton);

	pos.x = divengine::BaseGame::GetGameSettings().Width / 2.f;
	pos.y = 280.f;
	divengine::GameObject* pPvpButton = CreateButton("2P PVP - START", pos);
	m_pButtons.push_back(pPvpButton);
	
	pos.x = divengine::BaseGame::GetGameSettings().Width / 2.f;
	pos.y = 310.f;
	divengine::GameObject* pExitButton = CreateButton("EXIT", pos);
	m_pButtons.push_back(pExitButton);

	auto pActiveScene = divengine::SceneManager::GetInstance().GetSceneByName("MainMenu");
	for (auto pButton : m_pButtons)
	{
		pActiveScene->AddObject(pButton);
		pButton->Initialize();
		pButton->Start();
	}

	m_pButtons[ButtonType::singleplayer]->GetComponent<Button>()->SetSelected(true);
	m_CurrentButtonId = ButtonType::singleplayer;

	//Create select icon
	m_pSelectIcon = new divengine::GameObject(divengine::Vector3(m_pButtons[m_CurrentButtonId]->GetPos().x - m_OffsetIcon.x
		, m_pButtons[m_CurrentButtonId]->GetPos().y - m_OffsetIcon.y));
	m_pSelectIcon->AddComponent(new divengine::RenderComponent("icon.png")); //icon.png
	pActiveScene->AddObject(m_pSelectIcon);

	m_pSelectIcon->Initialize();
	m_pSelectIcon->Start();
}

void MenuController::SelectButton(int id, int oldId)
{
	m_pButtons[oldId]->GetComponent<Button>()->SetSelected(false);
	m_pButtons[id]->GetComponent<Button>()->SetSelected(true);

	auto newPos = m_pButtons[id]->GetPos();
	m_pSelectIcon->SetPos(glm::vec2(newPos.x - m_OffsetIcon.x, newPos.y - m_OffsetIcon.y));
}
