#include "MaitaBehaviour.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RigidbodyComponent.h"
#include "RenderComponent.h"
#include "BoxColliderComponent.h"
#include "Animator.h"
#include "ItemBehaviour.h"
#include "AnimationsEnum.h"
#include "AnimationClip.h"
#include "Debug.h"
#include "GameComponentType.h"

MaitaBehaviour::MaitaBehaviour(int damage, bool ai)
	:m_pHealth{nullptr}
	,m_pCollider{nullptr}
	,m_pRigidbody{nullptr}
	,m_pAnimator{nullptr}
	, EnemyBehaviour(damage, ai)
{
	m_TypeId = unsigned int(GameComponentType::maitabehaviour);

}

MaitaBehaviour::~MaitaBehaviour()
{

}

void MaitaBehaviour::Load(divengine::BinaryReader& reader)
{
	EnemyBehaviour::Load(reader);
}

void MaitaBehaviour::Save(divengine::BinaryWriter& writer)
{
	EnemyBehaviour::Save(writer);
}

void MaitaBehaviour::Update()
{
	EnemyBehaviour::Update();
}

void MaitaBehaviour::Initialize()
{
	EnemyBehaviour::Initialize();
	m_pAnimator = m_pGameObject->GetComponent<divengine::Animator>();
	if (!m_pAnimator)
	{
		divengine::Debug::LogError("MaitaBehaviour::Initialize: No animator found for maita");
	}
}

void MaitaBehaviour::PostInitialize()
{
	m_pAnimator->AddAnimation(new divengine::AnimationClip(4, 15, 2, "WalkingLeft"), CharacterAnimations::moveLeft);
	m_pAnimator->AddAnimation(new divengine::AnimationClip(2, 15, 2, "WalkingRight"), CharacterAnimations::moveRight);
	m_pAnimator->AddAnimation(new divengine::AnimationClip(6, 15, 4, "InBubble"), CharacterAnimations::inBubble);
	m_pAnimator->Play();
}

void MaitaBehaviour::Start()
{
	EnemyBehaviour::Start();
}

void MaitaBehaviour::Die()
{
	SpawnFrenchFries();
	divengine::SceneManager::GetInstance().GetCurrentScene()->DestroyObject(m_pGameObject);
}

void MaitaBehaviour::SpawnFrenchFries()
{
	using namespace divengine;
	float score = 200;

	GameObject* pFries = new GameObject(m_pGameObject->GetPosition(), 0.5f);
	pFries->AddComponent(new RenderComponent("Items/Bubble_Bobble_item_french_fries.png"));
	pFries->AddComponent(new RigidbodyComponent(true));
	pFries->AddComponent(new BoxColliderComponent(glm::vec2(36, 36), glm::vec2(), true));
	pFries->AddComponent(new ItemBehaviour(score));
	SceneManager::GetInstance().GetCurrentScene()->AddObject(pFries);
	pFries->Initialize();
	pFries->Start();
}
