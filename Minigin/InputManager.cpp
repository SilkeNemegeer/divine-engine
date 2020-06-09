#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Command.h"
#include "Time.h"
#include "Debug.h"

//References for input ImGui:
//https://github.com/Tyyppi77/imgui_sdl/blob/master/example.cpp
//https://github.com/ocornut/imgui/blob/master/examples/imgui_impl_sdl.cpp

bool divengine::InputManager::ProcessInput()
{
	RefreshControllers();
	UpdateControllerState();

	ImGuiIO& io = ImGui::GetIO();
	int wheel = 0;

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}

		if (!io.WantCaptureKeyboard || !io.WantCaptureMouse)
		{
			//capture other input (not imgui input)

		}

		if (e.type == SDL_WINDOWEVENT)
		{
			if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				io.DisplaySize.x = static_cast<float>(e.window.data1);
				io.DisplaySize.y = static_cast<float>(e.window.data2);
			}
		}
		if (e.type == SDL_MOUSEWHEEL)
		{
			wheel = e.wheel.y;
		}
		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
			int key =e.key.keysym.scancode;
			IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
			io.KeysDown[key] = (e.type == SDL_KEYDOWN);
			io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
			io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
			io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
		}
		if (e.type == SDL_TEXTINPUT)
		{
			io.AddInputCharactersUTF8(e.text.text);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		
	}

	int mouseX, mouseY;
	const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

	io.DeltaTime = Time::GetInstance().GetDeltaTime();
	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	io.MouseWheel = static_cast<float>(wheel);

	return true;
}

void divengine::InputManager::AddImGuiKeyboardMappings()
{
	ImGuiIO& io = ImGui::GetIO();

	io.KeyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
	io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
	io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
	io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
	io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
	io.KeyMap[ImGuiKey_Insert] = SDL_SCANCODE_INSERT;
	io.KeyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = SDL_SCANCODE_SPACE;
	io.KeyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;
	io.KeyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;
	io.KeyMap[ImGuiKey_KeyPadEnter] = SDL_SCANCODE_KP_ENTER;
	io.KeyMap[ImGuiKey_A] = SDL_SCANCODE_A;
	io.KeyMap[ImGuiKey_C] = SDL_SCANCODE_C;
	io.KeyMap[ImGuiKey_V] = SDL_SCANCODE_V;
	io.KeyMap[ImGuiKey_X] = SDL_SCANCODE_X;
	io.KeyMap[ImGuiKey_Y] = SDL_SCANCODE_Y;
	io.KeyMap[ImGuiKey_Z] = SDL_SCANCODE_Z;
}

void divengine::InputManager::AddCommand(Command* pCommand, int commandId)
{
	if (m_pCommands.find(commandId) != m_pCommands.end())
	{
		Debug::LogWarning("InputManager::AddCommand: there was already a command with this id!");
		return;
	}

	m_pCommands[commandId] = pCommand;
}

bool divengine::InputManager::IsTriggered(WORD button, TriggerState triggerState, int controllerId) const
{
	if (!m_ConnectedControllers[controllerId] || (button <= 0x0000 && button > 0x8000))
		return false;
		
	bool currentStateTriggered = (button & m_ControllerStates[controllerId].Gamepad.wButtons) != 0;
	bool oldStateTriggered = (m_PreviousControllerStates[controllerId].Gamepad.wButtons & button) != 0;

	switch (triggerState)
	{
		case divengine::InputManager::TriggerState::down:
			return (currentStateTriggered && oldStateTriggered);
		case divengine::InputManager::TriggerState::pressed:
			return (currentStateTriggered && !oldStateTriggered);
		case divengine::InputManager::TriggerState::released:
			return (!currentStateTriggered && oldStateTriggered);
		default:
			return false;
	}
}

divengine::InputManager::~InputManager()
{
	for (auto pCommand : m_pCommands)
	{
		SAFEDELETE(pCommand.second);
	}
}

divengine::InputManager::InputManager()
	:m_ControllerStates{}
	, m_ConnectedControllers{}
	,m_PreviousControllerStates{}
{
	RefreshControllers();
}

void divengine::InputManager::RefreshControllers()
{
	for (int i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		if (XInputGetState(DWORD(i), &state) == ERROR_SUCCESS)
		{
			if (!m_ConnectedControllers[i])
			{
				m_ConnectedControllers[i] = true;
				std::cout << "Player " << i << " connected\n";
			}
		}
		else
		{
			if (m_ConnectedControllers[i])
			{
				std::cout << "Player " << i << " disconnected\n";
				m_ConnectedControllers[i] = false;
			}
		}
	}
}

void divengine::InputManager::UpdateControllerState()
{
	DWORD result{};

	for (int i = 0; i < XUSER_MAX_COUNT; i++)
	{
		if (!m_ConnectedControllers[i])
			continue;

		m_PreviousControllerStates[i] = m_ControllerStates[i];
		result = XInputGetState(DWORD(i), &m_ControllerStates[i]);
		m_ConnectedControllers[i] = (result == ERROR_SUCCESS);
	}

	if (IsTriggered(XINPUT_GAMEPAD_A, TriggerState::pressed, 2))
	{
		std::cout << "Player 2 pressed button\n";
	}

	if (IsTriggered(XINPUT_GAMEPAD_A, TriggerState::pressed, 1))
	{
		std::cout << "Player 1 pressed button\n";
	}
}