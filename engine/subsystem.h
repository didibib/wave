#pragma once 

#include "util/result.h"

namespace Wave
{
	class Subsystem
	{
	public:
		Subsystem() = default;
		~Subsystem() = default;

		virtual void Init() = 0;
		virtual Result Update(const float&) = 0;
		virtual void Shutdown() = 0;
	};
}
