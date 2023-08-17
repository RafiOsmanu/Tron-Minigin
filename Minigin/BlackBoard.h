#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <string>
#include <any>

namespace dae
{
	class BlackBoard final
	{
	public:
		template<typename T>
		void Set(const std::string& key, const T& value)
		{
			m_Data[key] = value;
		}

		template<typename T>
		T Get(const std::string& key) const
		{
			if (m_Data.find(key) != m_Data.end())
			{
				try
				{
					return std::any_cast<T>(m_Data.at(key));
				}
				catch (const std::bad_any_cast&)
				{
					throw std::exception("Failed to cast value to requested type");
				}
			}

			return T();
		}

		bool Contains(const std::string& key) const
		{
			return m_Data.find(key) != m_Data.end();
		}

	private:
		std::unordered_map<std::string, std::any> m_Data;
	};
	
}

