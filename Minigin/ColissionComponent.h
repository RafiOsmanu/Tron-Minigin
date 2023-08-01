#pragma once
#include "BaseComponent.h"
#include "DataTypes.h"
#include <vector>


namespace dae
{
	class ColissionComponent : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit ColissionComponent(std::shared_ptr<GameObject> pOwner, std::vector<Cube>& mapCubes) : 
			m_pOwner(pOwner),
			m_MapCubes(mapCubes)
		{

		}

		ColissionComponent(const ColissionComponent&) = delete;
		ColissionComponent(ColissionComponent&&) = delete;
		ColissionComponent& operator= (const ColissionComponent&) = delete;
		ColissionComponent& operator= (const ColissionComponent&&) = delete;

		virtual void Update() override;
		virtual void Render() override;
		
		bool IsPlayerDead() const { return m_IsPlayerDead; }
		void SetPlayerDead(bool isDead) { m_IsPlayerDead = isDead; }

		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }

	private:
		bool IsColliding(glm::vec2 playerPos, Cube mapCube);
		bool IsNotColliding();
		std::vector<Cube>& m_MapCubes;
		bool m_IsPlayerDead{ false };
		
	};
}

