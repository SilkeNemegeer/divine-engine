#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

divengine::BaseComponent::BaseComponent()
	:m_pGameObject{nullptr}, m_TypeId{unsigned int(ComponentType::unknown)}
{
}

divengine::GameObject* divengine::BaseComponent::GetGameObject() const
{
	return m_pGameObject;
}
