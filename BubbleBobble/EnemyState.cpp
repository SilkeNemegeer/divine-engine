#include "EnemyState.h"
#include "Animator.h"
#include "EnemyBehaviour.h"
#include "RigidbodyComponent.h"
#include "Time.h"
#include <AnimationsEnum.h>
#include "GameObject.h"
//FOLLOW
EnemyState* FollowState::Update(divengine::RigidbodyComponent* pRigidbody, divengine::Animator* pAnimator, EnemyBehaviour* pEnemyBehaviour, divengine::GameObject* pPlayer)
{
	if (pEnemyBehaviour->IsInbubble())
	{
		return new InBubbleState();
	}

	if (!pPlayer)
	{
		pAnimator->Pause();
		return nullptr;
	}
	else
	{
		pAnimator->Play();
		auto vel = pRigidbody->GetVelocity();
		glm::vec2 dist = pRigidbody->GetPosition() - pPlayer->GetPos();

		glm::vec2 force = glm::vec2();
		//X follow
		if (dist.x > 0.2f) //Move left
		{
			force.x = -0.5f;
			pAnimator->SetAnimation(CharacterAnimations::moveLeft);
		}
		else if(dist.x < -0.2f)//move right
		{
			force.x = 0.5f;
			pAnimator->SetAnimation(CharacterAnimations::moveRight);
		}

		//Y follow if player is a certain amount higher than the enemy
		if (dist.y > 60.f && vel.y < 0.2f && vel.y > -0.2f)
		{
			if (!m_Jumped)
			{
				//Jump
				force.y = -400.f;
				m_Jumped = true;
			}
		}
		pRigidbody->AddForce(force);

	}

	if (m_Jumped)
	{
		m_CurrentJumpCooldown += Time::GetInstance().GetDeltaTime();
		if (m_CurrentJumpCooldown >= m_TotalJumpCooldown)
		{
			m_CurrentJumpCooldown = 0.f;
			m_Jumped = false;
		}
	}

	return nullptr;
}

void FollowState::Enter(divengine::RigidbodyComponent* , divengine::Animator*pAnimator, EnemyBehaviour*)
{
		pAnimator->SetAnimation(CharacterAnimations::moveLeft);
		pAnimator->Pause();
}

//ATTACK

EnemyState* AttackState::Update(divengine::RigidbodyComponent* , divengine::Animator* , EnemyBehaviour*, divengine::GameObject* pPlayer)
{
	if(!pPlayer)
		return new FollowState();

	//if player close enough (raycast) -> call attack from enemy behaviour
	//have attack cooldown
	return nullptr;
}

//IN BUBBLE

EnemyState* InBubbleState::Update(divengine::RigidbodyComponent* pRigidbody, divengine::Animator* , EnemyBehaviour* pEnemyBehaviour, divengine::GameObject* )
{
	float floatForce = float(rand() % 8 + 7);
	float floatForceX = float(rand() % 3);
	floatForceX = (rand() % 2) ? floatForceX : -floatForceX;
	pRigidbody->AddForce(glm::vec2(floatForceX,-floatForce));

	//Set timer, if enough time passes and the enemy still lives -> pop out of bubble state
	m_CurrentBubbleTime += Time::GetInstance().GetDeltaTime();
	if (m_CurrentBubbleTime >= m_MaxBubbleTime)
	{
		pEnemyBehaviour->PopBubble();
		return new FollowState();
	}

	return nullptr;
}

void InBubbleState::Enter(divengine::RigidbodyComponent* , divengine::Animator* pAnimator, EnemyBehaviour*)
{
	pAnimator->SetAnimation(CharacterAnimations::inBubble);
	pAnimator->Play();
	m_CurrentBubbleTime = 0.f;
}
