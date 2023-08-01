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
		MoveCommand(const std::shared_ptr<GameObject> actor, float speed, PlayerInput input);
		virtual void Execute() override;
		virtual void Update() override;

	private:
		std::shared_ptr<GameObject> m_Actor;
		float m_Speed;
		glm::vec2 m_OgPos{};
		glm::vec3 m_Direction{(0.f, 0.f, 0.f)};

		PlayerInput m_Input;

		bool m_IsMoving{ false };
		bool m_IsInitialized{ false };
		bool m_IsDisableInput{ false };

		float m_Timer{ 0.f };
		float m_MaxTime{ 0.25f };
	};

	class DamageCommand final : public Command
	{
	public:
		DamageCommand(const std::shared_ptr<GameObject> actor);
		virtual void Execute() override;
		virtual void Update() override {};
	private:
		std::shared_ptr<GameObject> m_Actor;
		
	};

	class AddScoreCommand final : public Command
	{
	public:
		AddScoreCommand(const std::shared_ptr<GameObject> actor);
		virtual void Execute() override;
		virtual void Update() override {};
	private:
		std::shared_ptr<GameObject> m_Actor;

	};
	
}

