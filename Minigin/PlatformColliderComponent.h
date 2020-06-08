#pragma once
#include "Structs.h"
#include "ColliderComponent.h"
namespace divengine 
{
	class PlatformColliderComponent : public ColliderComponent
	{
	public:

		//If collider is almost entirely above platform top-> collide
		//If colliders body is below platform top -> do not collide
		//Check velocity of other collider
		Rectf m_Rect;
		PlatformColliderComponent(const glm::vec2& dimensions, const glm::vec2& offset = glm::vec2(), bool isTrigger = false, PhysicsMaterial2D* pMaterial = nullptr);
		virtual bool IsColliding(const Rectf& rect) const override; //check if rect is on platform (velocity of rect )
		virtual bool IsColliding(const Circlef& circle) const override; //check if circle is on platform

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() override;

	private:
		//Collider that will check 
		float m_DepthOffset = 15.f;
		bool m_UseOneWay; //use one-way collision or not
		glm::vec2 m_Offset;
	};
}