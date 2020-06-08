#include "MiniginPCH.h"
#include "TransformComponent.h"

divengine::TransformComponent::TransformComponent(const Vector3& position, float scale)
	:m_Position{position}
	,m_Scale{scale}
{
}

void divengine::TransformComponent::SetPosition(const Vector3& pos)
{
	m_Position = pos;
}

void divengine::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

divengine::Vector3 divengine::TransformComponent::GetPosition() const
{
	return m_Position;
}

void divengine::TransformComponent::SetScale(float newScale)
{
	m_Scale = newScale;
}

float divengine::TransformComponent::GetScale() const
{
	return m_Scale;
}

void divengine::TransformComponent::Update()
{
}

void divengine::TransformComponent::Render()
{

}

void divengine::TransformComponent::Initialize()
{
}
