#pragma once
#include <vector>
#include <memory>
#include "BaseComponent.h"
#include "GameObject.h"
#include "Subject.h"
#include "BlackBoard.h"



namespace dae
{

	class ScoreComponent final : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		explicit ScoreComponent(std::shared_ptr<GameObject> pOwner, std::shared_ptr<BlackBoard> blackboard, bool displayLeaderboard);

		~ScoreComponent();
		ScoreComponent(const ScoreComponent&) = delete;
		ScoreComponent(ScoreComponent&&) = delete;
		ScoreComponent& operator= (const ScoreComponent&) = delete;
		ScoreComponent& operator= (const ScoreComponent&&) = delete;

		virtual void Update() override;
		virtual void Render() override;

		void AddScore(int score);
		void SaveHighScore();
		void SetMaxScore(int score) { m_MaxScore = score; }

		dae::Subject* GetSubject() { return m_pScore.get(); }
		int GetCurrentScore() { return m_CurrentScore; }
		void SetCurrentScore(int score) { m_CurrentScore = score; }


		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }

		void SetScoreActive(bool disabeScore) { m_DisplayScore = disabeScore; }


	private:

		void Initialize();

		int m_CurrentScore{ 0 };
		int m_MaxScore{ 10000 };
		//pointer to subject class
		std::unique_ptr<dae::Subject> m_pScore;

		char m_InputBuffer[256]{};

		std::shared_ptr<BlackBoard> m_Blackboard;

		void DisplayLeaderboard();

		std::vector<int> m_Highscores{};
		std::vector<std::string> m_Names{};

		bool m_DisplayScore{ false };



	};
}

