#include "PlayerController.h"
#include "RigidbodyComponent.h"
#include "ColliderComponent.h"
#include "Debug.h"
#include "GameObject.h"

PlayerController::PlayerController(int id)
	:m_PlayerId{id}
	,m_pRigidbody{nullptr}
{

}

PlayerController::~PlayerController()
{

}

void PlayerController::Update()
{

}

void PlayerController::Initialize()
{
	m_pRigidbody = m_pGameObject->GetComponent<divengine::RigidbodyComponent>();
	if (!m_pRigidbody)
	{
		divengine::Debug::LogWarning("No rigidbody found in player");
		m_pRigidbody = new divengine::RigidbodyComponent();
		m_pGameObject->AddComponent(m_pRigidbody);
	}
}

void PlayerController::MoveLeft()
{
	divengine::Debug::Log("MoveLeft");

}

void PlayerController::MoveRight()
{
	divengine::Debug::Log("MoveRight");

}

void PlayerController::Jump()
{
	divengine::Debug::Log("Jump");

}

void PlayerController::Attack()
{
	divengine::Debug::Log("Attack");
}
