#include "GameStateComponent.h"
#include "ServiceLocator.h"
#include "DeltaTime.h"
#include "Commands.h"
#include "CollisionComponent.h"
#include "Input.h"

void dae::GameStateComponent::Update()
{
    if (AllCubesActive(m_MapCubes))
    {
        m_IsGameWon = true;
    }

    if (m_IsGameWon)
    {
        //make sure the sound is only played once 
        if (!m_SoundPlayed)
        {
			Engine::ServiceLocator::GetAudioSystem().Play((unsigned short)Engine::Sound::QbertWin, 10.f);
			m_SoundPlayed = true;
            Input::GetInstance().GetKeyboard().get()->SetDisableInput(true);
		}
        
        //delay time to goto next level
        m_Timer += DeltaTime::GetInstance().getDeltaTime();
        if (m_Timer >= m_TimeToWait)
        {
            Input::GetInstance().GetKeyboard().get()->SetDisableInput(false);
            m_IsGameWon = false;
            m_SoundPlayed = false;
			m_Timer = 0.f;
            //code to go to next level

        }
    }

    if (m_Player->GetComponent<CollisionComponent>()->IsPlayerDead())
    {
        if (!m_SoundPlayed)
        {
            Engine::ServiceLocator::GetAudioSystem().Play((unsigned short)Engine::Sound::QbertHit, 10.f);
            m_SoundPlayed = true;
            Input::GetInstance().GetKeyboard().get()->SetDisableInput(true);
        }

        m_Timer += DeltaTime::GetInstance().getDeltaTime();
        if (m_Timer >= m_TimeToWait)
        {
            Input::GetInstance().GetKeyboard().get()->SetDisableInput(false);
            m_Player->GetComponent<CollisionComponent>()->SetPlayerDead(false);
            m_SoundPlayed = false;
            m_Timer = 0.f;
            //Restart level

        }
    }
}

bool dae::GameStateComponent::AllCubesActive(const std::vector<dae::Cube>& cubes)
{
    for (const auto& cube : cubes)
    {
        if (!cube.isActive)
        {
            return false;
        }
    }

    return true;
}
