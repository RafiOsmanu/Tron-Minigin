#include "TourretComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "DeltaTime.h"
#include "Bullet.h"

namespace dae
{
	void TourretComponent::Update()
	{
		for (auto& bullet : m_Bullets)
		{
			if(!bullet) continue;

			bullet->Update(DeltaTime::GetInstance().getDeltaTime());
			if (bullet->BulletIsDone())
			{
				//delete bullet from vector
				m_Bullets.erase(std::remove(m_Bullets.begin(), m_Bullets.end(), bullet), m_Bullets.end());
			}
		}

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
	}

	void TourretComponent::SetTexture(const std::string& filename)
	{
		m_TexturePath = filename;
		m_texture = ResourceManager::GetInstance().LoadTexture(filename);

	}

	void TourretComponent::FireTourret(float angle)
	{
		if (!m_CanFire) return;

		m_Angle = angle;
		m_Bullets.push_back(std::make_shared<Bullet>(m_pOwner.lock()->GetWorldPosition().x , m_pOwner.lock()->GetWorldPosition().y , m_Angle, 150.f, m_Environment));
		//fire bullet u just created
		m_Bullets.back()->Fire(angle);

        m_StartTimer = true;
		m_CanFire = false;
	}
}
