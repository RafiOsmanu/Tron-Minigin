#pragma once
#include <memory>
#include "GameObject.h"
#include "TextObject.h"
#include "Observer.h"


namespace dae
{
	class TextObject;
	class HealthComponent;

	class DeathObserver final : public Observer
	{
	public:
		DeathObserver(std::shared_ptr<HealthComponent> health
			, std::shared_ptr<TextObject> healthText);

		void Notify(EventType eventType) override;
		void Notify(EventType eventType, std::shared_ptr<BlackBoard> blackboard) override;

		
	private:

		std::weak_ptr<HealthComponent> m_pHealthComponent;
		std::weak_ptr<TextObject> m_pHealthText;

	};

}
