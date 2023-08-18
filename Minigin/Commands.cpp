#include "Commands.h"
#include "DeltaTime.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"
#include "TextureComponent.h"
#include "Input.h"
#include "TourretComponent.h"
#include "CollisionComponent.h"
#include "MapCreator.h"
#include "SceneManager.h"
#include "TextObject.h"
#include "GameStateComponent.h"
#include "ServiceLocator.h"

dae::MoveCommand::MoveCommand(const std::shared_ptr<GameObject> actor, float speed, TankInput input)
	:m_Actor{actor}
	,m_Speed{speed}
	,m_CurrentSpeed{speed}
	,m_Direction{}
	,m_Angle{0.f}
	,m_Offset{}
{
	switch (input)
	{
	case Left:
		m_Direction = { -1.f,0,0 };
		m_Offset = {1, 0};
		break;
	case Right:
		m_Direction = { 1.f,0,0 };
		m_Offset = {-1, 0};
		break;
	case Up:
		m_Direction = { 0,-1,0 };
		m_Offset = {0, -1};
		break;
	case Down:
		m_Direction = { 0,1,0 };
		m_Offset = {0, 1};
		break;
	}
	m_Angle = static_cast<float>(input);
}

void dae::MoveCommand::Execute()
{
	m_Actor->GetComponent<dae::TextureComponent>()->SetAngle(m_Angle);
	
	auto translation = glm::vec3(m_Actor->GetLocalPosition(), 0) + (m_Direction * m_CurrentSpeed * DeltaTime::GetInstance().getDeltaTime());
	m_Actor->GetComponent<dae::CollisionComponent>()->SetFuturePos({ translation.x, translation.y});
	if (m_Actor->GetComponent<dae::CollisionComponent>()->IsColliding())
	{
		return;
	}

	m_Actor->SetLocalPosition({ translation.x, translation.y});
	
	
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

dae::SkipMapCommand::SkipMapCommand(const std::shared_ptr<GameObject> actor)
	:m_Actor{ actor }
	 
{
}

void dae::SkipMapCommand::Execute()
{
	m_Actor->GetComponent<dae::GameStateComponent>()->ResetGame(true, true);
}


dae::StartGameCommand::StartGameCommand(const std::shared_ptr<GameObject> firstPlayer, const std::shared_ptr<GameObject> secondPLayer)
	:m_FirstPlayer{firstPlayer}
	,m_SecondPlayer{secondPLayer}
{
}

void dae::StartGameCommand::Execute()
{
	if (!SceneManager::GetInstance().IsSceneActive("StartScreen")) return;
	std::string nextScene = SceneManager::GetInstance().GetNextSceneName();

	if (nextScene == "VersusModeScene")
	{
		m_FirstPlayer->GetComponent<dae::TourretComponent>()->AddEnemy(m_SecondPlayer);
		m_SecondPlayer->GetComponent<dae::TourretComponent>()->AddEnemy(m_FirstPlayer);
		m_SecondPlayer->GetComponent<dae::TextureComponent>()->SetTexture("Sprites/PinkTank.png");

		m_FirstPlayer->GetComponent<dae::ScoreComponent>()->SetScoreActive(false);
		m_FirstPlayer->GetComponent<dae::TextObject>()->SetText("Red VS Pink");
	}
	SceneManager::GetInstance().loadScene(nextScene);

	Engine::ServiceLocator::GetAudioSystem().Stop((Engine::SoundId)Engine::Sound::mainMenu);
	Engine::ServiceLocator::GetAudioSystem().Play((Engine::SoundId)Engine::Sound::background, 6.f);
}

dae::SwitchGameModeCommand::SwitchGameModeCommand(const std::shared_ptr<GameObject> actor)
	:m_Actor{ actor }
{
}

void dae::SwitchGameModeCommand::Execute()
{
	if (!SceneManager::GetInstance().IsSceneActive("StartScreen")) return;

	switch (m_ModeIndx++ % 3)
	{
	case 0:
		SceneManager::GetInstance().SetNextSceneName("SoloModeScene");
		m_Actor->GetComponent<dae::TextObject>()->SetText("GameMode: Solo Mode");
		break;
	case 1:
		SceneManager::GetInstance().SetNextSceneName("CoopModeScene");
		m_Actor->GetComponent<dae::TextObject>()->SetText("GameMode: Co-op Mode");
		break;
	case 2:
		SceneManager::GetInstance().SetNextSceneName("VersusModeScene");
		m_Actor->GetComponent<dae::TextObject>()->SetText("GameMode: Versus Mode");
		break;

	}
}

void dae::MuteAudioCommand::Execute()
{
	Engine::ServiceLocator::GetAudioSystem().MuteAllAudio();
}
