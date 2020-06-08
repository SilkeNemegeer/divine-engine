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
			BoxColliderComponent(const glm::vec2& dimensions, const glm::vec2& offset = glm::vec2(), bool isTrigger = false, PhysicsMaterial2D* pMaterial = nullptr); //Pass an offset, width, height, isTrigger, physcics material (= nullptr) that's all
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


