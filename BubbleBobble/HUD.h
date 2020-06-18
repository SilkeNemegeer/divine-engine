#pragma once
#include "BaseComponent.h"

namespace divengine
{
	class GameObject;
	class TextComponent;
	class RenderComponent;
	class Font;
}
class PlayerController;

class HUD : public divengine::BaseComponent
{
public:
	HUD(int playerId = 0, const SDL_Color& color = SDL_Color{ 255, 255, 255 });
	~HUD() {};

	HUD(const HUD& other) = delete;
	HUD(HUD&& other) = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD& operator=(HUD&& other) = delete;

	virtual void Load(divengine::BinaryReader& reader) override;
	virtual void Save(divengine::BinaryWriter& writer) override;

protected:
	virtual void Update() override;
	virtual void Render() override {};
	virtual void Initialize() override;
	virtual void Start() override;

private:
	divengine::TextComponent* m_pScore;
	std::shared_ptr<divengine::Font> m_Font;
	SDL_Color m_Color;
	int m_PlayerId;
	PlayerController* m_pPlayer;
};

