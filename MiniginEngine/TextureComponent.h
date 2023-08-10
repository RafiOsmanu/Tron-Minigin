#pragma once
#include <vector>
#include <memory>
#include <string>
#include "BaseComponent.h"
#include "GameObject.h"


namespace dae
{
	class Texture2D;

	class TextureComponent : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit TextureComponent(std::shared_ptr<GameObject> pOwner) : m_pOwner(pOwner) 
		{
			m_SimpleTexture = true;
		};

		explicit TextureComponent(std::shared_ptr<GameObject> pOwner, float width, float height) : m_pOwner(pOwner) , m_Width(width), m_Height(height)
		{
			m_SimpleTexture = false;
		};
		
		TextureComponent(const TextureComponent&) = delete;
		TextureComponent(TextureComponent&&) = delete;
		TextureComponent& operator= (const TextureComponent&) = delete;
		TextureComponent& operator= (const TextureComponent&&) = delete;

		virtual void Update() override;

		virtual void Render() override;

		void SetTexture(const std::string& filename);

		std::string GetTexture() const;

		void SetAngle(float angle) { m_Angle = angle; }

		void SetIsDead(bool isDead) { m_IsDead = isDead; }

	protected:
		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
		std::shared_ptr<Texture2D> m_texture{};
		std::string m_TexturePath{};

		float m_Angle{ 0 };
		float m_Width;
		float m_Height;

		bool m_SimpleTexture{ false };

		bool m_IsDead{ false };
	};
}

