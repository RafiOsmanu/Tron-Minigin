#pragma once
#include "BaseComponent.h"
#include "DataTypes.h"
#include <vector> 
#include "GameObject.h"
#include "MapCreator.h"

namespace dae
{
	class GameStateComponent : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit GameStateComponent(std::shared_ptr<GameObject> pOwner, std::shared_ptr<GameObject> player) :
			m_pOwner(pOwner), 
			m_Player(player),
			m_MapCubes(m_pOwner.lock().get()->GetComponent<MapCreator>().get()->GetCubes())
		{
			//m_MapCubes = m_pOwner.lock().get()->GetComponent<MapCreator>().get()->GetCubes();
		};

		
		GameStateComponent(const GameStateComponent&) = delete;
		GameStateComponent(GameStateComponent&&) = delete;
		GameStateComponent& operator= (const GameStateComponent&) = delete;
		GameStateComponent& operator= (const GameStateComponent&&) = delete;


		virtual void Update() override;
		virtual void Render() override {};

		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
	private:
		bool AllCubesActive(const std::vector<dae::Cube>& cubes);

		bool m_IsGameOver{ false };
		bool m_IsGameWon{ false };
		bool m_SoundPlayed{ false };
		bool m_AllCubesActive{ true };
		std::shared_ptr<GameObject> m_Player;
		std::vector<Cube>& m_MapCubes;

		float m_Timer{ 0.f };
		float m_TimeToWait{ 3.f };

	};
}

