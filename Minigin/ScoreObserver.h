#pragma once
#include <memory>
#include "GameObject.h"
#include "TextObject.h"
#include "Observer.h"
#include "TextObject.h"


namespace dae
{
	class TextObject;
	class ScoreComponent;

	class ScoreObserver final : public Observer
	{
	public:
		ScoreObserver(std::shared_ptr<ScoreComponent> score
			, std::shared_ptr<TextObject> scoreText);

		
		void Notify(EventType eventType) override;
	private:
		std::weak_ptr<ScoreComponent> m_pScoreComponent;
		std::weak_ptr<TextObject> m_pScoreText;
	};

}

