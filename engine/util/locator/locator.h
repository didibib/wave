#pragma once

#include "util/singleton.h"

namespace Wave
{
	// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	class Subsystem;

	class Locator
	{
	public:
		static Locator& GetInstance()
		{
			static Locator instance;
			return instance;
		}
		template<typename T>
		std::shared_ptr<T> Register()
		{
			static_assert(std::is_base_of<Subsystem, T>::value, "Locator:: T must inherit from Subsystem.");

			// Create new system
			auto system = std::make_shared<T>();

			// Set into map
			// TODO: Base id on type 
			static int id = 0;
			m_Subsystems[id++] = system;

			return system;
		}
		// Singleton requirements
		Locator(Locator const&) = delete;
		void operator=(Locator const&) = delete;
	protected:
		Locator() = default;

	private:
		std::map<int, std::shared_ptr<Subsystem>> m_Subsystems;
	};
}