#pragma once
#include <memory>
#include "AudioNavigator.h"

namespace Engine
{
	class ServiceLocator final
	{
		static std::unique_ptr<BaseAudioNavigator> m_pAudioNavigatorInstance;
		static AudioNavigatorNull m_DefaultAudioNavigator;

	public:
		static BaseAudioNavigator& GetAudioSystem() { return *m_pAudioNavigatorInstance.get(); }
		static void RegisterAudioSystem(BaseAudioNavigator* pAudioNavigator)
		{
			m_pAudioNavigatorInstance.reset(pAudioNavigator == nullptr ? &m_DefaultAudioNavigator : pAudioNavigator);
		}
	};

	inline std::unique_ptr<BaseAudioNavigator> ServiceLocator::m_pAudioNavigatorInstance{};
	inline AudioNavigatorNull ServiceLocator::m_DefaultAudioNavigator;
}

