#include "ItemBehaviour.h"
#include "GameObject.h"
#include "PlayerController.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameComponentType.h"

ItemBehaviour::ItemBehaviour(float score)
	:m_Score{score}
{
	m_TypeId = unsigned int(GameComponentType::itembehaviour);
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

void ItemBehaviour::Load(divengine::BinaryReader& reader)
{
	reader.Read(m_Score);
}

void ItemBehaviour::Save(divengine::BinaryWriter& writer)
{
	writer.Write(m_Score);
}

void ItemBehaviour::Update()
{
}

void ItemBehaviour::Initialize()
{
}
