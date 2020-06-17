#include "Button.h"
//#include "ServiceLocator.h"
#include "TextComponent.h"
#include <ServiceLocator.h>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Debug.h"
#include "RenderComponent.h"
//#include "InputManager.h"

Button::Button(const SDL_Color& selectedColor, const SDL_Color& unselectedColor)
	:m_IsSelected{false}
	,m_pTextComponent{nullptr}
	,m_pRenderComponent{nullptr}
	,m_UnselectedColor{unselectedColor}
	,m_SelectedColor{selectedColor}
{
}

Button::~Button()
{

}

void Button::SetSelected(bool isSelected)
{
	m_IsSelected = isSelected;

	if (!m_pTextComponent)
		return;
	if (m_IsSelected)
	{
		m_pTextComponent->SetColor(m_SelectedColor);
	}
	else
	{
		m_pTextComponent->SetColor(m_UnselectedColor);
	}
}

void Button::SetPosition(const glm::vec2& pos)
{
	if(m_pRenderComponent)
		m_pRenderComponent->SetPosition(pos);
}

void Button::Initialize()
{

}

void Button::Update()
{
}

void Button::Start()
{
	using namespace divengine;

	m_pTextComponent = m_pGameObject->GetComponent<TextComponent>();
	if (!m_pTextComponent)
		Debug::LogWarning("Button::Initialize: no textcomponent was found");
	m_pRenderComponent = m_pGameObject->GetComponent<RenderComponent>();
	if (!m_pRenderComponent)
		Debug::LogWarning("Button::Initialize: no rendercomponent was found");


}
