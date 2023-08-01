#include "MapCreator.h"
#include "Renderer.h"
namespace dae
{
    MapCreator::MapCreator(std::shared_ptr<GameObject> pOwner, int numRows)
        : m_pOwner(pOwner), 
        m_NumRows(numRows)
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
           // SDL_Rect rect{ static_cast<int>(cube.position.x), static_cast<int>(cube.position.y), static_cast<int>(cube.size), static_cast<int>(cube.size / 2) };
           // Renderer::GetInstance().DrawRect(rect);
           
        }
    }

    void MapCreator::CreateMap()
    {
        const float cubeSize{ 37.f }; // The size of each cube in pixels
        const int xOffset{ 250 }; // The x-offset from the left edge of the viewport
        const int yOffset{ 250 }; // The y-offset from the top edge of the viewport

        for (int row{}; row < m_NumRows; row++)
        {
            int numCols = row + 1;
            float xRowOffset = (row % 2 == 0) ? cubeSize / 2.f : 0;

            for (int col{}; col < numCols; col++)
            {
                // Calculate the position of the cube in the viewport
                float xPos{ xOffset + xRowOffset + (col - row / 2) * cubeSize };
                float yPos{ yOffset + row * cubeSize/1.35f };



                // Create a new cube object with the appropriate position
                Cube cube;
                cube.size = cubeSize;
                cube.position = { xPos, yPos };
                cube.texture = ResourceManager::GetInstance().LoadTexture("InactiveCube.png");

                // Add the cube object to the list of cubes
                m_Cubes.emplace_back(cube);
            }
        }
    }
}