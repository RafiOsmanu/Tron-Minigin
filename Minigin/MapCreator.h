#pragma once
#include <vector>
#include "BaseComponent.h"
#include "ResourceManager.h"
#include "DataTypes.h"


namespace dae
{
	class MapCreator : public BaseComponent
	{
		std::weak_ptr<GameObject> m_pOwner;
	public:
		
		explicit MapCreator(std::shared_ptr<GameObject> pOwner);
		~MapCreator() = default;
		MapCreator(const MapCreator&) = delete;
		MapCreator(MapCreator&&) = delete;
		MapCreator& operator= (const MapCreator&) = delete;
		MapCreator& operator= (const MapCreator&&) = delete;

		//Fuctions
		void Update() override;
		void Render() override;

		void CreateMap(std::string mapAdress, int colorIndicator);
		bool mapIsLoaded() { return m_MapIsLoaded; }
		std::vector<Cube>& GetCubes() { return m_Cubes; }

		void GoToNextMap();

	protected:
		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }

	private:
		//DataMembers
		std::vector<Cube> m_Cubes;

		std::vector<Cube> m_Level1;
		std::vector<Cube> m_Level2;
		std::vector<Cube> m_Level3;

		Cube m_WallTileL1;
		Cube m_WallTileL2;
		Cube m_WallTileL3;


		Cube m_VoidTile;
		Cube m_TeleportTile;
		Cube m_PathTile;
		
		bool m_AllmapsLoaded{ false };
	
		void RenderCube(const Cube& cube);

		int m_mapIndicator{0};

		float m_Timer{};
		float m_TimeToNextMap{ 1.f };
		bool m_StartTimer{ false };
		bool m_MapIsLoaded{ false };
	};
}

