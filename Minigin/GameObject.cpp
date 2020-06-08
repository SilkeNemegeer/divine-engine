#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include <algorithm>
#include "TransformComponent.h"

divengine::GameObject::GameObject(const Vector3& position, float scale)
	:m_Transform(new TransformComponent(position, scale))
	,m_Tag{""}
	, m_IsActive(true)
{
	AddComponent(m_Transform);
}

divengine::GameObject::~GameObject()
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

void divengine::GameObject::Update()
{ 
	if (!m_IsActive)
		return;
	//Update all the components
	for (BaseComponent* component : m_pComponents)
	{
		component->Update();
	}
}

void divengine::GameObject::Render() const
{
	if (!m_IsActive)
		return;

	const auto pos = m_Transform->GetPosition();

	for (BaseComponent* component : m_pComponents)
	{
		component->Render();
	}
}

void divengine::GameObject::SetPosition(float x, float y, float z)
{
	m_Transform->SetPosition(x, y, z);
}

void divengine::GameObject::SetPosition(const Vector3& newPos)
{
	m_Transform->SetPosition(newPos);
}

divengine::Vector3 divengine::GameObject::GetPosition() const
{
	return m_Transform->GetPosition();
}

void divengine::GameObject::AddComponent(BaseComponent* pComponent)
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

void divengine::GameObject::RemoveComponent(BaseComponent* pComponent)
{
	if (pComponent)
	{
		auto it = std::find(m_pComponents.begin(), m_pComponents.end(), pComponent);
		m_pComponents.erase(it);
		pComponent->m_pGameObject = nullptr;
	}
}

void divengine::GameObject::OnTrigger(GameObject* trigger, GameObject* other, TriggerFlag flag)
{
	if (m_TriggerCallback)
	{
		m_TriggerCallback(trigger, other, flag);
	}
}

void divengine::GameObject::SetTriggerCallback(TriggerCallback callback)
{
	m_TriggerCallback = callback;
}

void divengine::GameObject::Initialize()
{
	for (BaseComponent* component : m_pComponents)
	{
		component->Initialize();
	}
}
