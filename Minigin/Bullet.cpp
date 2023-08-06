#include "Bullet.h"
#include <cmath>
#include "ResourceManager.h"
#include "Renderer.h"

namespace dae
{
	Bullet::Bullet(float x, float y, float angle, float speed, std::vector<Cube>& cubes)
		: m_X(x),
		  m_Y(y),
		  m_Angle(angle),
		  m_Speed(speed),
		  m_Cubes(cubes)
	{
		m_texture = ResourceManager::GetInstance().LoadTexture("Sprites/BulletPlayer.png");
	}

	void Bullet::Update(float deltaTime)
	{
		if (m_IsFired)
		{
			for (auto& cube : m_Cubes)
			{
				if (IsColliding(cube))
				{
					// Calculate the collision point on the cube's surface (assuming cube is centered at (0,0,0))
					float cx = m_X - cube.position.x;
					float cy = m_Y - cube.position.y;

					// Calculate the absolute values of the collision point's coordinates
					float absCX = std::abs(cx);
					float absCY = std::abs(cy);

					// Determine the orientation of the cube's face (aligned with x, y, or z-axis)
					if (absCX > absCY) // x-axis aligned face
					{
						// Reflect the bullet's angle horizontally
						m_Angle = 180.0f - m_Angle;
					}
					else // y-axis aligned face
					{
						// Reflect the bullet's angle vertically
						m_Angle = -m_Angle;
					}
					
					//++m_WallBounceCounter;
					break;
				}

				
			}

			m_X += std::cosf(m_Angle * (static_cast<float>(M_PI) / 180.f)) * m_Speed * deltaTime;
			m_Y += std::sinf(m_Angle * (static_cast<float>(M_PI) / 180.f)) * m_Speed * deltaTime;
		}

		
	}

	void Bullet::Render() const
	{
		if (m_IsFired)
		{
 			Renderer::GetInstance().RenderTexture(*m_texture, m_X, m_Y);
			

			SDL_Rect rect{ int(m_X), int(m_Y), static_cast<int>(10), static_cast<int>(10) };
			Renderer::GetInstance().DrawRect(rect);
		}
	}

	bool Bullet::IsColliding(Cube mapCube)
	{
		// Collision detection
		if (mapCube.cubeType != dae::MapTerrain::wall)
			return false;

		auto cubeRight = mapCube.position.x + mapCube.size;
		auto cubeBottom = mapCube.position.y + mapCube.size;
		auto centerOfBullet = glm::vec2(m_X + m_texture->GetSize().x / 2.f, m_Y + m_texture->GetSize().y / 2.f);
		float bulletRadius = std::max(m_texture->GetSize().x, m_texture->GetSize().y) / 2.f;

		// Check if the bullet's bounding circle collides with the cube
		float closestX = std::max(mapCube.position.x, std::min(centerOfBullet.x, cubeRight));
		float closestY = std::max(mapCube.position.y, std::min(centerOfBullet.y, cubeBottom));
		float distanceX = centerOfBullet.x - closestX;
		float distanceY = centerOfBullet.y - closestY;
		float distanceSquared = distanceX * distanceX + distanceY * distanceY;

		return distanceSquared < (bulletRadius * bulletRadius);
	}
}
