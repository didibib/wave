#pragma once

namespace Wave
{
#define REDMASK	(0xff0000)
#define GREENMASK (0x00ff00)
#define BLUEMASK (0x0000ff)

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

	typedef unsigned int	uint;
	typedef unsigned char	byte;

	// deterministic rng
	static uint seed = 0x12345678;
	inline uint random_uint()
	{
		seed ^= seed << 13;
		seed ^= seed >> 17;
		seed ^= seed << 5;
		return seed;
	}
	inline float random_float() { return random_uint() * 2.3283064365387e-10f; }
	inline float random_range(float range) { return random_float() * range; }

	class Math
	{
	public:
		static float map(float value, float in_start, float in_stop, float out_start, float out_stop)
		{
			return out_start + (out_stop - out_start) * ((value - in_start) / (in_stop - in_start));
		}		
	};

	class String
	{
	public:
		// https://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
		static std::string get_file_contents(const char* filename)
		{
			std::ifstream in(filename, std::ios::in | std::ios::binary);
			if (in)
			{
				std::string contents;
				in.seekg(0, std::ios::end);
				contents.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&contents[0], contents.size());
				in.close();
				return(contents);
			}
			throw(errno);
		}
	};	
}
