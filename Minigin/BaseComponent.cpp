#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::BaseComponent()
	:m_pGameObject{nullptr}
{
}

dae::GameObject* dae::BaseComponent::GetGameObject() const
{
	return m_pGameObject;
}
