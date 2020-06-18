#include "EnemyBehaviour.h"
#include "GameObject.h"
#include "Time.h"
#include "Health.h"
#include "RigidbodyComponent.h"
#include "AIController.h"
#include "GameComponentType.h"

EnemyBehaviour::EnemyBehaviour(int damage, bool ai)
	:m_Damage{damage}
	,m_IsInBubble{false}
	,m_CurrentDeathTime{0.f}
	,m_DeathCooldown{1.5f}
	,m_IsAI{ai}
{

}

void EnemyBehaviour::PopBubble()
{
	m_IsInBubble = false; 
	m_pHealth->ResetHealth();
}

void EnemyBehaviour::Load(divengine::BinaryReader& reader)
{
	reader.Read(m_Damage);
	reader.Read(m_IsInBubble);
	reader.Read(m_IsDead);
	reader.Read(m_IsAI);
	reader.Read(m_CurrentDeathTime);
	reader.Read(m_DeathCooldown);
}

void EnemyBehaviour::Save(divengine::BinaryWriter& writer)
{
	writer.Write(m_Damage);
	writer.Write(m_IsInBubble);
	writer.Write(m_IsDead);
	writer.Write(m_IsAI);
	writer.Write(m_CurrentDeathTime);
	writer.Write(m_DeathCooldown);
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

	if (m_IsAI)
	{
		AIController* pAI = m_pGameObject->GetComponent<AIController>();
		if (!pAI)
		{
			pAI = new AIController();
			m_pGameObject->AddComponent(pAI);
		}
		pAI->LinkEnemy(this);
	}
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