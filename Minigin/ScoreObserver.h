#pragma once
#include <memory>
#include "GameObject.h"
#include "TextObject.h"
#include "Observer.h"
#include "TextObject.h"
#include "Document.h"


namespace dae
{
	class Document;
	class TextObject;
	class ScoreComponent;
	class File;

	class ScoreObserver final : public Observer
	{
	public:
		ScoreObserver(std::shared_ptr<ScoreComponent> score
			, std::shared_ptr<TextObject> scoreText);

		
		void Notify(EventType eventType) override;
		void Notify(EventType eventType, std::shared_ptr<BlackBoard> blackboard) override;

	private:
		void WriteScore(const int score, const char* input, rapidjson::Document& jsonDoc, std::shared_ptr<BlackBoard> blackboard);
		std::weak_ptr<ScoreComponent> m_pScoreComponent;
		std::weak_ptr<TextObject> m_pScoreText;

		std::vector<int> m_Highscores{};
		std::vector<std::string> m_Names{};
		
	};

}

