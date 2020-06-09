#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "Time.h"

using namespace divengine;

divengine::SpriteComponent::SpriteComponent(const std::string& path, float clipWidth, float clipHeight, int nrOfFrames, float animationSpeed)
	:m_NrOfFrames(nrOfFrames)
	,m_AnimationSpeed{animationSpeed}
	,m_EnableAnim{true}
	,m_Path{path}
	,m_pRenderComp{nullptr}
	,destRect{}
	,m_pTransform{nullptr}
{
	srcRect.x = srcRect.y = 0;
	srcRect.y = 64;
	srcRect.w = (int)clipWidth;
	srcRect.h = (int)clipHeight;
	
}

divengine::SpriteComponent::~SpriteComponent()
{

}

void divengine::SpriteComponent::Update()
{
	//update texture
	if (m_EnableAnim)
	{
		srcRect.x = srcRect.w * (int(SDL_GetTicks() / m_AnimationSpeed) % m_NrOfFrames);

		auto pos = m_pTransform->GetPosition();
		destRect.x = (int)pos.x;
		destRect.y = (int)pos.y;
		m_pRenderComp->SetSourceRect(srcRect);
		m_pRenderComp->SetDestRect(destRect);

	}
}

void divengine::SpriteComponent::Initialize()
{
	m_pRenderComp = m_pGameObject->GetComponent<RenderComponent>();
	if (!m_pRenderComp)
	{
		m_pRenderComp = new RenderComponent(m_Path);
		m_pGameObject->AddComponent(m_pRenderComp);
	}

	m_pTransform = m_pGameObject->GetComponent<TransformComponent>();
	if (!m_pTransform)
	{
		m_pTransform = new TransformComponent(Vector3());
		m_pGameObject->AddComponent(m_pTransform);
		std::cout << "SpriteComponent::SpriteComponent: No transform component found\n";
	}

	m_pRenderComp->SetSourceRect(srcRect);

	auto transform = m_pTransform;

	destRect.x = (int)transform->GetPosition().x;
	destRect.y = (int)transform->GetPosition().y;

	destRect.w = int(srcRect.w * transform->GetScale());
	destRect.h = int(srcRect.h * transform->GetScale());

	m_pRenderComp->SetDestRect(destRect);

}

void divengine::SpriteComponent::Render()
{
	
}
