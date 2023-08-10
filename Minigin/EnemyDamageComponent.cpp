#include "EnemyDamageComponent.h"
#include <iostream>
#include "TourretComponent.h"
#include "Bullet.h"
#include "EnemyAiComponent.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"



void dae::EnemyDamageComponent::Update()
{
	if (m_Lives <= 0) m_IsDead = true;
	if (m_IsDead)
	{
		//delete m_pOwner.lock().get();
		std::cout << "Enemy is dead" << std::endl;
		m_pOwner.lock().get()->GetComponent<dae::CollisionComponent>()->SetIsDead(true);
		m_pOwner.lock().get()->GetComponent<dae::EnemyAiComponent>()->SetIsDead(true);
		m_pOwner.lock().get()->GetComponent<dae::TextureComponent>()->SetIsDead(true);
		m_pOwner.lock().get()->GetComponent<dae::TourretComponent>()->SetIsDead(true);
	}
}

void dae::EnemyDamageComponent::Render()
{
}

//void dae::EnemyDamageComponent::HandleDamage()
//{
//	for (auto& bullet : m_pOwner.lock().get()->GetComponent<dae::TourretComponent>()->GetBullets())
//	{
//		if(!bullet) continue;
//
//		if (bullet.get()->IsColliding(m_pOwner.lock().get()->GetLocalPosition(), m_Width, m_Height))
//		{
//			if (m_IsColliding) continue;
//			--m_Lives;
//			m_IsColliding = true;
//			m_pOwner.lock().get()->GetComponent<dae::TourretComponent>()->DeleteBullet(bullet);
//			break;
//		}
//		else
//		{
//			m_IsColliding = false;
//		}
//	}
//
//	
//
//}
