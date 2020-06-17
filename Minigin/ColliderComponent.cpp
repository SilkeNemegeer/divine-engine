#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "RigidbodyComponent.h"
#include "Structs.h"
#include "BoxColliderComponent.h"
#include "SceneManager.h"
#include "CircleColliderComponent.h"
#include "PlatformColliderComponent.h"
#include "Scene.h"
#include "MaterialManager.h"
#include "PhysicsMaterial2D.h"
//divengine::ColliderComponent::ColliderComponent(bool isTrigger, PhysicsMaterial2D* pMaterial)
//	:m_IsTrigger{isTrigger}
//	,m_Type{ ColliderType::rect}
//	,m_pMaterial{pMaterial}
//	,m_pRigidbody{nullptr}
//{
//	m_TypeId = unsigned int(ComponentType::collidercomponent);
//}

divengine::ColliderComponent::ColliderComponent(bool isTrigger, int materialId)
	:m_IsTrigger{ isTrigger }
	, m_Type{ ColliderType::rect }
	, m_pMaterial{ nullptr }
	,m_MaterialId{materialId}
	,m_pTransform{nullptr}

	, m_pRigidbody{ nullptr }
{
	m_pMaterial = MaterialManager::GetInstance().GetMaterial(materialId);
	m_TypeId = unsigned int(ComponentType::collidercomponent);
}


divengine::ColliderComponent::~ColliderComponent()
{
	//if (m_pMaterial) //Is done in material manager
	//{
	//	delete m_pMaterial;
	//	m_pMaterial = nullptr;
	//}
	//for (auto pCollider : m_pRigidbody->Colliders())
	//{
	//	pCollider->GetRigidBody()->RemoveCollider(this);
	//}
}

void divengine::ColliderComponent::Initialize()
{

}

void divengine::ColliderComponent::Start()
{
	//add collider to the rigidbody
	auto rigidBody = GetGameObject()->GetComponent<RigidbodyComponent>();
	if (rigidBody == nullptr)
	{
		std::cout << "Can't add collider to object that has no rigidbody!\n";
		return;
	}
	m_pRigidbody = rigidBody;
	SceneManager::GetInstance().GetCurrentScene()->AddCollider(this);
	rigidBody->SetCollider(this);

	m_pTransform = m_pGameObject->GetComponent<TransformComponent>();
}

bool divengine::ColliderComponent::IsColliding(ColliderComponent* pCollider) const
{
	switch (pCollider->Type())
	{
	case ColliderType::rect:	
		{
			auto boxCollider = static_cast<BoxColliderComponent*>(pCollider);
			return IsColliding(boxCollider->m_Rect);
			break;
		}

	case ColliderType::circle:
	{
		auto circleCollider = static_cast<CircleColliderComponent*>(pCollider);
		return IsColliding(circleCollider->m_Circle);
		break;
	}
	case ColliderType::platform:
		//Check the velocity
		auto platformCollider = static_cast<PlatformColliderComponent*>(pCollider);
		return IsColliding(platformCollider->m_Rect, true);
		break;
	}
	return false;
}

glm::vec2 divengine::ColliderComponent::ResolveCollision(ColliderComponent* pCollider)
{
	auto material = pCollider->Material();
	float restitution = 0.005f;
	if (material)
		restitution = material->Bounciness;

	switch (pCollider->Type())
	{
	case ColliderType::rect:
	{
		auto boxCollider = static_cast<BoxColliderComponent*>(pCollider);
		return ResolveCollision(boxCollider->m_Rect, restitution);
		break;
	}

	case ColliderType::circle:
	{
		auto circleCollider = static_cast<CircleColliderComponent*>(pCollider);
		return ResolveCollision(circleCollider->m_Circle, restitution);
		break;
	}
	case ColliderType::platform:
		//Check the velocity
		auto platformCollider = static_cast<PlatformColliderComponent*>(pCollider);
		if (pCollider->GetRigidBody()->GetVelocity().y >= 0)
			return ResolveCollision(platformCollider->m_Rect, restitution);
		break;
	}
	return glm::vec2();
}

void divengine::ColliderComponent::Load(divengine::BinaryReader& reader)
{
	reader.Read(m_IsTrigger);

	m_pRigidbody = m_pGameObject->GetComponent<RigidbodyComponent>(); //Get the rigidbody

	//read material id
	reader.Read(m_MaterialId);
	if (m_MaterialId != -1)
		m_pMaterial = MaterialManager::GetInstance().GetMaterial(m_MaterialId);
	else
		m_pMaterial = nullptr;

	reader.Read(m_Type);
}

void divengine::ColliderComponent::Save(divengine::BinaryWriter& writer)
{
	//No need
	writer.Write(m_IsTrigger);

	//Write material id
	writer.Write(m_MaterialId);

	writer.Write(m_Type);
}