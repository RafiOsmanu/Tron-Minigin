#pragma once
#include "BaseComponent.h"
#include "DataTypes.h"
#include <vector>


namespace dae
{
	class CollisionComponent final : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit CollisionComponent(std::shared_ptr<GameObject> pOwner, std::vector<Cube>& mapCubes) : 
			m_pOwner(pOwner),
			m_MapCubes(mapCubes)
		{
			
		};

		CollisionComponent(const CollisionComponent&) = delete;
		CollisionComponent(CollisionComponent&&) = delete;
		CollisionComponent& operator= (const CollisionComponent&) = delete;
		CollisionComponent& operator= (const CollisionComponent&&) = delete;

		virtual void Update() override;
		virtual void Render() override;
		
		bool IsPlayerDead() const { return m_IsPlayerDead; }
		void SetPlayerDead(bool isDead) { m_IsPlayerDead = isDead; }
		bool IsColliding() const { return m_IsColliding; }
		bool IsNotColliding() const { return m_IsNotColliding; }
		void SetFuturePos(glm::vec2 futurePos) { m_FuturePos = futurePos; }
		void SetIsDead(bool isDead) { m_IsDead = isDead; }

		void SetPlayersToCollideWith(std::vector<std::weak_ptr<GameObject>> playersToCollideWith) { m_PlayersToCollideWith = playersToCollideWith; }

		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }

	private:
		bool IsColliding(glm::vec2 playerPos, Cube& mapCube);
		bool IsCollidingWithPlayer(glm::vec2 playerPos, glm::vec2 playerPos2);
		bool IsNotColliding();
		bool m_IsPlayerDead{ false };
		std::vector<Cube>& m_MapCubes;
		bool m_IsColliding{ false };
		bool m_IsNotColliding{ false };
		glm::vec2 m_FuturePos{ 0,0 };
		bool m_IsDead{ false };
		float m_CollisionBoxSize{7.f};


		std::vector<std::weak_ptr<GameObject>> m_PlayersToCollideWith;
		
		
	};
}

