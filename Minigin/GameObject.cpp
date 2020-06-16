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
	,m_IsInitialized(false)
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

glm::vec2 divengine::GameObject::GetPos() const
{
	return glm::vec2(m_Transform->GetPosition().x, m_Transform->GetPosition().y);
}

void divengine::GameObject::SetPos(const glm::vec2& pos)
{
	m_Transform->SetPosition(pos.x, pos.y, 0);
}

void divengine::GameObject::SetPos(float x, float y)
{
	SetPos(glm::vec2(x, y));
}

float divengine::GameObject::GetScale() const
{
	return m_Transform->GetScale();
}

divengine::TransformComponent* divengine::GameObject::GetTransform() const
{
	return m_Transform;
}

void divengine::GameObject::AddComponent(BaseComponent* pComponent, bool initOnCreation)
{
	if (pComponent)
	{
		//Check if gameobject does not have the component yet
		for (BaseComponent* component : m_pComponents)
		{
			if (component == pComponent)
			{
				//throw std::exception("GameObject.h: Tried to add component that GameObject already had");
				return;
			}
		}
		m_pComponents.push_back(pComponent);
		pComponent->m_pGameObject = this;
		if (initOnCreation)
			pComponent->Initialize();
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
	if (m_IsInitialized)
		return;

	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Initialize();
	}

	for (BaseComponent* component : m_pComponents)
	{
		component->PostInitialize();
	}

	m_IsInitialized = true;
}
