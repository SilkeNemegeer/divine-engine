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
#include "Debug.h"
float divengine::RigidbodyComponent::m_Gravity = -9.81f;

divengine::RigidbodyComponent::RigidbodyComponent(bool isStatic)
	:m_IsStatic{isStatic}
	,m_IsKinematic{false}
	,m_Mass{1.f}
	,m_pColliderComp{nullptr}
	, m_Velocity{ 0, 0}
	
{
	m_TypeId = int(ComponentType::rigidbodycomponent);
}

divengine::RigidbodyComponent::~RigidbodyComponent()
{

}

void divengine::RigidbodyComponent::Load(divengine::BinaryReader& reader)
{
	reader.Read(m_Velocity);
	reader.Read(m_Acceleration);
	reader.Read(m_Force);
	reader.Read(m_Mass);

	reader.Read(m_IsKinematic);
	reader.Read(m_IsStatic);
	
	//Collider component takes care of linking rigidbody already
}

void divengine::RigidbodyComponent::Save(divengine::BinaryWriter& writer)
{
	writer.Write(m_Velocity);
	writer.Write(m_Acceleration);
	writer.Write(m_Force);
	writer.Write(m_Mass);

	writer.Write(m_IsKinematic);
	writer.Write(m_IsStatic);
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

void divengine::RigidbodyComponent::SetCollider(ColliderComponent* collider)
{
	m_pColliderComp = collider;
}

void divengine::RigidbodyComponent::RemoveCollider(ColliderComponent* collider)
{
	auto it = std::find(m_pCollidingObjects.begin(), m_pCollidingObjects.end(), collider);
	if (it == m_pCollidingObjects.end())
	{
		return;
	}

	m_pCollidingObjects.erase(it);
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
		m_Force = glm::vec2();

		float dragForce = 1.f;
		auto pMaterial = m_pColliderComp->Material();
		if (pMaterial)
			dragForce = pMaterial->Friction;

		//m_Acceleration
		m_Acceleration.x -= dragForce * m_Velocity.x;
		m_Acceleration.y -= dragForce * m_Velocity.y;

		HandleCollisions();

		m_Velocity += m_Acceleration * Time::GetInstance().GetDeltaTime();

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

void divengine::RigidbodyComponent::PostInitialize()
{

}

void divengine::RigidbodyComponent::HandleCollisions()
{
	if (!m_pColliderComp)
		return;

	glm::vec2 maxPenetration{0.f, 0.f}; //absX & absY
	glm::vec2 penetration{};

	//Use smallest restitution
	float XRestitution = 1.f;
	float YRestitution = 1.f;
	bool isColliding = false;
	for (auto& collider : SceneManager::GetInstance().GetCurrentScene()->GetColliders()) //check for new colliders
	{
		if (collider == m_pColliderComp)
			continue;

		if (m_pColliderComp->IsColliding(collider))
		{
			if (!collider->IsTrigger() && !m_pColliderComp->IsTrigger())
			{
				isColliding = true;
				penetration = m_pColliderComp->ResolveCollision(collider);
				auto material = collider->Material();
				float bounciness = 0.f;
				if (material)
				{
					bounciness = collider->Material()->Bounciness;
				}
				if (penetration.x > maxPenetration.x)
				{
					XRestitution = bounciness;
					maxPenetration.x = penetration.x;
				}
				if (penetration.y > maxPenetration.y)
				{
					YRestitution = bounciness;
					maxPenetration.y = penetration.y;
				}
			}
			NotifyCollisions(collider);

		}
	}

	if (isColliding)
	{
		if (abs(maxPenetration.x - maxPenetration.y) < 0.4f) //Corner
		{
			//Set the velocity according to the resolve collision
			if (rand() % 2)
			{
				m_Velocity.x = -m_Velocity.x * XRestitution;

				if (abs(m_Velocity.x) < 0.004f)
					m_Velocity.x = 0.f;
			}
			else
			{
				m_Velocity.y = -m_Velocity.y * YRestitution;
				if (abs(m_Velocity.y) < 0.004f)
					m_Velocity.y = 0;
			}
		}
		else if (maxPenetration.x > maxPenetration.y) //horizontal penetration
		{
		m_Velocity.x = -m_Velocity.x * XRestitution;

		if (abs(m_Velocity.x) < 0.004f)
			m_Velocity.x = 0.f;
		}
		else //vertical penetration
		{
		m_Velocity.y = -m_Velocity.y * YRestitution; 
		if (abs(m_Velocity.y) < 0.004f)
			m_Velocity.y = 0;
		}
	}

}

void divengine::RigidbodyComponent::NotifyCollisions(ColliderComponent* pCollider)
{
	//If it is a trigger -> call trigger
	auto other = pCollider->GetGameObject();
	if (std::find(m_pCollidingObjects.begin(), m_pCollidingObjects.end(), pCollider) == m_pCollidingObjects.end())
	{
		//Is not in there yet
		if (pCollider->IsTrigger() || m_pColliderComp->IsTrigger())
		{
			m_pGameObject->OnTriggerEnter(other);
			other->OnTriggerEnter(m_pGameObject);
		}
		else
		{
			m_pGameObject->OnCollisionEnter(other);
			other->OnCollisionEnter(m_pGameObject);
		}

		m_pCollidingObjects.insert(pCollider);

	}
	else
	{
		if (pCollider->IsTrigger() || m_pColliderComp->IsTrigger())
		{
			m_pGameObject->OnTriggerStay(other);
			other->OnTriggerStay(m_pGameObject);
		}
		else
		{
			m_pGameObject->OnCollisionStay(other);
			other->OnCollisionStay(m_pGameObject);
		}

	}
}

void divengine::RigidbodyComponent::UpdateCollidingObjects()
{
	if (!m_pColliderComp)
		return;

	auto it = m_pCollidingObjects.begin();


	while (it != m_pCollidingObjects.end())
	{

		if (!(*it)->GetGameObject()) //Check if queued for removal (to be removed from colliding objects) -> if so -> exit & erase
		{
			it = m_pCollidingObjects.erase(it);
		}
		else if (!(*it)->GetGameObject()->IsActive())
		{
			it = m_pCollidingObjects.erase(it);
		}
		else if (!(*it)->IsColliding(m_pColliderComp)) //Instead of checking if you are colliding, keep track with bool array if they are still found when in colliders update
		{
			auto other = (*it)->GetGameObject();
			if (m_pColliderComp->IsTrigger() || (*it)->IsTrigger())
			{
				m_pGameObject->OnTriggerExit(other);
				other->OnTriggerExit(m_pGameObject);
			}
			else
			{
				other->OnCollisionExit(m_pGameObject);
				m_pGameObject->OnCollisionExit(other);
			}
			it = m_pCollidingObjects.erase(it);
		}
		else
		{
			++it;
		}
	}

}
