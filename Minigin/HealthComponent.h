#pragma once
#include <vector>
#include <memory>
#include "BaseComponent.h"
#include "GameObject.h"
#include "Subject.h"


namespace dae
{
	

	class HealthComponent final : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit HealthComponent(std::shared_ptr<GameObject> pOwner) : m_pOwner(pOwner) 
		{ 
			m_CurrentLives = m_MaxLives;  
			m_pDamage = std::make_unique<dae::Subject>();
		}

		HealthComponent(const HealthComponent&) = delete;
		HealthComponent(HealthComponent&&) = delete;
		HealthComponent& operator= (const HealthComponent&) = delete;
		HealthComponent& operator= (const HealthComponent&&) = delete;

		virtual void Update() override;
		virtual void Render() override;

		void LoseLife();
		dae::Subject* GetSubject() { return m_pDamage.get(); }
		int GetCurrentHealth(){ return m_CurrentLives; }


		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
	

	private:
		
		int m_CurrentLives{0};
		const int m_MaxLives{30};

		//pointer to Subject class
		std::unique_ptr<dae::Subject> m_pDamage;
		
	};
}

