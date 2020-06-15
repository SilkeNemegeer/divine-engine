#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;

namespace divengine
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& destRect) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& destRect) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

	private:
		SDL_Renderer* m_Renderer{};
	};
}

