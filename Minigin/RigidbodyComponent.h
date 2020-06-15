#pragma once
#include "BaseComponent.h"
#include <vector>
//will immediately respond to gravity
//if one or more collider component is added, gameobject is moved by the incoming collisions
namespace divengine
{
	class ColliderComponent;
	class TransformComponent;
	class RigidbodyComponent : public divengine::BaseComponent
	{
		static float m_Gravity;
	public:
		RigidbodyComponent(bool isStatic = false);
		virtual ~RigidbodyComponent() = default;
		RigidbodyComponent(const RigidbodyComponent& other) = delete;
		RigidbodyComponent(RigidbodyComponent&& other) = delete;
		RigidbodyComponent& operator=(const RigidbodyComponent& other) = delete;
		RigidbodyComponent& operator=(RigidbodyComponent&& other) = delete;

		virtual bool IsStatic() const { return m_IsStatic; };
		virtual bool IsKinematic() const { return m_IsKinematic; };

		glm::vec2 GetVelocity() const { return m_Velocity; };
		void SetKinematic(bool isKinematic);
		void AddForce(const glm::vec2& force);
		void SetMass(float mass) { if(mass > 0.001f) m_Mass = mass; };
		void ClearForce();
		void AddCollider(ColliderComponent* collider);

	protected:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Render() override {};

	private:
		glm::vec2 m_Velocity;
		glm::vec2 m_Acceleration;
		glm::vec2 m_Force;
		float m_Mass;
		bool m_IsKinematic;
		bool m_IsStatic;
		ColliderComponent* m_pColliderComp;
		void HandleCollisions();
		void ResolveCollision(ColliderComponent* pCollider);
		void UpdateCollidingObjects();


		std::vector<ColliderComponent*> m_pCollidingObjects; //Objects currently colliding with the component
	};
}