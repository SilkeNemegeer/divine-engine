#include "Health.h"
#include "GameComponentType.h"

Health::Health(int maxHealth)
	:m_MaxHealth{maxHealth}
	,m_IsDead{false}
	,m_CurrentHealth{maxHealth}
{
	m_TypeId = unsigned int(GameComponentType::health);

}

void Health::Load(divengine::BinaryReader& reader)
{
	reader.Read(m_MaxHealth);
	reader.Read(m_CurrentHealth);
	reader.Read(m_IsDead);
}

void Health::Save(divengine::BinaryWriter& writer)
{
	writer.Write(m_MaxHealth);
	writer.Write(m_CurrentHealth);
	writer.Write(m_IsDead);
}
