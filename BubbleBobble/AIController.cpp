#include "AIController.h"
#include "EnemyBehaviour.h"
#include "Debug.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "EnemyState.h"

AIController::AIController(EnemyBehaviour* pEnemy)
	:m_pRigidbody{nullptr}
	,m_pEnemyBehaviour{nullptr}
	,m_pCurrentState{nullptr}
	,m_IsLookingLeft{bool(rand()%2)}
{
	m_pEnemyBehaviour = pEnemy;
}

AIController::~AIController()
{
	if (m_pCurrentState)
	{
		delete m_pCurrentState;
		m_pCurrentState = nullptr;
	}
}

void AIController::Update()
{
	if (!m_pEnemyBehaviour)
		return;

	//Find player that is closest
	divengine::GameObject* pNearestPlayer = nullptr;
	float closestDistance = FLT_MAX;
	if (!m_pPlayers.empty())
	{
		pNearestPlayer = m_pPlayers[0];
		for (auto pPlayer : m_pPlayers)
		{
			float dist = divengine::SquaredDistance(pPlayer->GetPos(), m_pGameObject->GetPos());
			if (dist < closestDistance)
			{
				closestDistance = dist;
				pNearestPlayer = pPlayer;
			}
		}
	}

	//Update fsm
	EnemyState* newState = m_pCurrentState->Update(m_pRigidbody, m_pAnimator, m_pEnemyBehaviour, pNearestPlayer);
	ChangeState(newState);
}

void AIController::Initialize()
{
	if (!m_pEnemyBehaviour)
		divengine::Debug::LogError("No enemy behaviour found for the ai controller!");
}

void AIController::Start()
{
	m_pRigidbody = m_pGameObject->GetComponent<divengine::RigidbodyComponent>();
	if (!m_pRigidbody)
	{
		divengine::Debug::LogWarning("AIController::Start: No rigidbody found");
	}	

	m_pAnimator = m_pGameObject->GetComponent<divengine::Animator>();
	if (!m_pAnimator)
	{
		divengine::Debug::LogWarning("AIController::Start: No animator found");

	}

	//Find all players in the scene
	m_pPlayers = divengine::SceneManager::GetInstance().GetCurrentScene()->FindObjectsWithTag("Player");

	if (!m_pCurrentState)
		m_pCurrentState = new FollowState();
	else
		ChangeState(new FollowState());
}

void AIController::ChangeState(EnemyState* pNewState)
{
	if (pNewState != nullptr)
	{
		delete m_pCurrentState;
		m_pCurrentState = pNewState;
		m_pCurrentState->Enter(m_pRigidbody, m_pAnimator, m_pEnemyBehaviour);
	}
}
