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
		PlatformColliderComponent(const glm::vec2& dimensions, const glm::vec2& offset = glm::vec2(), bool isTrigger = false, int materialId = -1);
		virtual bool IsColliding(const Rectf& rect, bool isPlatform = false) const override; //check if rect is on platform (velocity of rect )
		virtual bool IsColliding(const Circlef& circle) const override; //check if circle is on platform

		virtual glm::vec2 ResolveCollision(const Rectf& rect, float restitution) override;
		virtual glm::vec2 ResolveCollision(const Circlef& circle, float restitution) override;

		virtual void Load(divengine::BinaryReader& reader) override;
		virtual void Save(divengine::BinaryWriter& writer) override;
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