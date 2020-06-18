#pragma once
#include "RigidbodyComponent.h"
#include "Animator.h"

namespace divengine
{
	class GameObject;
}

class EnemyBehaviour;
class EnemyState
{
public:
	virtual ~EnemyState() {};
	virtual EnemyState* Update(divengine::RigidbodyComponent* pRigidbody, divengine::Animator* pAnimator, EnemyBehaviour* pEnemyBehaviour, divengine::GameObject* pPlayer) = 0;
	virtual void Enter(divengine::RigidbodyComponent* pRigidbody, divengine::Animator* pAnimator, EnemyBehaviour* pPlayer) = 0;
};

class FollowState : public EnemyState
{
	public:
	virtual EnemyState* Update(divengine::RigidbodyComponent* pRigidbody, divengine::Animator* pAnimator, EnemyBehaviour* pEnemyBehaviour, divengine::GameObject* pPlayer);
	virtual void Enter(divengine::RigidbodyComponent* pRigidbody, divengine::Animator* pAnimator, EnemyBehaviour* pEnemyBehaviour);

private:
	float m_TotalJumpCooldown = 2.f;
	float m_CurrentJumpCooldown = 0.f;
	bool m_Jumped = false;
};

class AttackState : public EnemyState
{
public:
	virtual EnemyState* Update(divengine::RigidbodyComponent* pRigidbody, divengine::Animator* pAnimator, EnemyBehaviour* pEnemyBehaviour, divengine::GameObject* pPlayer);
	virtual void Enter(divengine::RigidbodyComponent* , divengine::Animator* , EnemyBehaviour*) {};
};

class InBubbleState : public EnemyState
{
public:
	virtual EnemyState* Update(divengine::RigidbodyComponent* pRigidbody, divengine::Animator* pAnimator, EnemyBehaviour* pEnemyBehaviour, divengine::GameObject* pPlayer);
	virtual void Enter(divengine::RigidbodyComponent* pRigidbody, divengine::Animator* pAnimator, EnemyBehaviour* pEnemyBehaviour);

private:
	float m_CurrentBubbleTime = 0.f;
	float m_MaxBubbleTime = 3.f;
};