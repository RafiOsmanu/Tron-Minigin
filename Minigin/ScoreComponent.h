#pragma once
#include <vector>
#include <memory>
#include "BaseComponent.h"
#include "GameObject.h"
#include "Subject.h"



namespace dae
{
	
	class ScoreComponent : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit ScoreComponent(std::shared_ptr<GameObject> pOwner) : m_pOwner(pOwner)
		{
			m_CurrentScore = 0;
			m_pScore = std::make_unique<Subject>();
		}

		ScoreComponent(const ScoreComponent&) = delete;
		ScoreComponent(ScoreComponent&&) = delete;
		ScoreComponent& operator= (const ScoreComponent&) = delete;
		ScoreComponent& operator= (const ScoreComponent&&) = delete;

		virtual void Update() override;
		virtual void Render() override;

		void AddScore(float score);
		void SetMaxScore(float score) { m_MaxScore = score; }

		dae::Subject* GetSubject() { return m_pScore.get(); }
		float GetCurrentScore() { return m_CurrentScore; }


		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }


	private:

		float m_CurrentScore{ 0 };
		float m_MaxScore{ 10000 };

		//pointer to subject class
		std::unique_ptr<dae::Subject> m_pScore;

	};
}

