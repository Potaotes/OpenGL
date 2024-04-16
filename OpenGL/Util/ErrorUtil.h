#pragma once
#include <GL/glew.h>
#include <iostream>
#include <string>

using namespace std;

class ErrorUtil
{
public:
	/// <summary>
	/// 打印Shader日志
	/// </summary>
	/// <param name="nShaderId"></param>
	static void PrintShaderLog(GLuint nShaderId);

	/// <summary>
	/// 打印Program对象日志
	/// </summary>
	/// <param name="nProg"></param>
	static void PrintProgramLog(int nProgramId);

	/// <summary>
	/// 检测是否有OpenGL错误
	/// </summary>
	/// <returns></returns>
	static bool CheckOpenGLError();
};

