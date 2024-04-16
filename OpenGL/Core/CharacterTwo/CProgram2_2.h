#pragma once
#include "../Core/CProgramBase.h"

/// <summary>
/// Draw a point
/// </summary>
class CProgram2_2 : CProgramBase
{
public:
	CProgram2_2();
	CProgram2_2(GLFWwindow* pWindow, int nNumVAOs, GLuint arrVAO[]);

	void Display(GLFWwindow* pWindow, double dCurrentTime);
	void Init(GLFWwindow* pWindow, const int nNumVAOs, GLuint arrVAO[]);

private:
	GLuint DrawAPoint(GLFWwindow* pWindow, double dCurrentTime);

	GLint m_nRenderingProgram;
	string m_strVertextShader;
	string m_strFragmentShader;
};

