#include "ScoreComponent.h"
#include "DataTypes.h"


namespace dae
{

	void ScoreComponent::Update()
	{
	}

	void ScoreComponent::Render()
	{
	}

	void ScoreComponent::AddScore(float score)
	{
		m_CurrentScore += score;
		m_pScore->NotifyObservers(EventType::PlayerScoreAdd);
	}
}
