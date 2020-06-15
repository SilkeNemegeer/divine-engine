#include "MiniginPCH.h"
#include "Texture2D.h"
#include "SDL.h"
#include "Debug.h"

int divengine::Texture2D::GetHeight() const
{
	return m_Height;
}

divengine::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* divengine::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

divengine::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
	if (SDL_QueryTexture(texture, nullptr, nullptr, &m_Width, &m_Height) == -1)
	{
		Debug::LogWarning("Texture2D::Texture2D: texture with name was not valid");
	}
}

int divengine::Texture2D::GetWidth() const
{
	return m_Width;
}
