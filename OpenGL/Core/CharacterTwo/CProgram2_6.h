#include "../Core/CProgramBase.h"
#include "ShaderUtil.h"

#pragma once
class CProgram2_6
{
public:
	CProgram2_6();

	void Init(GLFWwindow* pWindow, const int nNumVAOs, GLuint arrVAO[]);
	void Display(GLFWwindow* pWindow, double dCurrentTime);

private:
	GLuint DrawTriangle(GLFWwindow* pWindow, double dCurrentTime);

	GLint m_nRenderingProgram;
	string m_strVertextShader;
	string m_strFragmentShader;

	GLfloat m_fXPos;
	GLfloat m_fOffsetDir;
};

