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
		CircleColliderComponent(float radius, const glm::vec2& offset, bool isTrigger = false, int materialId = -1);
		virtual ~CircleColliderComponent();
		virtual bool IsColliding(const Rectf& rect, bool isPlatform = false) const override;
		virtual bool IsColliding(const Circlef& circle) const override;

		virtual glm::vec2 ResolveCollision(const Rectf& rect, float restitution) override;
		virtual glm::vec2 ResolveCollision(const Circlef& circle, float restitution) override;

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() override;
		virtual void Start() override;

	private:
		glm::vec2 m_Offset;
	};
}
