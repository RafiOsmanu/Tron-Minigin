#include "Commands.h"
#include "DeltaTime.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"

dae::MoveCommand::MoveCommand(const std::shared_ptr<GameObject> actor, float speed, PlayerInput input)
	:m_Actor{actor}
	,m_Speed{speed}
	,m_OgPos{actor->GetLocalPosition()}
	,m_Input{input}
{
	switch (m_Input)
	{
	case Left:
		m_Direction = { -0.70f,-1,0 };
		break;
	case Right:
		m_Direction = { 0.70f,1,0 };
		break;
	case Up:
		m_Direction = { 0.70f,-1,0 };
		break;
	case Down:
		m_Direction = { -0.70f,1,0 };
		break;
	}

	
}

void dae::MoveCommand::Execute()
{
	if (m_IsMoving || m_Actor->IsMoving() || m_IsDisableInput) return;

	m_OgPos = m_Actor->GetLocalPosition();
	m_IsMoving = true;
	m_Actor->SetIsMoving(true);
	Engine::ServiceLocator::GetAudioSystem().Play((unsigned short)Engine::Sound::QbertJump, 10.f);
}

void dae::MoveCommand::Update()
{
	if (m_IsMoving)
	{
		if (glm::distance(m_Actor->GetLocalPosition(), m_OgPos) < 32.5f)
		{
			auto translation = glm::vec3(m_Actor->GetLocalPosition(), 0) + (m_Direction * m_Speed * DeltaTime::GetInstance().getDeltaTime());
			m_Actor->SetLocalPosition({ translation.x, translation.y });
		}
		else
		{
			if (m_Timer >= m_MaxTime)
			{
				m_IsMoving = false;
				m_Actor->SetIsMoving(false);
				m_Timer = 0.f;
			}
			else
			{
				m_Timer += DeltaTime::GetInstance().getDeltaTime();
			}
			
		}
	}
}

dae::DamageCommand::DamageCommand(const std::shared_ptr<GameObject> actor)
	:m_Actor{actor}
{
}

void dae::DamageCommand::Execute()
{
	m_Actor->GetComponent<dae::HealthComponent>()->LoseLife();
}

dae::AddScoreCommand::AddScoreCommand(const std::shared_ptr<GameObject> actor)
	:m_Actor {actor}
{

}

void dae::AddScoreCommand::Execute()
{
	m_Actor->GetComponent<dae::ScoreComponent>()->AddScore(10);
}
