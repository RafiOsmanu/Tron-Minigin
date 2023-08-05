#include "Bullet.h"
#include <cmath>
#include "ResourceManager.h"
#include "Renderer.h"

namespace dae
{
	Bullet::Bullet(float x, float y, float angle, float speed)
		: m_X(x),
		  m_Y(y),
		  m_Angle(angle),
		  m_Speed(speed)
	{
		m_texture = ResourceManager::GetInstance().LoadTexture("Sprites/BulletPlayer.png");
	}

	void Bullet::Update(float deltaTime)
	{
		if (m_IsFired)
		{
			m_X += std::cosf(m_Angle * (static_cast<float>(M_PI) / 180.f)) * m_Speed * deltaTime;
			m_Y += std::sinf(m_Angle * (static_cast<float>(M_PI) / 180.f)) * m_Speed * deltaTime;
		}
	}

	void Bullet::Render() const
	{
		if (m_IsFired)
		{
			Renderer::GetInstance().RenderTexture(*m_texture, m_X, m_Y);
		}
	}
}
