#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Time.h"

divengine::FPSComponent::FPSComponent()
	:m_FPS{0}
	,m_MaxTime{0.5f}
	,m_FPSTimer{0.f}
	,m_pTextComponent{nullptr}
{
}

int divengine::FPSComponent::GetFPS() const
{
	return m_FPS;
}

void divengine::FPSComponent::Update()
{
	if (m_pTextComponent)
		m_pTextComponent->SetText(std::to_string(Time::GetInstance().GetFps()) + " FPS");
}

void divengine::FPSComponent::Initialize()
{
	m_pTextComponent = m_pGameObject->GetComponent<TextComponent>();
}

void divengine::FPSComponent::Render()
{
}
