#pragma once
#include <vector>
#include <memory>
#include "BaseComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"

namespace dae
{
	class TourretComponent : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit TourretComponent(std::shared_ptr<GameObject> pOwner) : m_pOwner(pOwner)
		{};
		
		TourretComponent(const TourretComponent& other) = delete;
		TourretComponent(TourretComponent&& other) = delete;
		TourretComponent& operator=(const TourretComponent& other) = delete;
		TourretComponent& operator=(TourretComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() override;
		void SetTexture(const std::string& filename);

		void SetAngle(float angle) { m_Angle = angle; }
		void SetMirror(bool mirror) { m_Mirror = mirror; }

		

		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
	private:
		std::shared_ptr<Texture2D> m_texture{};
		float m_Angle{ 0 };
		bool m_Mirror{ false };
		std::string m_TexturePath;
		
	};
}

