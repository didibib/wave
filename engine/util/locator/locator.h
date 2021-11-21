#pragma once

#include "subsystem.h"

namespace Wave
{
	// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	
	class Locator
	{
	public:
		static Locator& GetInstance()
		{
			static Locator instance;
			return instance;
		}

		~Locator()
		{
			for (auto& [key, val] : m_Subsystems)
			{
				val->Shutdown();
				delete val;
				val = nullptr;
			}
			m_Subsystems.clear();
		}

		//@brief Registers and initializes the subsystem
		//@return A pointer the subsystem
		template<typename T>
		T* Register()
		{
			static_assert(std::is_base_of<Subsystem, T>::value, "Locator:: T must inherit from Subsystem.");

			// Create new system
			auto system = new T();

			// Id per type
			int id = GetSubsystemTypeId<T>();

			// Set into map
			m_Subsystems[id] = system;

			system->Init();

			return system;
		}

		template<typename T>
		T* Get()
		{
			static_assert(std::is_base_of<Subsystem, T>::value, "Locator:: T must inherit from Subsystem.");

			// Get id of subsystem type
			int id = GetSubsystemTypeId<T>();

			// If found, return the subsystem
			auto query = m_Subsystems.find(id);
			if (query != m_Subsystems.end())
			{
				return static_cast<T*>(query->second);
			}

			return nullptr;
		}

		template<typename T>
		int GetSubsystemTypeId()
		{
			return typeid(T).hash_code();
		}

		// Singleton requirements
		Locator(Locator const&) = delete;
		void operator=(Locator const&) = delete;
	protected:
		Locator() = default;
	private:
		std::map<int, Subsystem*> m_Subsystems;
	};
}