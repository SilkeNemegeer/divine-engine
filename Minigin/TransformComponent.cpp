#include "MiniginPCH.h"
#include "TransformComponent.h"

divengine::TransformComponent::TransformComponent(const Vector3& position, float scale)
	:m_Position{position}
	,m_Scale{scale}
{
	m_TypeId = unsigned int(ComponentType::transformcomponent);
}

divengine::TransformComponent::TransformComponent(const glm::vec2& pos, float scale)
	:m_Position{pos.x, pos.y, 0}, m_Scale{scale}
{
	m_TypeId = unsigned int(ComponentType::transformcomponent);
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

void divengine::TransformComponent::Load(BinaryReader& reader)
{
	//position
	//istream.read((char*)&m_Position, sizeof(m_Position));
	reader.Read(m_Position);

	////Scale
	//istream.read((char*)&m_Scale, sizeof(m_Scale));
	reader.Read(m_Scale);
}

void divengine::TransformComponent::Save(BinaryWriter& writer)
{
	//position
	//ostream.write((const char*)&m_Position, sizeof(m_Position));
	writer.Write(m_Position);

	////scale
	//ostream.write((const char*)&m_Scale, sizeof(m_Scale));
	writer.Write(m_Scale);
}
