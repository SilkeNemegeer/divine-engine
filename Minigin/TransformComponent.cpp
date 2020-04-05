#include "MiniginPCH.h"
#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(const Vector3& position)
	:m_Position{position}
{
}

void dae::TransformComponent::SetPosition(const Vector3& pos)
{
	m_Position = pos;
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

dae::Vector3 dae::TransformComponent::GetPosition() const
{
	return m_Position;
}

void dae::TransformComponent::Update(float MsPerUpdate)
{
	UNREFERENCED_PARAMETER(MsPerUpdate);
}

void dae::TransformComponent::Render()
{

}
