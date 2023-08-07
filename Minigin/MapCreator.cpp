#include "MapCreator.h"
#include "Renderer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include "rapidjson.h"
#include "document.h"
#include "stream.h"
#include "filereadstream.h"
#include "istreamwrapper.h"

namespace dae
{
    MapCreator::MapCreator(std::shared_ptr<GameObject> pOwner)
        : m_pOwner(pOwner)
    {
        CreateMap();
    }

    void MapCreator::Update()
	{
       
	}

    void MapCreator::Render()
    {
        // Render cubes
        for (const auto& cube : m_Cubes)
        {
            // Render cube texture
            Renderer::GetInstance().RenderTexture(*cube.texture, cube.position.x, cube.position.y, cube.size, cube.size);

            // Draw rectangle around cube
           //SDL_Rect rect{ static_cast<int>(cube.position.x), static_cast<int>(cube.position.y), static_cast<int>(cube.size), static_cast<int>(cube.size) };
           //Renderer::GetInstance().DrawRect(rect);
           
        }
    }

    void MapCreator::CreateMap()
    {

        using rapidjson::Document;
        Document jsonDoc;

        std::ifstream inputFile{ "C:/DAE/RETAKES/progg 4/Tron-Minigin/Data/Layout/LevelLayout0.json" };
        if (!inputFile.is_open())
        {
            // File opening failed, handle the error
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        rapidjson::IStreamWrapper inputFileWrapper{ inputFile };
        jsonDoc.ParseStream(inputFileWrapper);

        Cube cube;
        cube.size = 8.f;
        cube.position = { 0,0 };
        int mapWidth{ 0 };

        for (const auto& value : jsonDoc.GetArray())
        {
           
            //switch for value 
            switch (value.GetInt())
            {
            case 0:
                cube.texture = ResourceManager::GetInstance().LoadTexture("Level/wall.png");
                cube.cubeType = dae::MapTerrain::wall;
                break;

            case 1:
                cube.texture = ResourceManager::GetInstance().LoadTexture("Level/void.png");
                cube.cubeType = dae::MapTerrain::voidTile;
                break;

            case 2:
                cube.texture = ResourceManager::GetInstance().LoadTexture("Level/path.png");
                cube.cubeType = dae::MapTerrain::path;
                break;

            case 3:
                cube.texture = ResourceManager::GetInstance().LoadTexture("Level/teleport.png");
                cube.cubeType = dae::MapTerrain::teleport;
                break;

            case 4:
                cube.texture = ResourceManager::GetInstance().LoadTexture("Level/path.png");
                cube.cubeType = dae::MapTerrain::teleport;
                break;
            }

            m_Cubes.emplace_back(cube);

            mapWidth++;
            if (mapWidth / 58.f == 1)
            {
                mapWidth = 0;
                cube.position.x = 0;
                cube.position.y += cube.size;
            }
            else
            {
                cube.position.x += cube.size;
            }


        }

    }
}


//OLD CODE
            //const float cubeSize{ 37.f }; // The size of each cube in pixels
            //const int xOffset{ 250 }; // The x-offset from the left edge of the viewport
            //const int yOffset{ 250 }; // The y-offset from the top edge of the viewport

            //for (int row{}; row < m_NumRows; row++)
            //{
            //    int numCols = row + 1;
            //    float xRowOffset = (row % 2 == 0) ? cubeSize / 2.f : 0;

            //    for (int col{}; col < numCols; col++)
            //    {
            //        // Calculate the position of the cube in the viewport
            //        float xPos{ xOffset + xRowOffset + (col - row / 2) * cubeSize };
            //        float yPos{ yOffset + row * cubeSize/1.35f };

            //        // Create a new cube object with the appropriate position
            //        Cube cube;
            //        cube.size = cubeSize;
            //        cube.position = { xPos, yPos };
            //        cube.texture = ResourceManager::GetInstance().LoadTexture("InactiveCube.png");

            //        // Add the cube object to the list of cubes
            //        m_Cubes.emplace_back(cube);
            //    }
            //}