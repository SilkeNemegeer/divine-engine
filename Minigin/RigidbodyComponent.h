#pragma once
#include "BaseComponent.h"
#include <vector>
#include <unordered_set>
//will immediately respond to gravity
//if one or more collider component is added, gameobject is moved by the incoming collisions
namespace divengine
{
	class ColliderComponent;
	class RigidbodyComponent : public divengine::BaseComponent
	{
		static float m_Gravity;
	public:
		RigidbodyComponent(bool isStatic = false);
		virtual ~RigidbodyComponent();
		RigidbodyComponent(const RigidbodyComponent& other) = delete;
		RigidbodyComponent(RigidbodyComponent&& other) = delete;
		RigidbodyComponent& operator=(const RigidbodyComponent& other) = delete;
		RigidbodyComponent& operator=(RigidbodyComponent&& other) = delete;

		virtual bool IsStatic() const { return m_IsStatic; };
		virtual bool IsKinematic() const { return m_IsKinematic; };

		virtual void Load(divengine::BinaryReader& istream) override;
		virtual void Save(divengine::BinaryWriter& istream) override;


		glm::vec2 GetVelocity() const { return m_Velocity; };
		void SetKinematic(bool isKinematic);
		void AddForce(const glm::vec2& force);
		void SetMass(float mass) { if(mass > 0.001f) m_Mass = mass; };
		void SetVelocity(const glm::vec2& newVel) { m_Velocity = newVel; };
		void ClearForce();
		void SetCollider(ColliderComponent* collider);
		void RemoveCollider(ColliderComponent* collider);
		ColliderComponent* GetCollider() const { return m_pColliderComp; };
		const glm::vec2& GetPosition() const { return m_Position; };
		void SetPosition(const glm::vec2& pos) { m_Position = pos; };
		std::unordered_set<ColliderComponent*> Colliders() const { return m_pCollidingObjects; };

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void PostInitialize() override;
		virtual void Render() override {};

	private:
		glm::vec2 m_Velocity;
		glm::vec2 m_Acceleration;
		glm::vec2 m_Force;
		float m_Mass;
		bool m_IsKinematic;
		bool m_IsStatic;
		ColliderComponent* m_pColliderComp;
		glm::vec2 m_Position;
		void HandleCollisions();
		void NotifyCollisions(ColliderComponent* pCollider);
		void UpdateCollidingObjects();

		std::unordered_set<ColliderComponent*> m_pCollidingObjects; //Objects currently colliding with the component, set -> cannot add same collider twice
	};
}