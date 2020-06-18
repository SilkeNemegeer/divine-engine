#pragma once
#include "EnemyBehaviour.h"

namespace divengine
{
	class ColliderComponent;
	class RigidbodyComponent;
	class Animator;
}

class Health;
class ZenChanBehaviour : public EnemyBehaviour
{
public:
	ZenChanBehaviour(int damage = 1);
	~ZenChanBehaviour();

	ZenChanBehaviour(const ZenChanBehaviour& other) = delete;
	ZenChanBehaviour(ZenChanBehaviour&& other) = delete;
	ZenChanBehaviour& operator=(const ZenChanBehaviour& other) = delete;
	ZenChanBehaviour& operator=(ZenChanBehaviour&& other) = delete;

	virtual void Attack() {};
	virtual void Die(); 

protected:
	virtual void Update() override;
	virtual void Render() override {};
	virtual void Initialize() override;
	virtual void Start() override;

private:
	void SpawnWaterMelon();
	Health* m_pHealth;
	divengine::RigidbodyComponent* m_pRigidbody;
	divengine::ColliderComponent* m_pCollider;
	divengine::Animator* m_pAnimator;


};

