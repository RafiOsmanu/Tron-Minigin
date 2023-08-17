#include "GameStateComponent.h"
#include "ServiceLocator.h"
#include "DeltaTime.h"
#include "Commands.h"
#include "CollisionComponent.h"
#include "Input.h"
#include "SceneManager.h"
#include "DamageComponent.h"
#include "EnemyAiComponent.h"
#include "ScoreComponent.h"

void dae::GameStateComponent::Update()
{
	if (SceneManager::GetInstance().GetActiveSceneName() == "VersusModeScene")
	{
		if (m_AllEntities[m_AllEntities.size() - 1].lock()->GetComponent<dae::DamageComponent>()->GetIsDead()
			|| m_AllEntities[m_AllEntities.size() - 2].lock()->GetComponent<dae::DamageComponent>()->GetIsDead()) ResetGame(true, true);
	}

	for (auto& entity : m_AllEntities)
	{
		if (!entity.lock()->GetComponent<EnemyAiComponent>()) continue;
		if (!entity.lock()->GetComponent<dae::DamageComponent>()->GetIsDead()) return;
	}

	ResetGame(true, false);
}

void dae::GameStateComponent::ResetGame(bool goToNextMap, bool resetScore)
{
	for (auto& entity : m_AllEntities)
	{
		if (!entity.lock()->GetComponent<dae::DamageComponent>()->GetIsDead())
			entity.lock()->GetComponent<dae::DamageComponent>()->KillOwner();
	}

	if (resetScore)
	{
		if(m_AllEntities[m_AllEntities.size() - 1].lock()->GetComponent<dae::ScoreComponent>())
		m_AllEntities[m_AllEntities.size() - 1].lock()->GetComponent<dae::ScoreComponent>()->SetCurrentScore(0);
		m_AllEntities[m_AllEntities.size() - 1].lock()->GetComponent<dae::ScoreComponent>()->AddScore(0);

		if (m_AllEntities[m_AllEntities.size() - 2].lock()->GetComponent<dae::ScoreComponent>())
		m_AllEntities[m_AllEntities.size() - 2].lock()->GetComponent<dae::ScoreComponent>()->SetCurrentScore(0);
		m_AllEntities[m_AllEntities.size() - 2].lock()->GetComponent<dae::ScoreComponent>()->AddScore(0);
	}


	if(!m_GoToNextLevel && goToNextMap)
	{
		m_pOwner.lock()->GetComponent<MapCreator>()->GoToNextMap();
		m_GoToNextLevel = true;
	}

	if (m_pOwner.lock()->GetComponent<MapCreator>()->mapIsLoaded())
	{
		for (int i{}; i < m_AllEntities.size(); ++i)
		{
			m_AllEntities[i].lock()->GetComponent<dae::DamageComponent>()->ReviveOwner();
			m_AllEntities[i].lock()->SetLocalPosition(m_EnemyList[i].enemyData.second);
		}
		m_GoToNextLevel = false;
	}
}

