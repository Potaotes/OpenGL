#pragma once
#include "../Core/CProgramBase.h"

/// <summary>
/// Draw a point
/// </summary>
class CProgram2_2 : CProgramBase
{
public:
	CProgram2_2();
	CProgram2_2(GLFWwindow* pWindow, GLuint nRenderingProgram, int nNumVAOs, GLuint arrVAO[]);

	void Display(GLFWwindow* pWindow, double dCurrentTime, GLuint& nRenderingProgram);
	void Init(GLFWwindow* pWindow, GLuint& nRenderingProgram, const int nNumVAOs, GLuint arrVAO[]);

private:
	GLuint DrawAPoint(GLFWwindow* pWindow, double dCurrentTime);
	GLuint DrawTriangle(GLFWwindow* pWindow, double dCurrentTime);
};

