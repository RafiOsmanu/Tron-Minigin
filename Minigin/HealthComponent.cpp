#include "HealthComponent.h"
#include "DataTypes.h"


namespace dae
{

	void HealthComponent::Update()
	{
	}

	void HealthComponent::Render()
	{
	}

	void HealthComponent::LoseLife()
	{
		if (m_CurrentLives >= 1)
		{
			m_CurrentLives -= 1;
			m_pDamage->NotifyObservers(EventType::PlayerDamage);
		}

		if (m_CurrentLives <= 0) m_pDamage->NotifyObservers(EventType::PlayerDied);
	}
}


