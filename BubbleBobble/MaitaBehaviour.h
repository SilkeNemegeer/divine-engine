#pragma once
#include "BaseComponent.h"

namespace divengine
{
	class ColliderComponent;
	class RigidbodyComponent;
	class Animator;
}

class Health;

class MaitaBehaviour : public divengine::BaseComponent
{
public:
	MaitaBehaviour();
	~MaitaBehaviour();

	MaitaBehaviour(const MaitaBehaviour& other) = delete;
	MaitaBehaviour(MaitaBehaviour&& other) = delete;
	MaitaBehaviour& operator=(const MaitaBehaviour& other) = delete;
	MaitaBehaviour& operator=(MaitaBehaviour&& other) = delete;

protected:
	virtual void Update() override;
	virtual void Render() override {};
	virtual void Initialize() override;

private:
	void SpawnFrenchFries();
	Health* m_pHealth;
	divengine::RigidbodyComponent* m_pRigidbody;
	divengine::ColliderComponent* m_pCollider;
	divengine::Animator* m_pAnimator;
};

