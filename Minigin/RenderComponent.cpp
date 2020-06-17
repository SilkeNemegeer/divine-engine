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
#include <fstream>

using namespace divengine;
//
//divengine::RenderComponent::RenderComponent(bool centerPosition, const std::string& filename)
//	:BaseComponent(), m_CenterPosition{ centerPosition }, m_FileName{filename}
//{
//	m_SrcRect = nullptr;
//	m_DestRect = new SDL_Rect();
//}

divengine::RenderComponent::RenderComponent(bool centerPosition)
	:RenderComponent("", centerPosition)
{
}

divengine::RenderComponent::RenderComponent(const std::string& filename, bool centerPosition)
	: RenderComponent(filename.c_str(), centerPosition)
{

}

divengine::RenderComponent::RenderComponent(const char* filename, bool centerPosition)
	:m_CenterPosition{ centerPosition }, m_FileName{ filename }
{
	m_TypeId = unsigned int(ComponentType::rendercomponent);
	m_SrcRect = nullptr;
	m_DestRect = new SDL_Rect();

	if (!m_FileName.empty())
	{
		m_Texture = ServiceLocator::GetResourceManager()->LoadTexture(filename);
		SDL_QueryTexture((*m_Texture).GetSDLTexture(), nullptr, nullptr, &m_DestRect->w, &m_DestRect->h);
	}

	//m_Texture = ServiceLocator::GetResourceManager()->LoadTexture(filename);
	//SDL_QueryTexture((*m_Texture).GetSDLTexture(), nullptr, nullptr, &m_DestRect->w, &m_DestRect->h);
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
	if (m_FileName != "" && !m_Texture)
	{
		m_Texture = ServiceLocator::GetResourceManager()->LoadTexture(m_FileName);
		SDL_QueryTexture((*m_Texture).GetSDLTexture(), nullptr, nullptr, &m_DestRect->w, &m_DestRect->h);
	}
}

void divengine::RenderComponent::PostInitialize()
{
	glm::vec2 offset{};
	if (m_CenterPosition && m_Texture)
	{
		offset.x = -m_Texture->GetWidth() / 2.f;
		offset.y = -m_Texture->GetHeight() / 2.f;
	}

	Vector3 pos = m_pGameObject->GetPosition();
	glm::vec2 newPos(pos.x + offset.x, pos.y + offset.y);
	m_pGameObject->SetPos(newPos);
	SetPosition(newPos);
}

void divengine::RenderComponent::SetTexture(const std::string& filename)
{
	m_FileName = filename;
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
	if (!m_Texture)
	{
		Debug::LogWarning("RenderComponent::GetTextureDimensions: Texture was not found!");
		return Vector2();
	}
	return Vector2(float(m_Texture->GetWidth()), float(m_Texture->GetHeight()));
}

void divengine::RenderComponent::Load(BinaryReader& reader)
{
	//center position
	reader.Read(m_CenterPosition);
	//istream.read((char*)&m_CenterPosition, sizeof(m_CenterPosition));

	////read file name
	reader.Read(m_FileName);
	//size_t size = 0;
	//istream.read((char*)&size, sizeof(size_t));
	//m_FileName.resize(size, ' ');
	//istream.read((char*)&m_FileName[0], sizeof(char) * size);
}

void divengine::RenderComponent::Save(BinaryWriter& writer)
{
	//center position
	//ostream.write((const char*)&m_CenterPosition, sizeof(m_CenterPosition));
	writer.Write(m_CenterPosition);

	////write filename
	writer.Write(m_FileName);
	//size_t size = m_FileName.size();
	//ostream.write((const char*)&size, sizeof(size));
	//ostream.write((const char*)&m_FileName[0], size);

}

void divengine::RenderComponent::Update()
{
	if (!m_Texture)
		return;

	//Update transform
	auto transform = m_pGameObject->GetTransform();
	//glm::vec2 offset{};
	/*if (m_CenterPosition)
	{
		offset.x = m_Texture->GetWidth() /2.f;
		offset.y = m_Texture->GetHeight() / 2.f;*/
	//}
	m_DestRect->x = int(transform->GetPosition().x);
	m_DestRect->y = int(transform->GetPosition().y);

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


