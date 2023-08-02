#include "Commands.h"
#include "DeltaTime.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"
#include "TextureComponent.h"
#include "Input.h"
#include "TourretComponent.h"

dae::MoveCommand::MoveCommand(const std::shared_ptr<GameObject> actor, float speed, TankInput input)
	:m_Actor{actor}
	,m_Speed{speed}
{
	switch (input)
	{
	case Left:
		m_Direction = { -1.f,0,0 };
		m_Angle = 180.f;
		break;
	case Right:
		m_Direction = { 1.f,0,0 };
		m_Angle = 0.f;
		break;
	case Up:
		m_Direction = { 0,-1,0 };
		m_Angle = 270.f;
		break;
	case Down:
		m_Direction = { 0,1,0 };
		m_Angle = 90.f;
		break;
	}
}

void dae::MoveCommand::Execute()
{
	m_Actor->GetComponent<dae::TextureComponent>()->SetAngle(m_Angle);

	auto translation = glm::vec3(m_Actor->GetLocalPosition(), 0) + (m_Direction * m_Speed * DeltaTime::GetInstance().getDeltaTime());
	m_Actor->SetLocalPosition({ translation.x, translation.y });
	m_Actor->GetWorldPosition();
	//Engine::ServiceLocator::GetAudioSystem().Play((unsigned short)Engine::Sound::QbertJump, 10.f);
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
	switch (input)
	{
	case TourretLeft:
		m_Angle = 180.f;
		break;
	case TourretRight:
		m_Angle = 0.f;
		
		break;
	case TourretUp:
		
		m_Angle = 270.f;
		break;
	case TourretDown:
		m_Angle = 90.f;
		break;
	}
}

void dae::MoveTourretCommand::Execute()
{
	m_Actor->GetComponent<dae::TourretComponent>()->SetAngle(m_Angle);
}
