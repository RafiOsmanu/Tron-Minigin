#include "ScoreObserver.h"
#include "ScoreComponent.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <writer.h>
#include <locale>
#include <codecvt>
#include <string>
#include "rapidjson.h"
#include "stream.h"
#include "filereadstream.h"
#include "filewritestream.h"
#include "istreamwrapper.h"
#include "ostreamwrapper.h"
#include "ScoreComponent.h"



dae::ScoreObserver::ScoreObserver(std::shared_ptr<ScoreComponent> score, std::shared_ptr<TextObject> scoreText)
    :m_pScoreComponent{score}
    , m_pScoreText{scoreText}
{
}


void dae::ScoreObserver::Notify(EventType eventType)
{
    switch (eventType)
    {
    case dae::PlayerScoreAdd:

        m_pScoreText.lock()->SetText("Score: " + std::to_string(m_pScoreComponent.lock()->GetCurrentScore()));
        break;
    }
}

void dae::ScoreObserver::Notify(EventType eventType, std::shared_ptr<BlackBoard> blackboard)
{
    switch (eventType)
    {
    case dae::PlayerDied:

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

            int currentScore = m_pScoreComponent.lock()->GetCurrentScore();
            const char* nameInput = blackboard.get()->Get<const char*>("NameInput");

            // Insert the current score in the right place and write back to the file
            WriteScore(currentScore, nameInput, jsonDoc, blackboard);

            // Write the modified JSON back to the file
            std::ofstream outputFile("C:/DAE/RETAKES/progg 4/Tron-Minigin/Data/GameData/HighScores.json");
            if (!outputFile.is_open()) {
                std::cout << "Failed to open output file for writing." << std::endl;
                return;
            }

            rapidjson::OStreamWrapper outputStreamWrapper(outputFile);
            rapidjson::Writer<rapidjson::OStreamWrapper> writer(outputStreamWrapper);
            jsonDoc.Accept(writer);

            std::cout << "JSON file modified and saved successfully." << std::endl;
        }
        else {
            std::cout << "Failed to open input file." << std::endl;
            return;
        }

        return;
    }
}


void dae::ScoreObserver::WriteScore(const int score, const char* input, rapidjson::Document& jsonDoc, std::shared_ptr<BlackBoard> blackboard) {
    // Modify the JSON elements
    if (jsonDoc.HasMember("Highscores") && jsonDoc["Highscores"].IsArray()) {
        rapidjson::Value& highScores = jsonDoc["Highscores"];
        rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();

        rapidjson::SizeType insertIndex = 0;

        // Find the position to insert the new score
        for (; insertIndex < highScores.Size(); ++insertIndex) {
            const rapidjson::Value& highScore = highScores[insertIndex];
            if (highScore.HasMember("Highscore") && highScore["Highscore"].IsInt()) {
                if (highScore["Highscore"].GetInt() < score) {
                    break; // Found the position to insert
                }
            }
        }

        // Shift elements to make room for the new score
        highScores.PushBack(rapidjson::Value(), allocator); // Add a new value to the end
        for (rapidjson::SizeType i = highScores.Size() - 1; i > insertIndex; --i) {
            highScores[i].CopyFrom(highScores[i - 1], allocator);
        }

        // Insert the new score at the appropriate position
        rapidjson::Value newScore(rapidjson::kObjectType);

        rapidjson::Value inputName(input, allocator);

        newScore.AddMember("Name", inputName, allocator);
        newScore.AddMember("Highscore", score, allocator);

        highScores[insertIndex].CopyFrom(newScore, allocator);

        // Limit the number of high scores if needed
        const size_t maxHighScores = 10; // Maximum number of high scores
        while (highScores.Size() > maxHighScores) {
            highScores.PopBack();
        }

        if (insertIndex > 9) return;

        //change info on blackboard
        std::vector<std::string> namesBb{};
        std::vector<int> highscoresBb{};

        for (rapidjson::SizeType i{}; i < highScores.Size(); ++i)
        {
            const rapidjson::Value& highScore = highScores[i];

            namesBb.push_back(highScore["Name"].GetString());
            highscoresBb.push_back(highScore["Highscore"].GetInt());
        }

        

        blackboard.get()->Set("Names", namesBb);
        blackboard.get()->Set("Highscores", highscoresBb);

    }
}
