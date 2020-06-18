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
	ZenChanBehaviour(int damage = 1, bool ai = true);
	~ZenChanBehaviour();

	ZenChanBehaviour(const ZenChanBehaviour& other) = delete;
	ZenChanBehaviour(ZenChanBehaviour&& other) = delete;
	ZenChanBehaviour& operator=(const ZenChanBehaviour& other) = delete;
	ZenChanBehaviour& operator=(ZenChanBehaviour&& other) = delete;

	virtual void Attack() {};
	virtual void Die(); 

	virtual void Load(divengine::BinaryReader& reader) override;
	virtual void Save(divengine::BinaryWriter& writer) override;

protected:
	virtual void Update() override;
	virtual void Render() override {};
	virtual void Initialize() override;
	virtual void Start() override;
	virtual void PostInitialize() override;

private:
	void SpawnWaterMelon();
	Health* m_pHealth;
	divengine::RigidbodyComponent* m_pRigidbody;
	divengine::ColliderComponent* m_pCollider;
	divengine::Animator* m_pAnimator;


};

