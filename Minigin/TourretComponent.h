#pragma once
#include <vector>
#include "BaseComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "DataTypes.h"


namespace dae
{
	class Bullet;

	class TourretComponent final : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit TourretComponent(std::shared_ptr<GameObject> pOwner, std::vector<Cube>& environment, bool autoShoot) 
			: m_pOwner(pOwner), 
			  m_AutoShoot(autoShoot), 
			  m_Environment(environment)
		{
			m_SimpleTourret = true;
		};
		explicit TourretComponent(std::shared_ptr<GameObject> pOwner, std::vector<Cube>& environment,  float width, float height, bool autoShoot)
			: m_pOwner(pOwner), 
			  m_Width(width), 
			  m_Height(height), 
			  m_AutoShoot(autoShoot),
			  m_Environment(environment)
		{
			m_SimpleTourret = false;
		};
		
		TourretComponent(const TourretComponent& other) = delete;
		TourretComponent(TourretComponent&& other) = delete;
		TourretComponent& operator=(const TourretComponent& other) = delete;
		TourretComponent& operator=(TourretComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() override;

		//Methods
		void SetTexture(const std::string& filename);

		void SetAngle(float angle) { m_Angle = angle; }
		void SetMirror(bool mirror) { m_Mirror = mirror; }
		void FireTourret(float angle);
		//void SetEnvironment(std::vector<Cube>& environment) { m_Environment = environment; }
		void SetEnemies(std::vector<std::weak_ptr<GameObject>>& enemys) { m_Enemys = enemys; }
		void AddEnemy(std::weak_ptr<GameObject> enemy) { m_Enemys.push_back(enemy); }

		std::vector<std::shared_ptr<Bullet>> GetBullets() const { return m_Bullets; }
		void DeleteBullet(std::shared_ptr<Bullet> bullet);
		void SetIsDead(bool isDead);
		void SetEnemyCollisionSize(glm::vec2 size) { m_EnemyCollisionSize = size; }

		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
	private:
		//tourret texture variables
		std::shared_ptr<Texture2D> m_texture{};
		float m_Angle{ 0 };
		bool m_Mirror{ false };
		std::string m_TexturePath;

		//tourret variables
		float m_Width{};
		float m_Height{};
		bool m_SimpleTourret{ false };

		//bullet variables
		std::vector<std::shared_ptr<Bullet>> m_Bullets;
		int m_BulletCounter{ 0 };
		float m_FireRate{ 0.35f };
		float m_FireTimer{ 0.f };
		bool m_StartTimer{ false };
		bool m_CanFire{ true };

		//environment + enemies variables
		std::vector<Cube>& m_Environment;
		std::vector<std::weak_ptr<GameObject>> m_Enemys;
		bool HandleEnemyCollision(std::shared_ptr<Bullet> bullet);
		glm::vec2 m_EnemyCollisionSize{ 0,0 };

		//bool for player that owns the tourret is dead
		bool m_IsDead{ false };

		bool m_AutoShoot{ false };
		bool m_InitShot{ true };
	};
}

