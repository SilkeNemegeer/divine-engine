#pragma once
#include "Singleton.h"
#include <map>
namespace divengine
{
	class GameObject;
	class Command;

	enum class TriggerState
	{
		down, pressed, released
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		struct InputMapping
		{
			InputMapping(int commandId, SDL_Scancode key = SDL_Scancode::SDL_NUM_SCANCODES, WORD controllerButton = 0, TriggerState triggerState = TriggerState::pressed
				, GameObject* pObject = nullptr, int controllerId = 0)
				:ControllerButton{controllerButton}
				,CommandId{commandId}
				,KeyboardButton{key}
				,Trigger{triggerState}
				,pObject{pObject}
				,PlayerIndex{controllerId}
			{
			}
			WORD ControllerButton;
			SDL_Scancode KeyboardButton;
			TriggerState Trigger;
			int PlayerIndex;
			int CommandId;
			GameObject* pObject;
		};

		bool ProcessInput();

		void AddCommand(Command* pCommand, int commandId); //Add a command
		void AddInputMapping(int commandId, SDL_Scancode key = SDL_Scancode::SDL_NUM_SCANCODES, WORD controllerButton = 0, TriggerState triggerState = TriggerState::pressed, GameObject* pObject = nullptr, int controllerId = 0);
		
		void DestroyInputMappings();

		bool IsTriggered(WORD button, TriggerState triggerState, int controllerId = 0) const;
		bool IsKeyTriggered(SDL_Scancode key, TriggerState triggerState) const;

		//TODO: mouse button detection
		void SetVibration(float leftMotorSpeed, float rightMotorSpeed, int controllerId = 0); //Set speeds to 0 to stop a vibration
																									  
		//TODO: call refresh connections only when asked, not always

		glm::vec2 GetMousePos() { return m_MousePos; };
		glm::vec2 GetThumbStickPos(int controllerId = 0, bool leftStick = true);
		~InputManager();

	private:
		friend class Singleton<InputManager>;

		InputManager();
		void AddImGuiKeyboardMappings();

		void ProcessSDLInput(SDL_Event& e);

		std::vector<InputMapping*> m_pInputMappings;
		std::map<int, Command*> m_pCommands;
		const Uint8* m_pCurrentSDLKeyBoardState;
		Uint8 m_pPrevSDLKeyboardState[SDL_NUM_SCANCODES];
		glm::vec2 m_MousePos;
		bool m_KeyboardState1Active;

		SDL_Event m_CurrentEvent;

		XINPUT_STATE m_ControllerStates[XUSER_MAX_COUNT], m_PreviousControllerStates[XUSER_MAX_COUNT];
		bool m_ConnectedControllers[XUSER_MAX_COUNT];

		void RefreshControllers();
		void UpdateControllerState();
	};

}
