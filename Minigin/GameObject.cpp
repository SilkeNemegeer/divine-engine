#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include <algorithm>
#include "TransformComponent.h"

dae::GameObject::GameObject(const Vector3& position)
:m_Transform(new TransformComponent(position))
{
	AddComponent(m_Transform);
}

dae::GameObject::~GameObject()
{
	//delete all the components
	for (BaseComponent* pComponent: m_pComponents)
	{
		if (pComponent)
		{
			delete pComponent;
			pComponent = nullptr;
		}
	}
}

void dae::GameObject::Update(float MsPerUpdate)
{ 
	//Update all the components
	for (BaseComponent* component : m_pComponents)
	{
		component->Update(MsPerUpdate);
	}
}

void dae::GameObject::Render() const
{
	const auto pos = m_Transform->GetPosition();

	for (BaseComponent* component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	m_Transform->SetPosition(x, y, z);
}

void dae::GameObject::SetPosition(const Vector3& newPos)
{
	m_Transform->SetPosition(newPos);
}

dae::Vector3 dae::GameObject::GetPosition() const
{
	return m_Transform->GetPosition();
}

void dae::GameObject::AddComponent(BaseComponent* pComponent)
{
	if (pComponent)
	{
		//Check if gameobject does not have the component yet
		for (BaseComponent* component : m_pComponents)
		{
			if (component == pComponent)
			{
				throw std::exception("GameObject.h: Tried to add component that GameObject already had");
				return;
			}
		}
		m_pComponents.push_back(pComponent);
		pComponent->m_pGameObject = this;
	}
}

void dae::GameObject::RemoveComponent(BaseComponent* pComponent)
{
	if (pComponent)
	{
		auto it = std::find(m_pComponents.begin(), m_pComponents.end(), pComponent);
		m_pComponents.erase(it);
		pComponent->m_pGameObject = nullptr;
	}
}
