#include "Commands.h"
#include "DeltaTime.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"
#include "TextureComponent.h"
#include "Input.h"
#include "TourretComponent.h"
#include "ColissionComponent.h"

dae::MoveCommand::MoveCommand(const std::shared_ptr<GameObject> actor, float speed, TankInput input)
	:m_Actor{actor}
	,m_Speed{speed}
	,m_CurrentSpeed{speed}
{
	switch (input)
	{
	case Left:
		m_Direction = { -1.f,0,0 };
		break;
	case Right:
		m_Direction = { 1.f,0,0 };
		break;
	case Up:
		m_Direction = { 0,-1,0 };
		break;
	case Down:
		m_Direction = { 0,1,0 };
		break;
	}
	m_Angle = static_cast<float>(input);
}

void dae::MoveCommand::Execute()
{
	m_Actor->GetComponent<dae::TextureComponent>()->SetAngle(m_Angle);
	
	auto translation = glm::vec3(m_Actor->GetLocalPosition(), 0) + (m_Direction * m_CurrentSpeed * DeltaTime::GetInstance().getDeltaTime());
	m_Actor->GetComponent<dae::ColissionComponent>()->SetFuturePos({ translation.x, translation.y });
	if (m_Actor->GetComponent<dae::ColissionComponent>()->IsColliding())
	{
		return;
	}
	m_Actor->SetLocalPosition({ translation.x, translation.y });
	
	//Engine::ServiceLocator::GetAudioSystem().Play((unsigned short)Engine::Sound::QbertJump, 10.f);
}

glm::vec2 dae::MoveCommand::CalculateSlidingVector(const glm::vec2& currentPosition, const glm::vec2& potentialNewPosition)
{
	glm::vec2 direction = potentialNewPosition - currentPosition;
	glm::vec2 slidingVector;

	if (direction.x > 0)
		slidingVector.x = std::floor(potentialNewPosition.x) - currentPosition.x;
	else if (direction.x < 0)
		slidingVector.x = std::ceil(potentialNewPosition.x) - currentPosition.x;
	else
		slidingVector.x = 0;

	if (direction.y > 0)
		slidingVector.y = std::floor(potentialNewPosition.y) - currentPosition.y;
	else if (direction.y < 0)
		slidingVector.y = std::ceil(potentialNewPosition.y) - currentPosition.y;
	else
		slidingVector.y = 0;

	return slidingVector;
}

//void dae::MoveCommand::Update()
//{
//	if (m_IsMoving)
//	{
//		if (glm::distance(m_Actor->GetLocalPosition(), m_OgPos) < 32.5f)
//		{
//			auto translation = glm::vec3(m_Actor->GetLocalPosition(), 0) + (m_Direction * m_Speed * DeltaTime::GetInstance().getDeltaTime());
//			m_Actor->SetLocalPosition({ translation.x, translation.y });
//		}
//		else
//		{
//			if (m_Timer >= m_MaxTime)
//			{
//				m_IsMoving = false;
//				m_Actor->SetIsMoving(false);
//				m_Timer = 0.f;
//			}
//			else
//			{
//				m_Timer += DeltaTime::GetInstance().getDeltaTime();
//			}
//			
//		}
//	}
//}

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

dae::MoveTourretCommand::MoveTourretCommand(const std::shared_ptr<GameObject> actor, TourretInput input)
	:m_Actor{actor}
{
	m_Angle = static_cast<float>(input);
}

void dae::MoveTourretCommand::Execute()
{
	m_Actor->GetComponent<dae::TourretComponent>()->SetAngle(m_Angle);
	s_CurrentAngle = m_Angle;
}

dae::ShootTourretCommand::ShootTourretCommand(const std::shared_ptr<GameObject> actor)
	:m_Actor{ actor }
{
}

void dae::ShootTourretCommand::Execute()
{
	m_Actor->GetComponent<dae::TourretComponent>()->FireTourret(s_CurrentAngle);
}
