#include "MiniginPCH.h"
#include "Renderer.h"
#include"ResourceManager.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include "SDL_ttf.h"

using namespace divengine;

divengine::RenderComponent::RenderComponent()
	:BaseComponent()
{
	m_SrcRect = nullptr;
	m_DestRect = new SDL_Rect();
}

divengine::RenderComponent::RenderComponent(const std::string& filename)
	:RenderComponent()
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	SDL_QueryTexture((*m_Texture).GetSDLTexture(), nullptr, nullptr, &m_DestRect->w, &m_DestRect->h);
}

divengine::RenderComponent::~RenderComponent()
{
	if (m_SrcRect)
	{
		delete m_SrcRect;
		m_SrcRect = nullptr;
	}
	if (m_DestRect)
	{
		delete m_DestRect;
		m_DestRect = nullptr;
	}
}

void divengine::RenderComponent::Render()
{
	if (m_Texture)
	{
		Vector3 pos = m_pGameObject->GetPosition();

		m_DestRect->x = (int)pos.x;
		m_DestRect->y = (int)pos.y;
	
		//SDL_QueryTexture((*m_Texture).GetSDLTexture(), nullptr, nullptr, &m_DestRect->w, &m_DestRect->h);
		Renderer::GetInstance().RenderTexture(*m_Texture, *m_SrcRect, *m_DestRect);
		//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void divengine::RenderComponent::Initialize()
{
	Vector3 pos = m_pGameObject->GetPosition();
	m_DestRect->x = static_cast<int>(pos.x);
	m_DestRect->y = static_cast<int>(pos.y);
}

void divengine::RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	SDL_QueryTexture((*m_Texture).GetSDLTexture(), nullptr, nullptr, &m_DestRect->w, &m_DestRect->h);
}

void divengine::RenderComponent::SetTexture(SDL_Texture* texture)
{
	m_Texture = std::make_shared<Texture2D>(texture);
	SDL_QueryTexture((*m_Texture).GetSDLTexture(), nullptr, nullptr, &m_DestRect->w, &m_DestRect->h);
}

void divengine::RenderComponent::SetSourceRect(SDL_Rect& srcRect)
{
	if (!m_SrcRect)
		m_SrcRect = new SDL_Rect();
	m_SrcRect->x = srcRect.x;
	m_SrcRect->y = srcRect.y;
	m_SrcRect->w = srcRect.w;
	m_SrcRect->h = srcRect.h;
}

void divengine::RenderComponent::SetDestRect(SDL_Rect& destRect)
{
	if (!m_DestRect)
		m_DestRect = new SDL_Rect();
	m_DestRect->x = destRect.x;
	m_DestRect->y = destRect.y;
	m_DestRect->w = destRect.w;
	m_DestRect->h = destRect.h;
}

Vector2 divengine::RenderComponent::GetTextureDimensions() const
{
	int width, height;
	SDL_QueryTexture((*m_Texture).GetSDLTexture(), nullptr, nullptr, &width, &height);
	return Vector2(float(width), float(height));
}

void divengine::RenderComponent::Update()
{
}


