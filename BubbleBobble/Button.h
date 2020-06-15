#pragma once
#include "BaseComponent.h"
#include <string>
namespace divengine
{
	class TextComponent;
	class RenderComponent;
	class GameObject;
}

class Button : public divengine::BaseComponent
{

public:
	Button(const SDL_Color& selectedColor = SDL_Color{ 0, 0, 0 }, const SDL_Color& unselectedColor= SDL_Color{ 255, 255, 255 });
	~Button();
	Button(const Button& other) = delete;
	Button(Button&& other) noexcept = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other) noexcept = delete;

	void SetSelected(bool isSelected);
	bool IsSelected() const { return m_IsSelected; };
	void SetPosition(const glm::vec2& pos);
	virtual void Initialize() override;
	virtual void Render() override {};
	virtual void Update() override;

private:
	//divengine::GameObject* m_pButton;
	bool m_IsSelected;
	SDL_Color m_UnselectedColor;
	SDL_Color m_SelectedColor;

	divengine::TextComponent* m_pTextComponent;
	divengine::RenderComponent* m_pRenderComponent;
};

