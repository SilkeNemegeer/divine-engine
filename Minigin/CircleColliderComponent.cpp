#include "MiniginPCH.h"
#include "CircleColliderComponent.h"
#include "DebugRenderer.h"
#include "GameObject.h"
//divengine::CircleColliderComponent::CircleColliderComponent(float radius, const glm::vec2& offset, bool isTrigger, PhysicsMaterial2D* pMaterial)
//	:m_Offset{offset}
//	,m_Circle{glm::vec2(), radius}
//	,ColliderComponent::ColliderComponent(isTrigger, pMaterial)
//{
//	m_Type = ColliderComponent::ColliderType::circle;
//}

divengine::CircleColliderComponent::CircleColliderComponent(float radius, const glm::vec2& offset, bool isTrigger, int materialId)
	:m_Offset{ offset }
	, m_Circle{ glm::vec2(), radius }
	, ColliderComponent::ColliderComponent(isTrigger, materialId)
{
	m_Type = ColliderComponent::ColliderType::circle;
	m_TypeId = unsigned int(ComponentType::circlecollider);
}

divengine::CircleColliderComponent::~CircleColliderComponent()
{

}

bool divengine::CircleColliderComponent::IsColliding(const Rectf& rect, bool ) const
{


	//Calc distance between two center of the shapes
	float halfWidthRect = rect.width / 2.f;
	float halfHeightRect = rect.height / 2.f;
	glm::vec2 dist{};
	dist.x = abs(m_Circle.center.x - (rect.bottomLeft.x + halfWidthRect));
	dist.y = abs(m_Circle.center.y - (rect.bottomLeft.y + halfHeightRect));

	//Compare all sides of the rect with the distance between the two centers
	if (dist.x > (halfWidthRect + m_Circle.radius))
		return false;

	if (dist.y > (halfHeightRect + m_Circle.radius))
		return false;

	if (dist.x <= halfWidthRect)
		return true;

	if (dist.y <= halfHeightRect)
		return true;

	float cornerDist = Square(dist.x - halfWidthRect) + Square(dist.y - halfHeightRect);
	return cornerDist <= Square(m_Circle.radius);
}

bool divengine::CircleColliderComponent::IsColliding(const Circlef& circle) const
{
	return Square(circle.radius + m_Circle.radius) <= Square(circle.center.x - m_Circle.center.x) + Square(circle.center.y - m_Circle.center.y);
}

glm::vec2 divengine::CircleColliderComponent::ResolveCollision(const Rectf& , float )
{
	return glm::vec2();
}

glm::vec2 divengine::CircleColliderComponent::ResolveCollision(const Circlef& , float)
{
	return glm::vec2();
}

void divengine::CircleColliderComponent::Load(divengine::BinaryReader& reader)
{
	//Circle & offset 
	ColliderComponent::Load(reader);
	reader.Read(m_Circle);
	reader.Read(m_Offset);
}

void divengine::CircleColliderComponent::Save(divengine::BinaryWriter& writer)
{
	ColliderComponent::Save(writer);
	writer.Write(m_Circle);
	writer.Write(m_Offset);
}

void divengine::CircleColliderComponent::Update()
{
	auto pos = m_pGameObject->GetPosition();
	m_Circle.center.x = pos.x + m_Offset.x;
	m_Circle.center.y = pos.y + m_Offset.y;
}

void divengine::CircleColliderComponent::Initialize()
{
	ColliderComponent::Initialize();

}

void divengine::CircleColliderComponent::Render()
{
	DebugRenderer::DrawCircle(m_Circle, 255, 0, 0, 255);
}

void divengine::CircleColliderComponent::Start()
{
	ColliderComponent::Start();
	auto pos = m_pGameObject->GetPosition();
	m_Circle.center.x = pos.x + m_Offset.x;
	m_Circle.center.y = pos.y + m_Offset.y;
}
