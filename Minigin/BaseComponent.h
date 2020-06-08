#pragma once
#include "Structs.h"

namespace divengine
{
	class GameObject;

	class BaseComponent
	{
		friend class GameObject;

	public:
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
		BaseComponent();
		virtual ~BaseComponent() = default;

		GameObject* GetGameObject() const;
	protected:
		virtual void Update() = 0;
		virtual void Initialize() = 0;
		virtual void Render() = 0;

		GameObject* m_pGameObject;

	};
}
