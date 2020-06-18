#pragma once
#include "EnemyBehaviour.h"

namespace divengine
{
	class ColliderComponent;
	class RigidbodyComponent;
	class Animator;
}

class Health;

class MaitaBehaviour : public EnemyBehaviour
{
public:
	MaitaBehaviour(int damage = 1);
	~MaitaBehaviour();

	MaitaBehaviour(const MaitaBehaviour& other) = delete;
	MaitaBehaviour(MaitaBehaviour&& other) = delete;
	MaitaBehaviour& operator=(const MaitaBehaviour& other) = delete;
	MaitaBehaviour& operator=(MaitaBehaviour&& other) = delete;

protected:
	virtual void Update() override;
	virtual void Render() override {};
	virtual void Initialize() override;
	virtual void Start() override;

	virtual void Die() override;
	virtual void Attack() override {};

private:
	void SpawnFrenchFries();
	Health* m_pHealth;
	divengine::RigidbodyComponent* m_pRigidbody;
	divengine::ColliderComponent* m_pCollider;
	divengine::Animator* m_pAnimator;
};

