#pragma once
#include "BaseComponent.h"
#include "PhysicsMaterial2D.h"
namespace divengine
{
	struct Rectf;
	struct Circlef;
	//struct PhysicsMaterial2D;
	class RigidbodyComponent; 
	class TransformComponent;
	class ColliderComponent : public BaseComponent
	{
	public:
		enum class ColliderType
		{
			rect,
			circle,
			platform
		};

		struct CollisionInfo
		{
			glm::vec2 PenetrationDepth;
			glm::vec2 Direction;
			//TODO: list of contact points (if you want to add the rotating when hitting corners (rigidbody))
		};

	//	ColliderComponent(bool isTrigger = false, PhysicsMaterial2D* pMaterial = nullptr);
		ColliderComponent(bool isTrigger = false, int materialId = -1);
		virtual ~ColliderComponent();
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) = delete;

		virtual void Load(divengine::BinaryReader& reader) override;
		virtual void Save(divengine::BinaryWriter& writer) override;

		//ALL possible collider functions, write these in the specific collider component types (it is specific per type)
		virtual bool IsColliding(const Rectf& rect, bool isPlatform = false) const = 0;
		virtual bool IsColliding(const Circlef& circle) const = 0;
		virtual bool IsColliding(ColliderComponent* pCollider) const;

		virtual glm::vec2 ResolveCollision(const Rectf& rect, float restitution) = 0; //Will set the position of this collider to a new pos that doesn't collide
		virtual glm::vec2 ResolveCollision(const Circlef& circle, float restitution)= 0;
		virtual glm::vec2 ResolveCollision(ColliderComponent* pCollider);

		bool IsTrigger() const { return m_IsTrigger; };
		void SetTrigger(bool isTrigger) { m_IsTrigger = isTrigger; };
		ColliderType Type() const { return m_Type; };
		PhysicsMaterial2D* Material() const { return m_pMaterial; };
		RigidbodyComponent* GetRigidBody() const { return m_pRigidbody; };
	protected:
		virtual void Update() override = 0;
		virtual void Initialize() override;
		virtual void Render() override = 0;
		virtual void Start() override;

		bool m_IsTrigger;
		PhysicsMaterial2D* m_pMaterial;
		int m_MaterialId;
		ColliderType m_Type;
		RigidbodyComponent* m_pRigidbody;
		TransformComponent* m_pTransform;
	private:
	};
}
