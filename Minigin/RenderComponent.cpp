#include "MiniginPCH.h"
#include "Renderer.h"
#include"ResourceManager.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ServiceLocator.h"
#include "Texture2D.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Debug.h"

using namespace divengine;

divengine::RenderComponent::RenderComponent(bool centerPosition)
	:BaseComponent(),m_CenterPosition{centerPosition}
{
	m_SrcRect = nullptr;
	m_DestRect = new SDL_Rect();
}

divengine::RenderComponent::RenderComponent(const std::string& filename, bool centerPosition)
	:RenderComponent(centerPosition)
{
	m_Texture = ServiceLocator::GetResourceManager()->LoadTexture(filename);
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
	if (!m_Texture)
		return;

	if (m_SrcRect)
		Renderer::GetInstance().RenderTexture(*m_Texture, *m_SrcRect, *m_DestRect);
	else
		Renderer::GetInstance().RenderTexture(*m_Texture, *m_DestRect);
}

void divengine::RenderComponent::Initialize()
{
	Vector3 pos = m_pGameObject->GetPosition();
	SetPosition(glm::vec2(pos.x, pos.y));
}

void divengine::RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ServiceLocator::GetResourceManager()->LoadTexture(filename);
	if (SDL_QueryTexture((*m_Texture).GetSDLTexture(),nullptr, nullptr, &m_DestRect->w, &m_DestRect->h) == -1)
	{
		Debug::LogWarning("RenderComponent::SetTexture: texture with name: \'", filename.c_str(), "\' was not valid");
	}
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

void divengine::RenderComponent::SetPosition(const glm::vec2& pos)
{
	m_DestRect->x = int(pos.x);
	m_DestRect->y = int(pos.y);
}

Vector2 divengine::RenderComponent::GetTextureDimensions() const
{
	return Vector2(float(m_Texture->GetWidth()), float(m_Texture->GetHeight()));
}

void divengine::RenderComponent::Update()
{
	if (!m_Texture)
		return;

	//Update transform
	auto transform = m_pGameObject->GetTransform();
	glm::vec2 offset;
	if (m_CenterPosition)
	{
		offset.x = m_Texture->GetWidth() /2.f;
		offset.y = m_Texture->GetHeight() / 2.f;
	}
	m_DestRect->x = int(transform->GetPosition().x - offset.x);
	m_DestRect->y = int(transform->GetPosition().y - offset.y);

	if (m_SrcRect)
	{
		m_DestRect->w = int(m_SrcRect->w * transform->GetScale());
		m_DestRect->h = int(m_SrcRect->h * transform->GetScale());
	}
	else
	{
		m_DestRect->h = int(m_Texture->GetHeight() * transform->GetScale());
		m_DestRect->w = int(m_Texture->GetWidth() * transform->GetScale());
	}
}


