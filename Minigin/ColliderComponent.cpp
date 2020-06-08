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
divengine::ColliderComponent::ColliderComponent(bool isTrigger, PhysicsMaterial2D* pMaterial)
	:m_IsTrigger{isTrigger}
	,m_Type{ ColliderType::rect}
	,m_pMaterial{pMaterial}
	,m_pRigidbody{nullptr}
{

}

divengine::ColliderComponent::~ColliderComponent()
{
	if (m_pMaterial)
	{
		delete m_pMaterial;
		m_pMaterial = nullptr;
	}
}

void divengine::ColliderComponent::Initialize()
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
	rigidBody->AddCollider(this);
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
		if (pCollider->GetRigidBody()->GetVelocity().y >= 0)
			return IsColliding(platformCollider->m_Rect);
		else
			return false;
		break;
	}
	return false;
}
