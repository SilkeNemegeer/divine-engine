#include "MiniginPCH.h"
#include "DebugRenderer.h"
#include "Renderer.h"

bool divengine::DebugRenderer::m_DebugRenderingEnabled = false;

void divengine::DebugRenderer::DrawRect(const Rectf& rect, const SDL_Color& color)
{
	DrawRect(rect, color.r, color.g, color.b, color.a);
}

void divengine::DebugRenderer::DrawRect(const SDL_Rect& rect, const SDL_Color& color)
{
	DrawRect(rect, color.r, color.g, color.b, color.a);
}

void divengine::DebugRenderer::DrawRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	if (!m_DebugRenderingEnabled)
		return;

	auto renderer = Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawRect(renderer, &rect);
}

void divengine::DebugRenderer::DrawRect(const Rectf& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	if (!m_DebugRenderingEnabled)
		return;

	SDL_Rect sdlRect = RectfToSDLRect(rect);
	DrawRect(sdlRect, r, g, b, a);
}

void divengine::DebugRenderer::DrawCircle(const Circlef& circle, const SDL_Color& color)
{
	DrawCircle(circle, color.r, color.g, color.b, color.a);
}

void divengine::DebugRenderer::DrawCircle(const Circlef& circle, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int steps)
{
	if (!m_DebugRenderingEnabled)
		return;

	auto renderer = Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	float pi = 3.1415f;
	const float deltaAlpha = (pi*2) / steps;
	float alpha{ 0.f };
	glm::vec2 pos{};

	//First point
	glm::vec2 initPos;
	pos.x = (circle.radius * cos(alpha)) + circle.center.x;
	pos.y = (circle.radius * sin(alpha)) + circle.center.y;
	initPos = pos;
	for (int i = 0; i < steps - 1; i++) //diameter
	{
		alpha += deltaAlpha;
		glm::vec2 newPos{};
		newPos.x = (circle.radius * cos(alpha)) + circle.center.x;
		newPos.y = (circle.radius * sin(alpha)) + circle.center.y;
		SDL_RenderDrawLine(renderer, (int)pos.x, (int)pos.y, (int)newPos.x, (int)newPos.y);
		pos = newPos;
	}
	//Attach first point to last point
	SDL_RenderDrawLine(renderer, (int)pos.x, (int)pos.y, (int)initPos.x, (int)initPos.y);
}
