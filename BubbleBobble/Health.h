#pragma once
#include "BaseComponent.h"
#include <functional>

class Health : public divengine::BaseComponent
{
public:
	typedef std::function<void()> DeathCallback;
	bool Damage(int damage) //returns true when resulting in death
	{
		m_CurrentHealth -= damage;
		if (m_CurrentHealth <= 0)
		{
			m_CurrentHealth = 0;
			if (!m_IsDead)
				Kill();
			return true;
		}
		return false;
	}

	void Kill()
	{
		if (m_DeathCall)
			m_DeathCall();

		m_IsDead = true;
	}

	int GetHealth() const
	{
		return m_CurrentHealth;
	}

	bool IsDead() const
	{
		return m_IsDead;
	}

	void SetHealth(int newHealth)
	{
		m_CurrentHealth = newHealth;
	}

	void AddHealth(int deltaHealth) //Cannot gain health when you already died
	{
		if (m_IsDead)
			return;

		m_CurrentHealth += deltaHealth;
		if (m_CurrentHealth > m_MaxHealth)
			m_CurrentHealth = m_MaxHealth;
	}

	void ResetHealth()
	{
		m_CurrentHealth = m_MaxHealth;
		m_IsDead = false;
	}

	void SetDeathCallback(DeathCallback callback)
	{
		m_DeathCall = callback;
	}

	Health(const Health& other) = delete;
	Health(Health&& other) noexcept = delete;
	Health& operator=(const Health& other) = delete;
	Health& operator=(Health&& other) noexcept = delete;
	Health(int maxHealth);

	virtual void Initialize() override {};
	virtual void Update() override {};
	virtual void Render() override {};

private:
	const int m_MaxHealth;
	int m_CurrentHealth;
	bool m_IsDead;
	DeathCallback m_DeathCall;
};

