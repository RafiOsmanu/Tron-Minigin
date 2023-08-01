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
		
		explicit MapCreator(std::shared_ptr<GameObject> pOwner, int numRows);
		~MapCreator() = default;
		MapCreator(const MapCreator&) = delete;
		MapCreator(MapCreator&&) = delete;
		MapCreator& operator= (const MapCreator&) = delete;
		MapCreator& operator= (const MapCreator&&) = delete;

		//Fuctions

		void Update() override;
		void Render() override;

		void CreateMap();
		std::vector<Cube>& GetCubes() { return m_Cubes; }

	protected:
		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }

	private:
		//DataMembers
		int m_NumRows;
		std::vector<Cube> m_Cubes;
	};
}

