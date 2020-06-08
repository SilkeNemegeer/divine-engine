#include "Health.h"

Health::Health(int maxHealth)
	:m_MaxHealth{maxHealth}
	,m_IsDead{false}
	,m_CurrentHealth{maxHealth}
{

}