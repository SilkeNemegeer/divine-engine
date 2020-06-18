#include "HUD.h"
#include "TextComponent.h"
#include "PlayerController.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameComponentType.h"

HUD::HUD(int playerId, const SDL_Color& color)
	:m_Color{color}, m_PlayerId{playerId}
{
	m_Font = divengine::ServiceLocator::GetResourceManager()->LoadFont("Fonts/Airstream.ttf", 30);
	m_TypeId = unsigned int(GameComponentType::hud);

}

void HUD::Load(divengine::BinaryReader& reader)
{
	reader.Read(m_PlayerId);
	reader.Read(m_Color);
}

void HUD::Save(divengine::BinaryWriter& writer)
{
	writer.Write(m_PlayerId);
	writer.Write(m_Color);
}

void HUD::Update()
{
	if (!m_pPlayer)
		return;

	m_pScore->SetText("SCORE: " + std::to_string(int(m_pPlayer->GetScore())));
}

void HUD::Initialize()
{
	using namespace divengine;
	m_pScore = new TextComponent("SCORE: 0", m_Font, m_Color);
	m_pGameObject->AddComponent(m_pScore);
}

void HUD::Start()
{
	using namespace divengine;
	for (GameObject* pPlayer : SceneManager::GetInstance().GetCurrentScene()->FindObjectsWithTag("Player"))
	{
		auto controller = pPlayer->GetComponent<PlayerController>();
		if (controller->GetPlayerId() == m_PlayerId)
		{
			m_pPlayer = controller;
			break;
		}
	}
}
