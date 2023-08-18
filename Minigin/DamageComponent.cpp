#include "DamageComponent.h"
#include <iostream>
#include "TourretComponent.h"
#include "Bullet.h"
#include "EnemyAiComponent.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"



void dae::DamageComponent::Update()
{
}

void dae::DamageComponent::Render()
{
}

bool dae::DamageComponent::LoseLife()
{
	--m_Lives;
	if (m_Lives <= 0) m_IsDead = true;
	if (m_IsDead)
	{
		if (m_Player)
		{
			Engine::ServiceLocator::GetAudioSystem().Play((Engine::SoundId)Engine::Sound::loseGame, 4.f);
		}
		KillOwner();
		return true;
	}
	return false;
}

void dae::DamageComponent::ReviveOwner()
{
	m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->SetIsDead(false);
	m_pOwner.lock().get()->GetComponent<dae::TextureComponent>()->SetIsDead(false);

	if (m_pOwner.lock().get()->GetComponent<dae::TourretComponent>())
	m_pOwner.lock().get()->GetComponent<dae::TourretComponent>()->SetIsDead(false);

	if (!m_Player)
		m_pOwner.lock().get()->GetComponent<dae::EnemyAiComponent>()->SetIsDead(false);

	m_IsDead = false;

	if (m_Player && m_Lives <= 0)
	m_Lives = 4;
	else if (!m_Player)
	m_Lives = 3;
}

void dae::DamageComponent::KillOwner()
{
	m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->SetIsDead(true);
	m_pOwner.lock().get()->GetComponent<dae::TextureComponent>()->SetIsDead(true);

	if(m_pOwner.lock().get()->GetComponent<dae::TourretComponent>())
	m_pOwner.lock().get()->GetComponent<dae::TourretComponent>()->SetIsDead(true);

	if (!m_Player)
		m_pOwner.lock().get()->GetComponent<dae::EnemyAiComponent>()->SetIsDead(true);

	m_IsDead = true;
	if (m_Player && m_Lives > 0) return;
	m_Lives = 0;

	
}


