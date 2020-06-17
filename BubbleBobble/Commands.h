#pragma once
#include "Command.h"
#include "InputManager.h"
#include "PlayerController.h"
#include "MenuController.h"

using namespace divengine;

class JumpCommand : public Command
{
public:
	JumpCommand() {}; //Can pass extra values here if needed
	void Execute(GameObject* pObject) override 
	{
		auto playerController = pObject->GetComponent<PlayerController>();
		if (playerController)
		{
			playerController->Jump();
		}
	
	}
	void Undo() override {}
private:
};

class MoveLeft : public Command
{
public:
	void Execute(GameObject* pObject) override
	{
		auto playerController = pObject->GetComponent<PlayerController>();
		if (playerController)
		{
			playerController->MoveLeft();
		}
	}
	void Undo() override {}

private:

};

class MoveRight : public Command
{
public:
	void Execute(GameObject* pObject) override
	{
		auto playerController = pObject->GetComponent<PlayerController>();
		if (playerController)
		{
			playerController->MoveRight();
		}
	}
	void Undo() override {}

private:
};

class Attack : public Command
{
public:
	void Execute(GameObject* pObject) override
	{
		auto playerController = pObject->GetComponent<PlayerController>();
		if (playerController)
		{
			playerController->Attack();
		}
	}
	void Undo() override {}

private:
};

class NavigateUp : public Command
{
public:
	void Execute(GameObject* pObject) override
	{
		auto menuController = pObject->GetComponent<MenuController>();
		if (menuController && SceneManager::GetInstance().GetCurrentScene()->Name() == "MainMenu")
		{
			menuController->NavigateUp();
		}
	}
	void Undo() override {}
};

class NavigateDown : public Command
{
public:
	void Execute(GameObject* pObject) override
	{
		auto menuController = pObject->GetComponent<MenuController>();
		if (menuController && SceneManager::GetInstance().GetCurrentScene()->Name() == "MainMenu")
		{
			menuController->NavigateDown();
		}
	}
	void Undo() override {}
};

class Select : public Command
{
public:
	void Execute(GameObject* pObject) override
	{
		auto menuController = pObject->GetComponent<MenuController>();
		if (menuController && SceneManager::GetInstance().GetCurrentScene()->Name() == "MainMenu")
		{
			menuController->Select();
		}
	}
	void Undo() override {}
};