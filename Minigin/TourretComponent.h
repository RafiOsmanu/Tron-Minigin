#pragma once
#include <vector>
#include "BaseComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "DataTypes.h"


namespace dae
{
	class Bullet;

	class TourretComponent : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit TourretComponent(std::shared_ptr<GameObject> pOwner) : m_pOwner(pOwner)
		{
			m_SimpleTourret = true;
		};
		explicit TourretComponent(std::shared_ptr<GameObject> pOwner, float width, float height) : m_pOwner(pOwner), m_Width(width), m_Height(height)
		{
			m_SimpleTourret = false;
		};
		
		TourretComponent(const TourretComponent& other) = delete;
		TourretComponent(TourretComponent&& other) = delete;
		TourretComponent& operator=(const TourretComponent& other) = delete;
		TourretComponent& operator=(TourretComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() override;
		void SetTexture(const std::string& filename);

		void SetAngle(float angle) { m_Angle = angle; }
		void SetMirror(bool mirror) { m_Mirror = mirror; }
		void FireTourret(float angle);
		void SetEnvironment(std::vector<Cube>& environment) { m_Environment = environment; }
		

		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
	private:
		std::shared_ptr<Texture2D> m_texture{};
		float m_Angle{ 0 };
		bool m_Mirror{ false };
		std::string m_TexturePath;
		std::vector<std::shared_ptr<Bullet>> m_Bullets;
		int m_BulletCounter{ 0 };
		float m_Width;
		float m_Height;
		bool m_SimpleTourret{ false };
		std::vector<Cube> m_Environment;
		
	};
}

