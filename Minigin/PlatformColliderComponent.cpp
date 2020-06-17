#include "MiniginPCH.h"
#include "PlatformColliderComponent.h"
#include "DebugRenderer.h"
#include "GameObject.h"
#include "RigidbodyComponent.h"

divengine::PlatformColliderComponent::PlatformColliderComponent(const glm::vec2& dimensions, const glm::vec2& offset, bool isTrigger, int materialId)
	:ColliderComponent::ColliderComponent(isTrigger, materialId), m_Offset{offset}, m_Rect{glm::vec2(), dimensions.x, dimensions.y}, m_UseOneWay(false)
{
	m_Type = ColliderComponent::ColliderType::platform;
	m_TypeId = unsigned int(ComponentType::platformcollider);
}

bool divengine::PlatformColliderComponent::IsColliding(const Rectf& rect, bool ) const
{
	//Check velocity 
	if (m_pRigidbody->GetVelocity().y >= 0)
		return false;

	//Check if rect is on top of platform
	if ((rect.bottomLeft.y >= m_Rect.bottomLeft.y + m_Rect.height)
		&& (rect.bottomLeft.y <= m_Rect.bottomLeft.y + m_Rect.height + m_DepthOffset)
		&& (rect.bottomLeft.x + rect.width >= m_Rect.bottomLeft.x)
		&& (rect.bottomLeft.x <= m_Rect.bottomLeft.x + m_Rect.width))
	{
		std::cout << "IsColliding\n";
		return true;
	}

	//if not on top, but inside or below, then is not colliding
	return false;
}

bool divengine::PlatformColliderComponent::IsColliding(const Circlef&  ) const
{
	//TODO: implement circle on platform collision function
	return false;
}

glm::vec2 divengine::PlatformColliderComponent::ResolveCollision(const Rectf& , float )
{
	return glm::vec2();
}

glm::vec2 divengine::PlatformColliderComponent::ResolveCollision(const Circlef& , float )
{
	return glm::vec2();
}

void divengine::PlatformColliderComponent::Load(divengine::BinaryReader& reader)
{
	reader.Read(m_Rect);
	reader.Read(m_Offset);
}

void divengine::PlatformColliderComponent::Save(divengine::BinaryWriter& writer)
{
	writer.Write(m_Rect);
	writer.Write(m_Offset);
}

void divengine::PlatformColliderComponent::Update()
{
}

void divengine::PlatformColliderComponent::Initialize()
{
	ColliderComponent::Initialize();
}



void divengine::PlatformColliderComponent::Render()
{
	DebugRenderer::DrawRect(m_Rect, 0, 0, 255, 255);
}

void divengine::PlatformColliderComponent::Start()
{
	ColliderComponent::Start();
	auto pos = m_pGameObject->GetPosition();
	m_Rect.bottomLeft.x = pos.x + m_Offset.x;
	m_Rect.bottomLeft.y = pos.y + m_Offset.y;
}
