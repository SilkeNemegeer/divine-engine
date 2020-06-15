#pragma once
#include "GeneralStructs.h"
#include "Minigin.h"

namespace divengine
{
	class BaseGame
	{
	public:
		BaseGame(const BaseGame& other) = delete;
		BaseGame(BaseGame&& other) noexcept = delete;
		BaseGame& operator=(const BaseGame& other) = delete;
		BaseGame& operator=(BaseGame&& other) noexcept = delete;
		BaseGame();
		virtual ~BaseGame();

		void Run();

		static const GameSettings& GetGameSettings() { return m_GameSettings; };
		
	protected:
		virtual void Initialize() = 0;


	private:
		static GameSettings m_GameSettings;
		SDL_Window* m_Window{};
		divengine::Minigin m_Engine;

	};
}
