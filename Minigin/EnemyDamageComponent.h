#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "Bullet.h"


namespace dae
{

	class EnemyDamageComponent : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit EnemyDamageComponent(std::shared_ptr<GameObject> pOwner) : 
			m_pOwner(pOwner)
		{
		};
		

		EnemyDamageComponent(const EnemyDamageComponent&) = delete;
		EnemyDamageComponent(EnemyDamageComponent&&) = delete;
		EnemyDamageComponent& operator= (const EnemyDamageComponent&) = delete;
		EnemyDamageComponent& operator= (const EnemyDamageComponent&&) = delete;	

		virtual void Update() override;
		virtual void Render() override;

		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }

		void LoseLife() { --m_Lives; }

	private:
		//void HandleDamage();

		bool m_IsDead{ false };

		int m_Lives { 3 };
		
	};
}

