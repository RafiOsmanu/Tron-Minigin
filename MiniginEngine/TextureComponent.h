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
		explicit TextureComponent(std::shared_ptr<GameObject> pOwner) : m_pOwner(pOwner) {};
		
		TextureComponent(const TextureComponent&) = delete;
		TextureComponent(TextureComponent&&) = delete;
		TextureComponent& operator= (const TextureComponent&) = delete;
		TextureComponent& operator= (const TextureComponent&&) = delete;

		virtual void Update() override;

		virtual void Render() override;

		void SetTexture(const std::string& filename);

	protected:
		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
		std::shared_ptr<Texture2D> m_texture{};

	
	};
}

