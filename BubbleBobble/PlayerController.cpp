#include "PlayerController.h"
#include "RigidbodyComponent.h"
#include "ColliderComponent.h"
#include "Debug.h"
#include "GameObject.h"
#include "Time.h"
#include "Animator.h"
#include "AnimationClip.h"
#include "SceneManager.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "BubbleBehaviour.h"
#include "CircleColliderComponent.h"

PlayerController::PlayerController(int id)
	:m_PlayerId{id}
	,m_pRigidbody{nullptr}
	,m_pAnimator{nullptr}
	,m_IsFacingLeft{false}
	,m_MaxAttackTime{0.4f}
	,m_CurrentAttackTime{0.f}
	,m_CurrentState{State::idle}
	,m_FireBubbleForce{100.f}
{

}

PlayerController::~PlayerController()
{

}

void PlayerController::Update()
{
	auto vel = m_pRigidbody->GetVelocity();

	switch (m_CurrentState)
	{
	case PlayerController::State::walkLeft:
		if(vel.x > -0.2f)
			ChangeState(PlayerController::State::idle);
		break;
	case PlayerController::State::walkRight:
		if(vel.x < 0.2f)
			ChangeState(PlayerController::State::idle);
		break;
	case PlayerController::State::idle:
		break;
	case PlayerController::State::attack:
		m_CurrentAttackTime += Time::GetInstance().GetDeltaTime();
		if (m_CurrentAttackTime > m_MaxAttackTime)
		{
			ChangeState(State::idle);
			m_CurrentAttackTime = 0.f;
		}
		break;
	case PlayerController::State::dead:
		break;
	default:
		break;
	}
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

	m_pGameObject->SetTag("Player");
	m_pAnimator = m_pGameObject->GetComponent<divengine::Animator>();
	m_pAnimator->AddAnimation(new divengine::AnimationClip(2, 0, 2, "MoveLeft", 3)); //TODO: change strings to ints
	m_pAnimator->AddAnimation(new divengine::AnimationClip(0, 0, 2, "MoveRight", 3));
	m_pAnimator->AddAnimation(new divengine::AnimationClip(2, 0, 1, "IdleLeft", 1)); //TODO: change strings to ints
	m_pAnimator->AddAnimation(new divengine::AnimationClip(0, 0, 1, "IdleRight", 1));
	m_pAnimator->AddAnimation(new divengine::AnimationClip(4, 0, 2, "AttackRight", 5));
	m_pAnimator->AddAnimation(new divengine::AnimationClip(6, 0, 2, "AttackLeft", 3));
	m_pAnimator->SetAnimation("IdleLeft");
	m_pAnimator->Play();
}

void PlayerController::MoveLeft()
{
	if (!m_pRigidbody)
		return;
	divengine::Debug::Log("MoveLeft");
	m_pRigidbody->AddForce(glm::vec2(-15.f, 0.f));
	m_IsFacingLeft = true;

	if (m_CurrentState == State::attack)
		SetAnimation(m_CurrentState);
	else
		ChangeState(State::walkLeft);
}

void PlayerController::MoveRight()
{
	if (!m_pRigidbody)
		return;
	divengine::Debug::Log("MoveRight");
	m_pRigidbody->AddForce(glm::vec2(15.f, 0.f));
	m_IsFacingLeft = false;

	if (m_CurrentState == State::attack)
		SetAnimation(m_CurrentState);
	else
		ChangeState(State::walkRight);
}

void PlayerController::Jump()
{
	if (!m_pRigidbody)
		return;

	divengine::Debug::Log("Jump");
	if(abs(m_pRigidbody->GetVelocity().y) < 0.2f)
		m_pRigidbody->AddForce(glm::vec2(0.f, -600.f));

	if (m_CurrentState == State::attack)
		SetAnimation(m_CurrentState);
	else
		ChangeState(State::idle);
}

void PlayerController::Attack()
{
	divengine::Debug::Log("Attack");
	ChangeState(State::attack);
}

void PlayerController::SetAnimation(State anim)
{
	switch (anim)
	{
	case PlayerController::State::walkLeft:
			m_pAnimator->SetAnimation("MoveLeft");
		break;
	case PlayerController::State::walkRight:
		m_pAnimator->SetAnimation("MoveRight");
		break;

	case PlayerController::State::idle:
		if (m_IsFacingLeft)
			m_pAnimator->SetAnimation("IdleLeft");
		else
			m_pAnimator->SetAnimation("IdleRight");
		break;
	case PlayerController::State::attack:
		if (m_IsFacingLeft)
			m_pAnimator->SetAnimation("AttackLeft");
		else
			m_pAnimator->SetAnimation("AttackRight");
		break;
	case PlayerController::State::dead:
		break;
	default:
		break;
	}
}

void PlayerController::ChangeState(State newState)
{
	if (newState == m_CurrentState)
		return;

	m_CurrentState = newState;

	//Enter new state
	if (m_CurrentState == State::attack)
	{
		FireBubble();
	}

	SetAnimation(newState);
}

void PlayerController::FireBubble()
{
	using namespace divengine;

	float bubbleWidth = 8.f;
	float spawnOffset = 15.f + bubbleWidth;

	int playerDir = 1; //right
	if (m_IsFacingLeft)
	{
		playerDir = -1;
		spawnOffset -= bubbleWidth;
	}

	auto spawnPos = m_pGameObject->GetPosition();
	spawnPos.x += spawnOffset * playerDir;
	GameObject* pBubble = new GameObject(spawnPos, 1.f);

	auto rigidbody = new RigidbodyComponent();
	auto collider = new CircleColliderComponent(5.f, glm::vec2(8, 8), true, 1);
	collider->SetTrigger(true);
	pBubble->AddComponent(collider);


	rigidbody->AddForce(glm::vec2(playerDir * m_FireBubbleForce, 0));
	pBubble->AddComponent(rigidbody);

	auto behaviour = new BubbleBehaviour();
	pBubble->AddComponent(behaviour);

	auto animator = new Animator("sprites.png", 16,16);
	//animator->AddAnimation(new AnimationClip(0, 10, 2, "GreenBubbles"));
	animator->AddAnimation(new AnimationClip(2, 12, 2, "BlueBubbles"));
	animator->Play();
	pBubble->AddComponent(animator);

	SceneManager::GetInstance().GetCurrentScene()->AddObject(pBubble);
	pBubble->Initialize();
}
