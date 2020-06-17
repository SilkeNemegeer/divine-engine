#include "MaitaBehaviour.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RigidbodyComponent.h"
#include "RenderComponent.h"
#include "BoxColliderComponent.h"
#include "Animator.h"
#include "ItemBehaviour.h"

MaitaBehaviour::MaitaBehaviour()
	:m_pHealth{nullptr}
	,m_pCollider{nullptr}
	,m_pRigidbody{nullptr}
	,m_pAnimator{nullptr}
{
}

MaitaBehaviour::~MaitaBehaviour()
{

}

void MaitaBehaviour::Update()
{

}

void MaitaBehaviour::Initialize()
{

}

void MaitaBehaviour::SpawnFrenchFries()
{
	using namespace divengine;
	float score = 200;

	GameObject* pFries = new GameObject(m_pGameObject->GetPosition());
	pFries->AddComponent(new RenderComponent("Items/Bubble_Bobble_item_french_fries.png"));
	pFries->AddComponent(new RigidbodyComponent(true));
	pFries->AddComponent(new BoxColliderComponent(glm::vec2(36, 36), glm::vec2(), true));
	pFries->AddComponent(new ItemBehaviour(score));
	SceneManager::GetInstance().GetCurrentScene()->AddObject(pFries);
}
