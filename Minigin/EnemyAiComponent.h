#pragma once
#include "BaseComponent.h"
#include <memory>
#include <iostream>
#include <random>
#include <set>
#include "DataTypes.h"

namespace dae
{
	class GameObject;

	enum class EnemyDirection
	{
		Left,
		Right,
		Up,
		Down
	};

	class EnemyAiComponent final : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
		public:
			explicit EnemyAiComponent(std::shared_ptr<GameObject> pOwner, EnemyType type) : m_pOwner(pOwner) , m_Type(type)
			{
				if (type == EnemyType::tank) m_Speed = 50.f;
				else if (type == EnemyType::recognizer) m_Speed = 75.f;
			};
			EnemyAiComponent(const EnemyAiComponent& other) = delete;
			EnemyAiComponent(EnemyAiComponent&& other) = delete;
			EnemyAiComponent& operator=(const EnemyAiComponent& other) = delete;
			EnemyAiComponent& operator=(EnemyAiComponent&& other) = delete;
			virtual void Update() override;
			virtual void Render() override;

			void HandleMovement();
			void SetIsDead(bool isDead) { m_Isdead = isDead; }
			EnemyType GetEnemyType() { return m_Type; }

			std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
	private:

		EnemyDirection m_Direction{ EnemyDirection::Left };
		EnemyType m_Type{};

		bool m_Isdead{ false };
		float m_Speed{ 50.f };


	};

}