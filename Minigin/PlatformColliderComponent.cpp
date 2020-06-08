#include "MiniginPCH.h"
#include "PlatformColliderComponent.h"

divengine::PlatformColliderComponent::PlatformColliderComponent(const glm::vec2& dimensions, const glm::vec2& offset, bool isTrigger, PhysicsMaterial2D* pMaterial)
	:ColliderComponent::ColliderComponent(isTrigger, pMaterial), m_Offset{offset}, m_Rect{glm::vec2(), dimensions.x, dimensions.y}, m_UseOneWay(false)
{
	m_Type = ColliderComponent::ColliderType::platform;
}

bool divengine::PlatformColliderComponent::IsColliding(const Rectf& rect) const
{
	//Check velocity 
	//if (!(velocity.y < 0)) //only calc collision if actor is falling down
	//	return;

	//Check if rect is on top of platform
	if ((rect.bottomLeft.y >= m_Rect.bottomLeft.y + m_Rect.height)
		&& (rect.bottomLeft.y <= m_Rect.bottomLeft.y + m_Rect.height + m_DepthOffset)
		&& (rect.bottomLeft.x + rect.width >= m_Rect.bottomLeft.x)
		&& (rect.bottomLeft.x <= m_Rect.bottomLeft.x + m_Rect.width))
	{
		return true;
	}

	//if not on top, but inside or below, then is not colliding
	return false;
}

bool divengine::PlatformColliderComponent::IsColliding(const Circlef& ) const
{
	//TODO: implement circle on platform collision function
	return false;
}

void divengine::PlatformColliderComponent::Update()
{
}

void divengine::PlatformColliderComponent::Initialize()
{
}

void divengine::PlatformColliderComponent::Render()
{
}
