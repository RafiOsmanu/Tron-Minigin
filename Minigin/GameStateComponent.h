#pragma once
#include "BaseComponent.h"
#include "DataTypes.h"
#include <vector> 
#include "GameObject.h"
#include "MapCreator.h"

namespace dae
{
	class GameStateComponent final: public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit GameStateComponent(std::shared_ptr<GameObject> pOwner, std::vector<std::weak_ptr<GameObject>> allEnteties, std::vector<EnemyData> enemyDataList) :
			m_pOwner(pOwner), 
			m_AllEntities(allEnteties),
			m_MapCubes(m_pOwner.lock().get()->GetComponent<MapCreator>().get()->GetCubes()),
			m_EnemyList(enemyDataList)
		{
		};

		
		GameStateComponent(const GameStateComponent&) = delete;
		GameStateComponent(GameStateComponent&&) = delete;
		GameStateComponent& operator= (const GameStateComponent&) = delete;
		GameStateComponent& operator= (const GameStateComponent&&) = delete;


		virtual void Update() override;
		virtual void Render() override {};
		void ResetGame(bool goToNextMap, bool resetScore);
		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }


	private:
		std::vector<std::weak_ptr<GameObject>> m_AllEntities;
		std::vector<Cube>& m_MapCubes;
		std::vector<EnemyData> m_EnemyList;
		bool m_GoToNextLevel{ false };

	};
}

