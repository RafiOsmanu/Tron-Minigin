#include "ScoreComponent.h"
#include <iostream>
#include <fstream>
#include "DataTypes.h"
#include "imgui.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "document.h"
#include "istreamwrapper.h"


namespace dae
{
	ScoreComponent::ScoreComponent(std::shared_ptr<GameObject> pOwner, std::shared_ptr<BlackBoard> blackboard, bool displayLeaderboard) 
		: m_pOwner(pOwner),
		  m_Blackboard(blackboard),
		  m_DisplayScore(displayLeaderboard)
	{
		m_CurrentScore = 0;
		m_pScore = std::make_unique<Subject>();
		
		if(m_DisplayScore)
		DisplayLeaderboard();
	}

	ScoreComponent::~ScoreComponent()
	{
		
	}

	void ScoreComponent::Initialize()
	{
		
	}

	void ScoreComponent::DisplayLeaderboard()
	{
		using rapidjson::Document;
		Document jsonDoc;

		if (std::ifstream inputFile{ "C:/DAE/RETAKES/progg 4/Tron-Minigin/Data/GameData/HighScores.json" })
		{
			rapidjson::IStreamWrapper inputFileWrapper{ inputFile };
			jsonDoc.ParseStream(inputFileWrapper);

			// Check if parsing succeeded
			if (!jsonDoc.IsObject())
			{
				std::cout << "Failed to parse JSON file." << std::endl;
				return;
			}

			if (jsonDoc.HasMember("Highscores") && jsonDoc["Highscores"].IsArray()) {
				rapidjson::Value& highScores = jsonDoc["Highscores"];

				// Find the position to insert the new score
				for (rapidjson::SizeType i{}; i < highScores.Size(); ++i) {
					const rapidjson::Value& highScore = highScores[i];
					if (highScore.HasMember("Highscore") && highScore["Highscore"].IsInt()) {
						m_Highscores.push_back(highScore["Highscore"].GetInt());
					}
					if (highScore.HasMember("Name") && highScore["Name"].IsString())
					{
						m_Names.push_back(highScore["Name"].GetString());
					}
				}
			}
			
		}

		m_Blackboard.get()->Set("Names", m_Names);
		m_Blackboard.get()->Set("Highscores", m_Highscores);
	}

	void ScoreComponent::Update()
	{
		if (!m_DisplayScore) return;
		m_Blackboard.get()->Set("NameInput", m_InputBuffer);
	}

	void ScoreComponent::Render()
	{
		if (!m_DisplayScore) return;

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplSDL2_NewFrame(Renderer::GetInstance().GetWindow());
		ImGui::NewFrame();

		ImGui::SetNextWindowPos(ImVec2(472.5f, 10));
		ImGui::SetNextWindowSize(ImVec2(160, 275));

		ImGui::Begin("Leaderboard", nullptr, ImGuiWindowFlags_NoResize);


		// Display label and input box
		ImGui::Text("Input your name:");
		ImGui::InputText("Name", m_InputBuffer, sizeof(m_InputBuffer));
		if (ImGui::Button("Save Score", { 128.f, 24.f }))
		{
			SaveHighScore();
		}

		for (size_t i{}; i < m_Highscores.size(); ++i)
		{
			std::string leaderboard = std::to_string(i + 1) + ". " + m_Names[i] + " " + std::to_string(m_Highscores[i]);
			ImGui::Text(leaderboard.c_str());
		}
			

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

		// Update the stored string with the entered text
		
		//s_NameInput = m_InputBuffer;
	}

	void ScoreComponent::AddScore(int score)
	{
		if (!m_DisplayScore) return;
		m_CurrentScore += score;
		m_pScore->NotifyObservers(EventType::PlayerScoreAdd);
	}
	void ScoreComponent::SaveHighScore()
	{
		if (!m_DisplayScore) return;
		m_pScore->NotifyObservers(EventType::PlayerDied, m_Blackboard);
		m_Names = m_Blackboard.get()->Get<std::vector<std::string>>("Names");
		m_Highscores = m_Blackboard.get()->Get < std::vector <int>>("Highscores");
	}
}
