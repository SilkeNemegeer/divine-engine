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
#include "Health.h"
#include "TextComponent.h"
#include "BaseGame.h"

PlayerController::PlayerController(int id)
	:m_PlayerId{id}
	,m_pRigidbody{nullptr}
	,m_pAnimator{nullptr}
	,m_IsFacingLeft{false}
	,m_MaxAttackTime{0.4f}
	,m_CurrentAttackTime{0.f}
	,m_CurrentState{State::idle}
	,m_FireBubbleForce{100.f}
	,m_pHealth{nullptr}
	,m_MaxLives{4}
	,m_TotalRespawnTime{1.5f}
	,m_CurrentDeadTime{0.f}
	,m_Score{0.f}
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
		m_CurrentDeadTime += Time::GetInstance().GetDeltaTime();
		if (m_CurrentDeadTime > m_TotalRespawnTime)
		{
			if (m_MaxLives <= 0)
			{
				//End level -> display end menu (check game mode to see who won, ...)
				std::cout << "Game Over\n";
				divengine::SceneManager::GetInstance().SetAsCurrentScene("MainMenu");
				m_MaxLives = 4;
				return;
			}
			std::cout << "die\n";
			m_pHealth->ResetHealth();
			m_pGameObject->SetPos(glm::vec2(250, 50));
			m_pRigidbody->ClearForce();
			m_pRigidbody->SetVelocity(glm::vec2(0.f, 0.f));
			ChangeState(State::idle);
		}
		break;
	default:
		break;
	}

	auto pos = m_pGameObject->GetPosition();
	//if fall through bottom screen -> reappear at top
	if ( pos.y > divengine::BaseGame::GetGameSettings().Height)
	{
		m_pGameObject->SetPosition(pos.x, 0.f);
	}
}

void PlayerController::Initialize()
{
	m_pGameObject->SetTag("Player");

	//Create animations
	m_pAnimator = m_pGameObject->GetComponent<divengine::Animator>();
	if (!m_pAnimator)
	{
		divengine::Debug::LogError("No rigidbody found in player");
		return;
	}
	m_pAnimator->AddAnimation(new divengine::AnimationClip(2, 0, 2, "MoveLeft", 3), CharacterAnimations::moveLeft); //TODO: change strings to ints
	m_pAnimator->AddAnimation(new divengine::AnimationClip(0, 0, 2, "MoveRight", 3), CharacterAnimations::moveRight);
	m_pAnimator->AddAnimation(new divengine::AnimationClip(2, 0, 1, "IdleLeft", 1), CharacterAnimations::idleLeft); //TODO: change strings to ints
	m_pAnimator->AddAnimation(new divengine::AnimationClip(0, 0, 1, "IdleRight", 1), CharacterAnimations::idleRight);
	m_pAnimator->AddAnimation(new divengine::AnimationClip(4, 0, 2, "AttackRight", 5), CharacterAnimations::attackRight);
	m_pAnimator->AddAnimation(new divengine::AnimationClip(6, 0, 2, "AttackLeft", 3), CharacterAnimations::attackLeft);
	m_pAnimator->AddAnimation(new divengine::AnimationClip(8, 0, 4, "Dead", 5), CharacterAnimations::inBubble);
	m_pAnimator->SetAnimation(CharacterAnimations::idleLeft);
	m_IsFacingLeft = true;
	m_pAnimator->Play();
//	m_pAnimator->SetAnimation("IdleLeft");
	m_IsFacingLeft = true;
	//m_pAnimator->Play();
}

void PlayerController::Start()
{
	//Set rigidbody
	m_pRigidbody = m_pGameObject->GetComponent<divengine::RigidbodyComponent>();
	if (!m_pRigidbody)
	{
		divengine::Debug::LogWarning("No rigidbody found in player");
		m_pRigidbody = new divengine::RigidbodyComponent();
		m_pGameObject->AddComponent(m_pRigidbody);
	}

	//Set health
	m_pHealth = m_pGameObject->GetComponent<Health>();
	if (!m_pHealth)
	{
		divengine::Debug::LogWarning("No health component found in player");
		m_pHealth = new Health(m_MaxLives);
		m_pGameObject->AddComponent(m_pHealth);
	}
	m_pHealth->SetDeathCallback([this]()
		{
			Die();
		});

	m_pHealth->ResetHealth();
	m_pGameObject->SetPos(glm::vec2(250, 50));
	m_pRigidbody->ClearForce();
	m_pRigidbody->SetVelocity(glm::vec2(0.f, 0.f));
	ChangeState(State::idle);
}

void PlayerController::MoveLeft()
{
	if (!m_pRigidbody || m_CurrentState == State::dead)
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
	if (!m_pRigidbody || m_CurrentState == State::dead)
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
	if (!m_pRigidbody || m_CurrentState == State::dead)
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
	if (m_CurrentState == State::dead)
		return;
	divengine::Debug::Log("Attack");
	ChangeState(State::attack);
}

void PlayerController::SetAnimation(State anim)
{
	switch (anim)
	{
	case PlayerController::State::walkLeft:
			//m_pAnimator->SetAnimation("MoveLeft");
		m_pAnimator->SetAnimation(CharacterAnimations::moveLeft);

		break;
	case PlayerController::State::walkRight:
		//m_pAnimator->SetAnimation("MoveRight");
		m_pAnimator->SetAnimation(CharacterAnimations::moveRight);

		break;

	case PlayerController::State::idle:
		if (m_IsFacingLeft)
			m_pAnimator->SetAnimation(CharacterAnimations::idleLeft);
			//m_pAnimator->SetAnimation("IdleLeft");
		else
			m_pAnimator->SetAnimation(CharacterAnimations::idleRight);
			//m_pAnimator->SetAnimation("IdleRight");
		break;
	case PlayerController::State::attack:
		if (m_IsFacingLeft)
			m_pAnimator->SetAnimation(CharacterAnimations::attackLeft);
			//m_pAnimator->SetAnimation("AttackLeft");
		else
			m_pAnimator->SetAnimation(CharacterAnimations::attackRight);
			//m_pAnimator->SetAnimation("AttackRight");
		break;
	case PlayerController::State::dead:
		m_pAnimator->SetAnimation(CharacterAnimations::inBubble);
		//m_pAnimator->SetAnimation("Dead");
		break;
	default:
		break;
	}
}

void PlayerController::Die()
{
	m_MaxLives -= 1;
	m_CurrentDeadTime = 0.f;
	if(m_MaxLives > 0)
		m_pGameObject->SetPos(glm::vec2(250, 50));
	ChangeState(PlayerController::State::dead);
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
	//animator->AddAnimation(new AnimationClip(0, 12, 2, "GreenBubbles"));
	animator->AddAnimation(new AnimationClip(0, 12, 2, "GreenBubbles"), 0);
	//animator->AddAnimation(new AnimationClip(2, 12, 2, "BlueBubbles"));
	animator->Play();
	pBubble->AddComponent(animator);

	SceneManager::GetInstance().GetCurrentScene()->AddObject(pBubble);
	pBubble->Initialize();
	pBubble->Start();
}
