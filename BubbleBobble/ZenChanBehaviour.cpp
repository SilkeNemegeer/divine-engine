#include "ZenChanBehaviour.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RigidbodyComponent.h"
#include "RenderComponent.h"
#include "BoxColliderComponent.h"
#include "Animator.h"
#include "ItemBehaviour.h"

ZenChanBehaviour::ZenChanBehaviour()
	:m_pHealth{ nullptr }
	, m_pCollider{ nullptr }
	, m_pRigidbody{ nullptr }
	, m_pAnimator{ nullptr }
{
}

ZenChanBehaviour::~ZenChanBehaviour()
{
}

void ZenChanBehaviour::Update()
{
}

void ZenChanBehaviour::Initialize()
{
}

void ZenChanBehaviour::SpawnWaterMelon()
{
	using namespace divengine;
	float score = 200;

	GameObject* pMelon = new GameObject(m_pGameObject->GetPosition());
	pMelon->AddComponent(new RenderComponent("Items/Bubble_Bobble_item_french_fries.png"));
	pMelon->AddComponent(new RigidbodyComponent(true));
	pMelon->AddComponent(new BoxColliderComponent(glm::vec2(36, 36), glm::vec2(), true));
	pMelon->AddComponent(new ItemBehaviour(score));
	SceneManager::GetInstance().GetCurrentScene()->AddObject(pMelon);
}
