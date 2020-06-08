#pragma once
#include "BaseComponent.h"
#include "PhysicsMaterial2D.h"
namespace divengine
{
	struct Rectf;
	struct Circlef;
	class RigidbodyComponent; 
	class ColliderComponent : public BaseComponent
	{
	public:
		enum class ColliderType
		{
			rect,
			circle,
			platform
		};

		ColliderComponent(bool isTrigger = false, PhysicsMaterial2D* pMaterial = nullptr);
		virtual ~ColliderComponent();
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		//ALL possible collider functions, write these in the specific collider component types (it is specific per type)
		virtual bool IsColliding(const Rectf& rect) const = 0;
		virtual bool IsColliding(const Circlef& circle) const = 0;
		virtual bool IsColliding(ColliderComponent* pCollider) const;
		bool IsTrigger() const { return m_IsTrigger; };
		void SetTrigger(bool isTrigger) { m_IsTrigger = isTrigger; };
		ColliderType Type() const { return m_Type; };
		PhysicsMaterial2D* Material() const { return m_pMaterial; };
		RigidbodyComponent* GetRigidBody() const { return m_pRigidbody; };
	protected:
		virtual void Update() override = 0;
		virtual void Initialize() override;
		virtual void Render() override = 0;

		bool m_IsTrigger;
		PhysicsMaterial2D* m_pMaterial;
		ColliderType m_Type;
		RigidbodyComponent* m_pRigidbody;
	private:
	};
}
