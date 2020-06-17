#include "HUD.h"
#include "TextComponent.h"
#include "PlayerController.h"
#include "GameObject.h"

HUD::HUD(const std::shared_ptr<divengine::Font>& font, const SDL_Color& color)
	:m_Font{font}, m_Color{color}
{
}

void HUD::LinkPlayer(PlayerController* pPlayer)
{
	m_pPlayer = pPlayer;
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
