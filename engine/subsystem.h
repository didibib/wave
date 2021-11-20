#pragma once 

#include "util/result.h"

namespace Wave
{
	class Subsystem
	{
		friend Locator;
	public:
		Subsystem() = default;
		~Subsystem() = default;

		virtual void Init() = 0;
		virtual Result Update(const float&) = 0;
		int GetId()
		{
			return m_Id;
		}

	private:
		int m_Id = 0;
	};
}
