#pragma once
#include <XInput.h>
#include "Singleton.h"
class Command;
#include <map>
namespace divengine
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class TriggerState
		{
			down, pressed, released
		};

		struct ActionMapping
		{
			ActionMapping()
			{
				button = 0;
				key = 0;
				actionId = 0;
				triggerState = TriggerState::pressed;
				playerIndex = 0; //player 1
			}
			WORD button;
			int key;
			int actionId;
			TriggerState triggerState;
			int playerIndex;
		};

		bool ProcessInput();
		void AddImGuiKeyboardMappings();
		bool IsTriggered(WORD button, TriggerState triggerState, int controllerId = 0) const;
		~InputManager() {};

	private:
		friend class Singleton<InputManager>;

		InputManager();
		std::map<int, ActionMapping> m_ActionMappings;
		XINPUT_STATE m_ControllerStates[XUSER_MAX_COUNT], m_PreviousControllerStates[XUSER_MAX_COUNT];
		bool m_ConnectedControllers[XUSER_MAX_COUNT];

		void RefreshControllers();
		void UpdateControllerState();
	};

}
