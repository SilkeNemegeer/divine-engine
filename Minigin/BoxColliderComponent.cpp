#include "MiniginPCH.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "SDL.h"
#include "Scene.h"
#include "DebugRenderer.h"
#include "Renderer.h"

divengine::BoxColliderComponent::BoxColliderComponent(const glm::vec2& dimensions, const glm::vec2& offset, bool isTrigger, PhysicsMaterial2D* pMaterial)
	:m_Rect{glm::vec2(), dimensions.x, dimensions.y }
	, ColliderComponent::ColliderComponent(isTrigger, pMaterial)
	,m_Offset{offset}
{
	m_Type = ColliderComponent::ColliderType::rect;
}

bool divengine::BoxColliderComponent::IsColliding(const Rectf& rect) const
{
	//Check x collisions
	if(m_Rect.bottomLeft.x >= rect.bottomLeft.x + rect.width || m_Rect.bottomLeft.x + m_Rect.width < rect.bottomLeft.x)
		return false;

	//Check y collisions
	if (m_Rect.bottomLeft.y >= rect.bottomLeft.y + rect.height || m_Rect.bottomLeft.y + m_Rect.height < rect.bottomLeft.y)
		return false;

	return true;
}

bool divengine::BoxColliderComponent::IsColliding(const Circlef& circle) const
{
	//Calc distance between two center of the shapes
	float halfWidthRect = m_Rect.width / 2.f;
	float halfHeightRect = m_Rect.height / 2.f;
	glm::vec2 dist{};
	dist.x = abs(circle.center.x - (m_Rect.bottomLeft.x + halfWidthRect));
	dist.y = abs(circle.center.y - (m_Rect.bottomLeft.y + halfHeightRect));

	//Compare all sides of the rect with the distance between the two centers
	if (dist.x > (halfWidthRect + circle.radius))
		return false;

	if (dist.y > (halfHeightRect + circle.radius))
		return false;

	if (dist.x <= halfWidthRect)
		return true;

	if (dist.y <= halfHeightRect)
		return true;

	float cornerDist = Square(dist.x - halfWidthRect) + Square(dist.y - halfHeightRect);
	return cornerDist <= Square(circle.radius);
}

void divengine::BoxColliderComponent::Update()
{
	//Set collider position equal to position of object
	//m_Collider.x = 
	auto pos = m_pGameObject->GetPosition();
	m_Rect.bottomLeft.x = pos.x + m_Offset.x;
	m_Rect.bottomLeft.y = pos.y + m_Offset.y;
}

void divengine::BoxColliderComponent::Initialize()
{
	ColliderComponent::Initialize();
	auto pos = m_pGameObject->GetPosition();
	m_Rect.bottomLeft.x = pos.x + m_Offset.x;
	m_Rect.bottomLeft.y = pos.y + m_Offset.y;
}

void divengine::BoxColliderComponent::Render()
{
	DebugRenderer::DrawRect(m_Rect, 255, 0, 0, 255);
}
