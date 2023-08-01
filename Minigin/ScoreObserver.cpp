#include "ScoreObserver.h"
#include "ScoreComponent.h"


dae::ScoreObserver::ScoreObserver(std::shared_ptr<ScoreComponent> score, std::shared_ptr<TextObject> scoreText)
    :m_pScoreComponent{score}
    , m_pScoreText{scoreText}
{
}


void dae::ScoreObserver::Notify(EventType eventType)
{
    switch (eventType)
    {
    case dae::PlayerScoreAdd:

        m_pScoreText.lock()->SetText("Score: " + std::to_string(m_pScoreComponent.lock()->GetCurrentScore()));
        break;
    }
}
