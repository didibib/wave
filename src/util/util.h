#pragma once

namespace Wave
{
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

	typedef unsigned int	uint;
	typedef unsigned char	byte;

	enum class Direction { Forward, Right, Up, Backward, Left, Down };
	enum class TextureType { Diffuse, Specular, Height };
	inline std::string TextureTypeToString(const TextureType& type)
	{
		static std::string strings[] = {
			"diffuse",
			"specular",
			"height"
		};
		return strings[(int)type];
	}

	namespace Random
	{
		// Deterministic rng
		static uint seed = 0x12345678;
		inline uint Uint()
		{
			seed ^= seed << 13;
			seed ^= seed >> 17;
			seed ^= seed << 5;
			return seed;
		}
		inline float Float() { return Uint() * 2.3283064365387e-10f; }
		inline float Range(float range) { return Float() * range; }
	}

	namespace Math
	{
		inline float Map(float value, float in_start, float in_stop, float out_start, float out_stop)
		{
			return out_start + (out_stop - out_start) * ((value - in_start) / (in_stop - in_start));
		}
	};

	namespace String
	{
		// https://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
		inline std::string GetFileContents(const char* filename)
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

	namespace Asset
	{
		inline std::string GetDirectory()
		{
			// WAVE_ASSETS_DIR is set during cmake building in wave/CMakeLists.txt
			static std::string assetDir = TOSTRING(WAVE_ASSETS_DIR);
			return assetDir;
		}
	}
}
