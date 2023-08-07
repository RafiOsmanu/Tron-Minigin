#pragma once
#include "BaseComponent.h"
#include <memory>
#include <iostream>
#include <random>
#include <set>

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

	class EnemyAiComponent : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
		public:
			explicit EnemyAiComponent(std::shared_ptr<GameObject> pOwner) : m_pOwner(pOwner)
			{
			};
			EnemyAiComponent(const EnemyAiComponent& other) = delete;
			EnemyAiComponent(EnemyAiComponent&& other) = delete;
			EnemyAiComponent& operator=(const EnemyAiComponent& other) = delete;
			EnemyAiComponent& operator=(EnemyAiComponent&& other) = delete;
			virtual void Update() override;
			virtual void Render() override;

			void HandleMovement();

			std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
	private:

		EnemyDirection m_Direction{ EnemyDirection::Left };


	};

}