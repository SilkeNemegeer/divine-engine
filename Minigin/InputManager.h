#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "ControllerComponent.h"
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

		struct InputMapping
		{
			InputMapping(int commandId, int key = -1, WORD controllerButton = 0, TriggerState triggerState = TriggerState::pressed, ControllerComponent* pController = nullptr, int controllerId = 1)
				:ControllerButton{ controllerButton }
				,KeyboardButton{key}
				,CommandID{commandId}
				,TriggerState{triggerState}
				,PlayerIndex{controllerId}
				,Controller{pController}
			{};
			WORD ControllerButton;
			int KeyboardButton;
			int CommandID;
			TriggerState TriggerState;
			int PlayerIndex;
			ControllerComponent* Controller;
		};

		bool ProcessInput();
		void AddImGuiKeyboardMappings();

	//	void AddCommand(Command* pCommand, int commandId); //Add a command
		//void AddInputMapping(int commandId, int key, WORD controllerButton, TriggerState triggerState = TriggerState::pressed, ControllerComponent* pController = nullptr, int controllerId = 1);
		
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
