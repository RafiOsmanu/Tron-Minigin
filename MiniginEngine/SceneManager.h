#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include <unordered_map>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name, int sceneIdx);

		void Update();
		void Render();
		void loadScene(std::string sceneName);
		bool IsSceneActive(std::string sceneName);
		std::string& GetActiveSceneName();

		//for start screen
		std::string& GetNextSceneName() { return m_NextSceneName; }
		void SetNextSceneName(std::string sceneName) { m_NextSceneName = sceneName; }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		size_t m_ActiveSceneIdx = 0;
		std::unordered_map<std::string, int> m_SceneData;
		std::string m_ActiveSceneName;
		std::string m_NextSceneName;
	};
}
