#include "MiniginPCH.h"
#include "Debug.h"
#include <SDL.h>
#include "Renderer.h"

void divengine::Debug::Log(const std::string& text)
{
	std::cout << text << "\n";
}

void divengine::Debug::LogWarning(const char* const text, ...)
{
	std::cout << "WARNING: " << text << "\n";
}


void divengine::Debug::LogError(const std::string& text)
{
	MessageBox(0, text.c_str(), "ERROR", 0);
}
