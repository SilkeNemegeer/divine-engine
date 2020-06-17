#pragma once
#include "ColliderComponent.h"
#include "Structs.h"
#include "PhysicsMaterial2D.h"
namespace divengine
{
	class BoxColliderComponent : public ColliderComponent
	{
		public:
			Rectf m_Rect; 
			BoxColliderComponent(const glm::vec2& dimensions = glm::vec2(), const glm::vec2& offset = glm::vec2(), bool isTrigger = false, int materialId = -1); //Pass an offset, width, height, isTrigger, physcics material (= nullptr) that's all
			virtual bool IsColliding(const Rectf& rect, bool isPlatform = false) const override;
			virtual bool IsColliding(const Circlef& circle) const override;

			virtual glm::vec2 ResolveCollision(const Rectf& rect, float restitution) override;
			virtual glm::vec2 ResolveCollision(const Circlef& circle, float restitution) override;

			virtual void Load(divengine::BinaryReader& reader) override;
			virtual void Save(divengine::BinaryWriter& writer) override;

		protected:
			virtual void Update() override;
			virtual void Initialize() override;
			virtual void Render() override;
			virtual void Start() override;

		private:
			glm::vec2 m_Offset;
	};
}


