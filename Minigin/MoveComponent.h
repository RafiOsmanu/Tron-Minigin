#pragma once
#include <vector>
#include <memory>
#include <string>
#include "BaseComponent.h"
#include "GameObject.h"
namespace dae
{

	class MoveComponent final : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit MoveComponent(std::shared_ptr<GameObject> pOwner) : m_pOwner(pOwner) {};

		MoveComponent(const MoveComponent&) = delete;
		MoveComponent(MoveComponent&&) = delete;
		MoveComponent& operator= (const MoveComponent&) = delete;
		MoveComponent& operator= (const MoveComponent&&) = delete;

		virtual void Update() override;

		virtual void Render() override;

		

	protected:
		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
		std::shared_ptr<Texture2D> m_texture{};
	private:
		float m_PosX{0.f};
		float m_PosY{0.f};
		float m_Radius{ 3.f };
		float m_Angle{ 0.f };
		
	};
}

