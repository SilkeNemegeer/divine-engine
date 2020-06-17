#include "ItemBehaviour.h"
#include "GameObject.h"
#include "PlayerController.h"
#include "SceneManager.h"
#include "Scene.h"

ItemBehaviour::ItemBehaviour(float score)
	:m_Score{score}
{
}

void ItemBehaviour::OnTriggerEnter(divengine::GameObject* pCollider)
{
	if (strcmp(pCollider->GetTag().c_str(), "Player") == 0)
	{
		auto player = pCollider->GetComponent<PlayerController>();
		player->AddToScore(m_Score);
		std::cout << "Picked up item\n";
		divengine::SceneManager::GetInstance().GetCurrentScene()->DestroyObject(m_pGameObject);
	}
}

void ItemBehaviour::Update()
{
}

void ItemBehaviour::Initialize()
{
}
