#include "MiniginPCH.h"
#include "Renderer.h"
#include"ResourceManager.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include <SDL_ttf.h>

dae::RenderComponent::RenderComponent()
	:BaseComponent()
{
}

dae::RenderComponent::RenderComponent(const std::string& filename)
	:RenderComponent()
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::Render()
{
	if (m_Texture)
	{
		Vector3 pos = m_pGameObject->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(SDL_Texture* texture)
{
	m_Texture = std::make_shared<Texture2D>(texture);
}

void dae::RenderComponent::Update(float MsPerUpdate)
{
	UNREFERENCED_PARAMETER(MsPerUpdate);

}


