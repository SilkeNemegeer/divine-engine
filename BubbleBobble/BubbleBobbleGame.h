#pragma once
#include "BaseGame.h"
class BubbleBobbleGame : public divengine::BaseGame
{
public:

	enum class GameMode
	{
		solo, //bob
		coop, //bob and bub
		versus //bob = player 1, maita = player 2
	};

	enum CommandId : int
	{
		select
		, navigatedown
		, navigateup
		, moveleft
		, moveright
		, jump
		, attack
	};

	BubbleBobbleGame();
	virtual ~BubbleBobbleGame();
	//static const GameMode& GetGameMode() { return m_GameMode; };
	static GameMode m_GameMode;

private:
	virtual void Initialize();
};

