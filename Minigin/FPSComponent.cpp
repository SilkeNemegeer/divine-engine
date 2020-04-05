#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Time.h"

dae::FPSComponent::FPSComponent()
	:m_FPS{0}
	,m_MaxTime{0.5f}
	,m_FPSTimer{0.f}
{
}

int dae::FPSComponent::GetFPS() const
{
	return m_FPS;
}

void dae::FPSComponent::Update(float MsPerUpdate)
{
	UNREFERENCED_PARAMETER(MsPerUpdate);
	float elapsed = Time::GetInstance().GetDeltaTime();
	m_FPSTimer += elapsed;
	if (m_FPSTimer >= m_MaxTime)
	{
		m_FPS = int(1.f / Time::GetInstance().GetDeltaTime());

		auto textComp = m_pGameObject->GetComponent<TextComponent>();

		if (textComp)
			textComp->SetText(std::to_string(m_FPS) + " FPS");
		m_FPSTimer = 0.f;
	}
}

void dae::FPSComponent::Render()
{
}
