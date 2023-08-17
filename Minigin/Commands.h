#pragma once
#include "GameObject.h"
#include "MoveComponent.h"
#include "Command.h"
#include "DataTypes.h"


namespace dae
{
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(const std::shared_ptr<GameObject> actor, float speed, TankInput input);
		virtual void Execute() override;

	private:
		std::shared_ptr<GameObject> m_Actor;
		float m_Speed;
		float m_CurrentSpeed;
		glm::vec3 m_Direction{(0.f, 0.f, 0.f)};

		
		float m_Angle{ 0.f };
		glm::vec2 m_Offset{};

		
		
	};

	class DamageCommand final : public Command
	{
	public:
		DamageCommand(const std::shared_ptr<GameObject> actor);
		virtual void Execute() override;

	private:
		std::shared_ptr<GameObject> m_Actor;
		
	};

	class AddScoreCommand final : public Command
	{
	public:
		AddScoreCommand(const std::shared_ptr<GameObject> actor);
		virtual void Execute() override;
		
	private:
		std::shared_ptr<GameObject> m_Actor;

	};

	class MoveTourretCommand final : public Command
	{
	public:
		MoveTourretCommand(const std::shared_ptr<GameObject> actor, TourretInput input);
		virtual void Execute() override;
	private:
		std::shared_ptr<GameObject> m_Actor;
		float m_Angle{ 0.f };
		

	};

	static float s_CurrentAngle{ 0.f };

	class ShootTourretCommand final : public Command
	{
	public:
		ShootTourretCommand(const std::shared_ptr<GameObject> actor);
		virtual void Execute() override;
	private:
		std::shared_ptr<GameObject> m_Actor;
	};

	class SkipMapCommand final : public Command
	{
	public:
		SkipMapCommand(const std::shared_ptr<GameObject> actor);
		virtual void Execute() override;
	private:
		std::shared_ptr<GameObject> m_Actor;
	};

	class StartGameCommand final : public Command
	{
	public:
		StartGameCommand(const std::shared_ptr<GameObject> firstPlayer, const std::shared_ptr<GameObject> secondPLayer);
		virtual void Execute() override;
	private:
		std::shared_ptr<GameObject> m_FirstPlayer;
		std::shared_ptr<GameObject> m_SecondPlayer;
	};

	class SwitchGameModeCommand final : public Command
	{
	public:
		SwitchGameModeCommand(const std::shared_ptr<GameObject> actor);
		virtual void Execute() override;
	private:
		int m_ModeIndx{ 1 };
		std::shared_ptr<GameObject> m_Actor;
	};

	class MuteAudioCommand final : public Command
	{
	public:
		MuteAudioCommand() {};
		virtual void Execute() override;
	};

	
}

