#pragma once

#include "renderer/opengl/opengl.h"

#include <iostream>

#ifdef _DEBUG
#define glCheck() {GLenum glError = glGetError(); if(glError) std::cout << "GL Error " << glError << ", file " << __FILE__ << ", line " << __LINE__ << std::endl;}
#else
#define glCheck()
#endif