#pragma once
#include <memory>

namespace dae
{
	class Texture2D;

	class Bullet
	{
	public:
		Bullet(float x, float y, float angle, float speed);

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
	private:
		float m_Speed;
		float m_Angle;
		float m_X;
		float m_Y;
		bool m_IsFired;
		std::shared_ptr<Texture2D> m_texture{};
	};
}

