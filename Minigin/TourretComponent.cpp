#include "TourretComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "DeltaTime.h"
#include "Bullet.h"
#include "DamageComponent.h"
#include "ScoreComponent.h"
#include "EnemyAiComponent.h"
#include "ServiceLocator.h"

namespace dae
{
	void TourretComponent::Update()
	{
		if (m_IsDead) return;

		//only happens to npc tourret
		if (m_AutoShoot && m_InitShot)
		{
			FireTourret(m_Angle);
			m_InitShot = false;
		}

		for (auto& bullet : m_Bullets)
		{
			if(!bullet) continue;

			//check if bullet is colliding with enemy
			if (HandleEnemyCollision(bullet)) continue;

			


			bullet->Update(DeltaTime::GetInstance().getDeltaTime());
			if (bullet->BulletIsDone())
			{
				//delete bullet from vector
				DeleteBullet(bullet);
				if(m_AutoShoot) FireTourret(m_Angle);

			}

		}

		

		//if enemy is ai dont check for fire rate 
		if (m_AutoShoot) return;

		if (m_FireTimer < m_FireRate)
		{
			if(m_StartTimer)
			m_FireTimer += DeltaTime::GetInstance().getDeltaTime();
		}
		else
		{
			m_CanFire = true;
			m_StartTimer = false;
			m_FireTimer = 0.f;
		}


	}

	void TourretComponent::Render()
	{
		if (m_IsDead) return;
		const auto& pos = m_pOwner.lock()->GetWorldPosition();

		if (m_SimpleTourret)
		{
			Renderer::GetInstance().RenderTexture(*m_texture, pos.x - 8.f, pos.y - 8.f, m_Angle, m_Mirror);
		}
		else
		{
			Renderer::GetInstance().RenderTexture(*m_texture, pos.x - 18.f, pos.y - 18.f, m_Width, m_Height, m_Angle, m_Mirror);
		}

		for (auto& bullet : m_Bullets)
		{
			bullet->Render();
		}

		/*for (auto& enemy : m_Enemys)
		{
			if (!enemy) return;
			SDL_Rect rect
			{
			   int(enemy.get()->GetLocalPosition().x - m_EnemyCollisionSize.x * 0.35f), 
			   int(enemy.get()->GetLocalPosition().y - m_EnemyCollisionSize.y * 0.35f),
			   (int)m_EnemyCollisionSize.x,
			   (int)m_EnemyCollisionSize.y
			};
		
			Renderer::GetInstance().DrawRect(rect);
		}*/
	}

	void TourretComponent::SetTexture(const std::string& filename)
	{
		m_TexturePath = filename;
		m_texture = ResourceManager::GetInstance().LoadTexture(filename);

	}

	void TourretComponent::FireTourret(float angle)
	{
		if (m_IsDead) return;
		if (!m_CanFire) return;

		m_Angle = angle;
		m_Bullets.push_back(std::make_shared<Bullet>
			(m_pOwner.lock()->GetWorldPosition().x , m_pOwner.lock()->GetWorldPosition().y , m_Angle, 150.f, m_Environment, m_AutoShoot));
		//fire bullet u just created
		m_Bullets.back()->Fire(angle);


		if (m_AutoShoot) return;
		//play shoot sound effect
		Engine::ServiceLocator::GetAudioSystem().Play((Engine::SoundId)Engine::Sound::shoot, 2.f);
        m_StartTimer = true;
		m_CanFire = false;
	}
	void TourretComponent::DeleteBullet(std::shared_ptr<Bullet> bullet)
	{
		m_Bullets.erase(std::remove(m_Bullets.begin(), m_Bullets.end(), bullet), m_Bullets.end());
	}

	void TourretComponent::SetIsDead(bool isDead)
	{
		m_IsDead = isDead;
		if (m_AutoShoot) return;
	}

	bool TourretComponent::HandleEnemyCollision(std::shared_ptr<Bullet> bullet)
	{
		if (!bullet) return false;
		if(m_IsDead) return false;

		for (auto& enemy : m_Enemys)
		{
			if (!enemy.lock()) continue;
			if(enemy.lock().get()->GetComponent<DamageComponent>()->GetIsDead()) continue;

			if (bullet->IsColliding({ enemy.lock().get()->GetLocalPosition().x - m_EnemyCollisionSize.x * 0.35f, enemy.lock().get()->GetLocalPosition().y - m_EnemyCollisionSize.y * 0.35f }
				, m_EnemyCollisionSize.x, m_EnemyCollisionSize.y))
			{
				DeleteBullet(bullet);
				if (m_AutoShoot) FireTourret(m_Angle);
				if (enemy.lock()->GetComponent<DamageComponent>()->LoseLife())
				{
					if (m_AutoShoot) continue;
					//add score to player

					if (!enemy.lock()->GetComponent<EnemyAiComponent>())
					{
						m_pOwner.lock()->GetComponent<ScoreComponent>()->AddScore(300);
						return true;
					}

					if (enemy.lock()->GetComponent<EnemyAiComponent>()->GetEnemyType() == EnemyType::tank)
					{
						m_pOwner.lock()->GetComponent<ScoreComponent>()->AddScore(100);
					}
					else
					{
						m_pOwner.lock()->GetComponent<ScoreComponent>()->AddScore(250);
					}

					return true;
				}
				return true;
			}
		}

		return false;
	}
}
