#include "EnemyBehaviour.h"
#include "GameObject.h"
#include "Time.h"
#include "Health.h"
#include "RigidbodyComponent.h"

EnemyBehaviour::EnemyBehaviour(int damage)
	:m_Damage{damage}
	,m_IsInBubble{false}
	,m_CurrentDeathTime{0.f}
	,m_DeathCooldown{1.5f}
{
}

void EnemyBehaviour::PopBubble()
{
	m_IsInBubble = false; 
	m_pHealth->ResetHealth();
}

void EnemyBehaviour::Update()
{
	if (m_IsDead)
	{
		m_CurrentDeathTime += Time::GetInstance().GetDeltaTime();
		if (m_CurrentDeathTime >= m_DeathCooldown)
		{
			Die();
		}
	}
}

void EnemyBehaviour::Initialize()
{
	m_pGameObject->SetTag("Enemy");
	m_pHealth = m_pGameObject->GetComponent<Health>();
	if (!m_pHealth)
	{
		m_pHealth = new Health(1);
		m_pGameObject->AddComponent(m_pHealth);
	}

	m_pHealth->SetDeathCallback([this]() {m_IsInBubble = true; });
}

void EnemyBehaviour::Start()
{
	m_IsInBubble = false;
	m_pHealth->ResetHealth();
}

void EnemyBehaviour::OnCollisionEnter(divengine::GameObject* pCollider)
{
	if (m_IsDead)
		return;

	if (strcmp(pCollider->GetTag().c_str(), "Player") == 0)
	{
		if (!m_IsInBubble)
		{
			Health* pPlayerHealth = pCollider->GetComponent<Health>();
			if (pPlayerHealth)
			{
				pPlayerHealth->Damage(m_Damage);
			}
		}
		else
		{
			//Player hit -> enemy dies -> apply force & kill after some time
			m_IsDead = true;
			auto rigid = m_pGameObject->GetComponent<divengine::RigidbodyComponent>();
			if (rigid)
			{
				auto playerVel = pCollider->GetComponent<divengine::RigidbodyComponent>()->GetVelocity();
				playerVel *= -1;
				rigid->AddForce(playerVel * 30.f);
			}
		}
	}
}