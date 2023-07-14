#include "../Core/CProgramBase.h"
#include "ShaderUtil.h"

#pragma once
class CProgram2_5 : CProgramBase
{
public:
	CProgram2_5();
	CProgram2_5(GLFWwindow* pWindow, int nNumVAOs, GLuint arrVAO[]);

	void Display(GLFWwindow* pWindow, double dCurrentTime);
	void Init(GLFWwindow* pWindow, const int nNumVAOs, GLuint arrVAO[]);

private:
	GLuint DrawTriangle(GLFWwindow* pWindow, double dCurrentTime);

	GLint m_nRenderingProgram;
	string m_strVertextShader;
	string m_strFragmentShader;
};

