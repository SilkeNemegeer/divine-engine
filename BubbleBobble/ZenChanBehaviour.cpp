#include "ZenChanBehaviour.h"
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

ZenChanBehaviour::ZenChanBehaviour(int damage, bool ai)
	:m_pHealth{ nullptr }
	, m_pCollider{ nullptr }
	, m_pRigidbody{ nullptr }
	, m_pAnimator{ nullptr }
	,EnemyBehaviour(damage, ai)
{
	m_TypeId = unsigned int(GameComponentType::zenchanbehaviour);

}

ZenChanBehaviour::~ZenChanBehaviour()
{
}

void ZenChanBehaviour::Die()
{
	SpawnWaterMelon();
	divengine::SceneManager::GetInstance().GetCurrentScene()->DestroyObject(m_pGameObject);
}

void ZenChanBehaviour::Load(divengine::BinaryReader& reader)
{
	EnemyBehaviour::Load(reader);
}

void ZenChanBehaviour::Save(divengine::BinaryWriter& writer)
{
	EnemyBehaviour::Save(writer);
}

void ZenChanBehaviour::Update()
{
	EnemyBehaviour::Update();
}

void ZenChanBehaviour::Initialize()
{
	EnemyBehaviour::Initialize();

	m_pAnimator = m_pGameObject->GetComponent<divengine::Animator>();
	if (!m_pAnimator)
	{
		divengine::Debug::LogError("ZenChanBehaviour::Initialize: No animator found for zenchan");
	}
}

void ZenChanBehaviour::Start()
{
	EnemyBehaviour::Start();
}

void ZenChanBehaviour::PostInitialize()
{
	m_pAnimator->AddAnimation(new divengine::AnimationClip(2, 4, 2, "WalkingLeft"), CharacterAnimations::moveLeft);
	m_pAnimator->AddAnimation(new divengine::AnimationClip(0, 4, 2, "WalkingRight"), CharacterAnimations::moveRight);
	m_pAnimator->AddAnimation(new divengine::AnimationClip(4, 4, 2, "InBubble"), CharacterAnimations::inBubble);
	m_pAnimator->Play();
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
