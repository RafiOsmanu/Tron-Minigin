#pragma once
#include <memory>
#include <vector>
#include "DataTypes.h"

namespace dae
{
	class Texture2D;

	class Bullet final
	{
	public:
		Bullet(float x, float y, float angle, float speed, std::vector<Cube>& cubes, bool isNpc);

		~Bullet() = default;
		Bullet(const Bullet& other) = delete;
		Bullet(Bullet&& other) = delete;
		Bullet& operator=(const Bullet& other) = delete;
		Bullet& operator=(Bullet&& other) = delete;

		void Update(float deltaTime);
		void Render() const;
		void Fire(float angle)
		{
			m_Angle = angle;
			m_IsFired = true;
		}

		bool IsColliding(Cube& mapCube);
		bool IsColliding(glm::vec2 pos, float width, float height);
		//bool IsColliding();
		bool BulletIsDone() const { return m_WallBounceCounter >= 5; }
	private:
		float m_Speed;
		float m_Angle;
		float m_X;
		float m_Y;
		bool m_IsFired;
		std::shared_ptr<Texture2D> m_texture{};
		std::vector<Cube>& m_Cubes;
		int m_WallBounceCounter{ 0 };
	};
}

