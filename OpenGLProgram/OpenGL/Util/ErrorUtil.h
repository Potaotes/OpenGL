#pragma once
#include <GL/glew.h>
#include <iostream>
#include <string>

using namespace std;

class ErrorUtil
{
public:
	/// <summary>
	/// ��ӡShader��־
	/// </summary>
	/// <param name="nShaderId"></param>
	static void PrintShaderLog(GLuint nShaderId);

	/// <summary>
	/// ��ӡProgram������־
	/// </summary>
	/// <param name="nProg"></param>
	static void PrintProgramLog(int nProgramId);

	/// <summary>
	/// ����Ƿ���OpenGL����
	/// </summary>
	/// <returns></returns>
	static bool CheckOpenGLError();
};

