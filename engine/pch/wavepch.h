#pragma once

// STD headers
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
// GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/fast_square_root.hpp"
// FreeImage
#include "FreeImage.h"
// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// Utility
#include "util/logger/logger.h"
#include "util/locator/locator.h"
#include "util/util.h"
#include "scene/mesh/vertex.h"
#include "scene/texture/texture.h"

#ifndef WAVE_OPENGL_VERSION
#define WAVE_OPENGL_VERSION 410
#endif // !WAVE_OPENGL_VERSION
#define WAVE_OPENGL_VERSION_MAJ (WAVE_OPENGL_VERSION / 100) 
#define WAVE_OPENGL_VERSION_MIN ((WAVE_OPENGL_VERSION % 100) / 10)

