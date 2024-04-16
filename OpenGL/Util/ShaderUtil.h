
#pragma once

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "FileUtil.h"
#include "ErrorUtil.h"

class ShaderUtil
{
public:
	static GLint GenShaderProgram(GLFWwindow* pWindow, std::string strVertPath, std::string strFragPath);
};

