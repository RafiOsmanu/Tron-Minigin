#include "FPS.h"
#include "DeltaTime.h"
#include "TextObject.h"


namespace dae
{
	void FPS::Update()
	{
		m_Timer += dae::DeltaTime::GetInstance().getDeltaTime();

		m_FpsSample.push_back(GetFPS());
		if (m_Timer > 0.5f)
		{
			float average{};
			for (auto& fps : m_FpsSample)
			{
				average += fps;
			}
			average /= m_FpsSample.size();
			m_FpsSample.clear();
			
			m_pOwner.lock()->GetComponent<TextObject>()->SetText("FPS: " + std::to_string(static_cast<int>(average)));
			m_Timer = 0.f;
			
		}
	}

	void FPS::Render()
	{
	}

	float FPS::GetFPS()
	{
		float deltaTime{ dae::DeltaTime::GetInstance().getDeltaTime() };
		if (deltaTime == 0)
		{
			return 0;
		}
		return 1.f / dae::DeltaTime::GetInstance().getDeltaTime();
	}
}
