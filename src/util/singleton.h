#pragma once 

namespace Wave
{
	// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	template<typename T>
	class Singleton
	{
	public:
		static T& GetInstance()
		{
			// Guaranteed to be destroyed.
			// Instantiated on first use.
			static T instance;
			return instance;
		}
		// C++ 11, We can use the better technique of deleting the methods we don't want.
		Singleton(const Singleton&) = delete;
		void operator=(const Singleton&) = delete;
		// Note: Scott Meyers mentions in his Effective Modern
		//       C++ book, that deleted functions should generally
		//       be public as it results in better error messages
		//       due to the compilers behavior to check accessibility
		//       before deleted status
	protected:
		Singleton() {};
	};
}