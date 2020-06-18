#include "BubbleBehaviour.h"
#include "Time.h"
#include "TransformComponent.h"
#include "BaseGame.h"
#include "RigidbodyComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Health.h"

BubbleBehaviour::BubbleBehaviour()
	:m_MaxLifeTime{2.5f}
	, m_CurrentLifeTimePassed{0.f}
	,m_pTransform{nullptr}
	,m_UpwardsForce{10.f}
	,m_pRigidbody{nullptr}
{
}

void BubbleBehaviour::Update()
{
	m_CurrentLifeTimePassed += Time::GetInstance().GetDeltaTime();
	if (m_CurrentLifeTimePassed >= m_MaxLifeTime)
	{
		m_CurrentLifeTimePassed = 0.f;
		divengine::SceneManager::GetInstance().GetCurrentScene()->DestroyObject(m_pGameObject);
	}
	else 
	{
		auto pos = m_pTransform->GetPosition();
		int width = divengine::BaseGame::GetGameSettings().Width;
		int height = divengine::BaseGame::GetGameSettings().Height;
		if (pos.x < 0.f || pos.x > width || pos.y < 0.f || pos.y > height)
			divengine::SceneManager::GetInstance().GetCurrentScene()->DestroyObject(m_pGameObject);
	}

	m_pRigidbody->AddForce(glm::vec2(0,-m_UpwardsForce));
}

void BubbleBehaviour::Initialize()
{
	m_pGameObject->SetTag("Bubble");
	m_pTransform = m_pGameObject->GetComponent<divengine::TransformComponent>();
	m_pRigidbody = m_pGameObject->GetComponent<divengine::RigidbodyComponent>();
}

void BubbleBehaviour::OnTriggerEnter(divengine::GameObject* trigger)
{
	if (strcmp(trigger->GetTag().c_str(), "Enemy") == 0)
	{		
		//call bubble hit on enemy behaviour component
		auto enemyHealth = trigger->GetComponent<Health>();
		if (enemyHealth)
		{
			enemyHealth->Damage(1);
		}
		divengine::SceneManager::GetInstance().GetCurrentScene()->DestroyObject(m_pGameObject);
	}
}
