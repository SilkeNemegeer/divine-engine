#pragma once
#include "ColliderComponent.h"
#include "Structs.h"
#include "PhysicsMaterial2D.h"

namespace divengine
{
	class CircleColliderComponent : public ColliderComponent
	{
	public:
		Circlef m_Circle;
		CircleColliderComponent(float radius, const glm::vec2& offset, bool isTrigger = false, PhysicsMaterial2D* pMaterial = nullptr);
		virtual ~CircleColliderComponent();
		virtual bool IsColliding(const Rectf& rect) const override;
		virtual bool IsColliding(const Circlef& circle) const override;

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() override;

	private:
		glm::vec2 m_Offset;
	};
}
