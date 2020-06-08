#include "MiniginPCH.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "BoxColliderComponent.h"
#include "Time.h"
#include "PhysicsMaterial2D.h"

float divengine::RigidbodyComponent::m_Gravity = -9.81f;

divengine::RigidbodyComponent::RigidbodyComponent(bool isStatic)
	:m_IsStatic{isStatic}
	,m_IsKinematic{false}
	,m_Mass{1.f}
	,m_pColliderComp{nullptr}
	, m_Velocity{ 0, 0}
	
{
	
}

void divengine::RigidbodyComponent::SetKinematic(bool isKinematic)
{
	if (m_IsStatic && isKinematic)
	{
		std::cout << "Cannot make a static object kinematic!\n";
		return;
	}
	m_IsKinematic = isKinematic;
}

void divengine::RigidbodyComponent::AddForce(const glm::vec2& force)
{
	m_Force += force;
}

void divengine::RigidbodyComponent::ClearForce()
{
	m_Force = glm::vec2{};
}

void divengine::RigidbodyComponent::AddCollider(ColliderComponent* collider)
{
	m_pColliderComp = collider;
}

void divengine::RigidbodyComponent::Update()
{
	//Update position & velocity
	//Detect collisions
	//Resolve collisions
	m_Acceleration = glm::vec2();
	if (!m_IsStatic && !m_IsKinematic)
	{
		//Only move & check collision for dynamic bodies 
		glm::vec2 force = m_Force / m_Mass; //Apply forces
		m_Acceleration.y = -m_Gravity; 	//Apply gravity
		m_Acceleration += force;
		auto pMaterial = m_pColliderComp->Material();
		if (pMaterial)
		{
			//Apply friction
			glm::vec2 friction = pMaterial->Friction * force;
			m_Force -= friction;

			if (m_Force.x < 0.001f)
				m_Force.x = 0.f;
			if (m_Force.y < 0.001f)
				m_Force.y = 0.1f;
		}
		m_Velocity += m_Acceleration * Time::GetInstance().GetDeltaTime();

		HandleCollisions();
		auto position = m_pGameObject->GetPosition();
		glm::vec2 newPos{ position.x, position.y };
		newPos += m_Velocity;// *Time::GetInstance().GetDeltaTime();

		m_pGameObject->SetPosition(newPos.x, newPos.y, position.z);
	}

	UpdateCollidingObjects();
}

void divengine::RigidbodyComponent::Initialize()
{

}

void divengine::RigidbodyComponent::HandleCollisions()
{
	if (!m_pColliderComp)
		return;

	for (auto& collider : SceneManager::GetInstance().GetCurrentScene()->GetColliders())
	{
		if (collider == m_pColliderComp)
			continue;
		if (m_pColliderComp->IsColliding(collider))
		{
			ResolveCollision(collider);
		}
	}
}

void divengine::RigidbodyComponent::ResolveCollision(ColliderComponent* pCollider)
{
	auto pMaterial = m_pColliderComp->Material();

	if (!pCollider->IsTrigger())
	{
		//Calculate bounce direction & Apply bounciness/restitution
		if (pMaterial)
		{
			m_Velocity *= -pMaterial->Bounciness;
			if (abs(m_Velocity.x) < 0.1f)
			{
				m_Velocity.x = 0.f;
			}

			if (abs(m_Velocity.y) < 0.1f)
			{
				m_Velocity.y = 0.f;
			}
		}
		else //no bounciness
		{
			m_Velocity = glm::vec2(); //set velocity to zero when detecting collision
		}
		return;
	}

	//If it is a trigger -> call trigger
	auto other = pCollider->GetGameObject();
	if(std::find(m_pCollidingObjects.begin(), m_pCollidingObjects.end(), pCollider) == m_pCollidingObjects.end())
	{
		//Is not in there yet
		//-> add new
		m_pGameObject->OnTrigger(m_pGameObject, other, GameObject::TriggerFlag::enter);
		other->OnTrigger(other, m_pGameObject, GameObject::TriggerFlag::enter);
		m_pCollidingObjects.push_back(pCollider);

	}
	else
	{
		m_pGameObject->OnTrigger(m_pGameObject, other, GameObject::TriggerFlag::stay);
		other->OnTrigger(other, m_pGameObject, GameObject::TriggerFlag::stay);
	}
}

void divengine::RigidbodyComponent::UpdateCollidingObjects()
{
	auto it = m_pCollidingObjects.begin();
	while(it != m_pCollidingObjects.end())
	{
		if (!(*it)->IsColliding(m_pColliderComp)) //Instead of checking if you are colliding, keep track with bool array if they are still found when in colliders update
		{
			auto other = (*it)->GetGameObject();

			m_pGameObject->OnTrigger(m_pGameObject, other, GameObject::TriggerFlag::leave);
			other->OnTrigger(other, m_pGameObject, GameObject::TriggerFlag::leave);
			it = m_pCollidingObjects.erase(it);
		}
		else
		{
			++it;
		}
	}
}
