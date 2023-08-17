#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "Bullet.h"


namespace dae
{

	class DamageComponent final : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit DamageComponent(std::shared_ptr<GameObject> pOwner, bool player) : 
			m_pOwner(pOwner),
			m_Player(player)
		{
		};
		

		DamageComponent(const DamageComponent&) = delete;
		DamageComponent(DamageComponent&&) = delete;
		DamageComponent& operator= (const DamageComponent&) = delete;
		DamageComponent& operator= (const DamageComponent&&) = delete;	

		virtual void Update() override;
		virtual void Render() override;

		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }

		bool LoseLife();
		bool GetIsDead() { return m_IsDead; }

		void KillOwner();
		void ReviveOwner();

	private:
		//void HandleDamage();

		bool m_IsDead{ false };
		bool m_Player{ false };
		bool m_OwnerKilled{ false };

		int m_Lives { 3 };

		
	};
}

