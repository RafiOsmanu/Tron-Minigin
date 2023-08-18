#include "SceneManager.h"
#include "Scene.h"

namespace dae
{
	void SceneManager::Update()
	{
		m_scenes[m_ActiveSceneIdx]->Update();
	}

	void SceneManager::Render()
	{
		m_scenes[m_ActiveSceneIdx]->Render();
	}

	void SceneManager::loadScene(std::string sceneName)
	{
		m_ActiveSceneIdx = m_SceneData[sceneName];
		m_ActiveSceneName = m_scenes[m_ActiveSceneIdx]->GetName();
	}

	bool SceneManager::IsSceneActive(std::string sceneName)
	{
		if (m_ActiveSceneIdx == static_cast<size_t>(m_SceneData[sceneName]))
			return true;

		return false;
	}

	std::string& SceneManager::GetActiveSceneName()
	{
		return m_ActiveSceneName;
	}

	Scene& SceneManager::CreateScene(const std::string& name, int sceneIdx)
	{
		const auto& scene = std::shared_ptr<Scene>(new Scene(name));
		m_ActiveSceneIdx = sceneIdx;
		m_SceneData[name] = sceneIdx;
		m_scenes.push_back(scene);
		return *scene;
	}
}
