#pragma once

// C++ headers
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <fstream>
#include <string>
#include <cerrno>
#include <optional>
#include <charconv>
#include <unordered_set>
// External dependencies
// Include glad before glfw!
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#ifdef _WIN32
#include "GLFW/glfw3native.h"
#endif

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/fast_square_root.hpp"

#include "FreeImage.h"
// Utility
#include "util/log.h"
#include "util/util.h"

namespace Wave
{
	// Order of these enum is important
	enum class Direction { Forward, Right, Up, Backward, Left, Down };
}

#ifndef WAVE_OPENGL_VERSION
#define WAVE_OPENGL_VERSION 410
#endif // !WAVE_OPENGL_VERSION
#define WAVE_OPENGL_VERSION_MAJ (WAVE_OPENGL_VERSION / 100) 
#define WAVE_OPENGL_VERSION_MIN ((WAVE_OPENGL_VERSION % 100) / 10)

