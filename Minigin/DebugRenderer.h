#pragma once
#include "Structs.h"
namespace divengine
{
	class DebugRenderer final
	{
	public:
		static void EnableDebugRendering(bool enable) { m_DebugRenderingEnabled = enable; };

		//Draw functions
		static void DrawRect(const Rectf& rect, const SDL_Color& color);
		static void DrawRect(const SDL_Rect& rect, const SDL_Color& color);
		static void DrawRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		static void DrawRect(const Rectf& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		static void DrawCircle(const Circlef& circle, const SDL_Color& color);
		static void DrawCircle(const Circlef& circle, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int steps = 15);

	private:
		static bool m_DebugRenderingEnabled;
	};
}

