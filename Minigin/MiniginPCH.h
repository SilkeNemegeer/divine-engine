#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>
#include <fstream>

#pragma warning(push)
#pragma warning(disable : 26495)
#include "imgui.h"
#include "imgui_sdl.h"
#pragma warning(pop)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//FMOD library
//www.fmod.org
#pragma warning(push)
#pragma warning(disable: 4505 26812)
#include "fmod.hpp" //Precompiled Header
#include "fmod_errors.h"
#pragma warning(pop)

#include <XInput.h>
#include <SDL.h>

#pragma comment(lib, "fmod_vc.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "fmodL_vc.lib")
#endif

//glm library
#pragma warning(push)
#pragma warning(disable : 4201)
#pragma warning(disable : 26812)
#pragma warning(disable : 26495)
#include "glm/glm.hpp"
#pragma warning(pop)

#pragma region DeleteAndReleaseHelpers
template<class T>
inline void SAFEDELETE(T& toDelete)
{
	if (toDelete != nullptr)
	{
		delete toDelete;
		toDelete = nullptr;
	}
}

template<class T>
inline void SAFERELEASE(T& toRelease)
{
	if (toRelease != nullptr)
	{
		toRelease->Release();
		toRelease = nullptr;
	}
}
#pragma endregion