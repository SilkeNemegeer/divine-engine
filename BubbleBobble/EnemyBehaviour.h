#pragma once
#include "BaseComponent.h"
//If colliding with player -> remove life of player
//Has attack function

namespace divengine
{
	class GameObject;
}

class Health;

class EnemyBehaviour : public divengine::BaseComponent
{
	public:
		EnemyBehaviour(int damage = 1, bool ai = true);
		virtual ~EnemyBehaviour() = default;
		virtual void Attack() = 0;
		virtual void Die() = 0;

		bool IsInbubble() const { return m_IsInBubble; };	
		void PopBubble();

		virtual void Load(divengine::BinaryReader& reader) override;
		virtual void Save(divengine::BinaryWriter& writer) override;

protected:
	virtual void Update() override;
	virtual void Render() override {};
	virtual void Initialize() override;
	virtual void Start() override;
	virtual void OnCollisionEnter(divengine::GameObject* pCollider);

private:
	int m_Damage;
	Health* m_pHealth;
	bool m_IsInBubble;

	float m_DeathCooldown;
	float m_CurrentDeathTime;
	bool m_IsDead;
	bool m_IsAI;
};

