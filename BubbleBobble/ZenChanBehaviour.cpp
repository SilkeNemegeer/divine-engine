#include "ZenChanBehaviour.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RigidbodyComponent.h"
#include "RenderComponent.h"
#include "BoxColliderComponent.h"
#include "Animator.h"
#include "ItemBehaviour.h"

ZenChanBehaviour::ZenChanBehaviour(int damage)
	:m_pHealth{ nullptr }
	, m_pCollider{ nullptr }
	, m_pRigidbody{ nullptr }
	, m_pAnimator{ nullptr }
	,EnemyBehaviour(damage)
{
}

ZenChanBehaviour::~ZenChanBehaviour()
{
}

void ZenChanBehaviour::Die()
{
	SpawnWaterMelon();
	divengine::SceneManager::GetInstance().GetCurrentScene()->DestroyObject(m_pGameObject);
}

void ZenChanBehaviour::Update()
{
	EnemyBehaviour::Update();
}

void ZenChanBehaviour::Initialize()
{
	EnemyBehaviour::Initialize();
}

void ZenChanBehaviour::Start()
{
	EnemyBehaviour::Start();
}

void ZenChanBehaviour::SpawnWaterMelon()
{
	using namespace divengine;
	float score = 100;

	GameObject* pMelon = new GameObject(m_pGameObject->GetPosition(), 0.5f);
	pMelon->AddComponent(new RenderComponent("Items/Bubble_Bobble_item_french_fries.png"));
	pMelon->AddComponent(new RigidbodyComponent(true));
	pMelon->AddComponent(new BoxColliderComponent(glm::vec2(36, 36), glm::vec2(), true));
	pMelon->AddComponent(new ItemBehaviour(score));
	SceneManager::GetInstance().GetCurrentScene()->AddObject(pMelon);
	pMelon->Initialize();
	pMelon->Start();
}
