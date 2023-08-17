#include "DeathObserver.h"
#include "HealthComponent.h"
#include "TextObject.h"


namespace dae
{
    DeathObserver::DeathObserver(std::shared_ptr<HealthComponent> health, std::shared_ptr<TextObject> healthText)
        : m_pHealthComponent{health}
        , m_pHealthText{healthText}
    {
    }


    void DeathObserver::Notify(EventType eventType)
    {
        switch (eventType)
        {
        case dae::PlayerDied:
            
            m_pHealthText.lock()->SetText("Player Died");
           
            break;
        case dae::PlayerDamage:
        
            m_pHealthText.lock()->SetText("Remaining Lives: " + std::to_string(m_pHealthComponent.lock()->GetCurrentHealth()));
           
            break;
        }
    }
    void DeathObserver::Notify(EventType /*eventType*/, std::shared_ptr<BlackBoard> /*blackboard*/)
    {
    }
}
