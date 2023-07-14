#include "CProgram2_6.h"

CProgram2_6::CProgram2_6()
	: m_strVertextShader(""),
	m_strFragmentShader(""),
	m_nRenderingProgram(0),
	m_fXPos(0.0f),
	m_fOffsetDir(0.01f)
{

}

void CProgram2_6::Init(GLFWwindow* pWindow, const int nNumVAOs, GLuint arrVAO[])
{
	m_strVertextShader = "GLSL\\CharacterTwo\\program2_6.vert";
	m_strFragmentShader = "GLSL\\CharacterTwo\\program2_6.frag";
	m_nRenderingProgram = ShaderUtil::GenShaderProgram(pWindow, m_strVertextShader, m_strFragmentShader);

	// ����VAO
	glGenVertexArrays(nNumVAOs, arrVAO);
	// ��VAO
	glBindVertexArray(arrVAO[0]);
}

void CProgram2_6::Display(GLFWwindow* pWindow, double dCurrentTime)
{
	// ��ձ���
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// ����ɫ���������
	glUseProgram(m_nRenderingProgram);

	// �ƶ�������
	m_fXPos += m_fOffsetDir;
	// �ﵽһ��λ�ú���
	if (m_fXPos > 1.0f)
	{
		m_fOffsetDir = -0.01f;
	}
	if (m_fXPos < -1.0f)
	{
		m_fOffsetDir = 0.01f;
	}

	// ��ȡΨһ�����ĵ�ַ
	GLuint nOffsetAddress = glGetUniformLocation(m_nRenderingProgram, "fOffset");
	// ��Ψһ������ֵ
	glProgramUniform1f(m_nRenderingProgram, nOffsetAddress, m_fXPos);

	// �������ߴ������
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLuint CProgram2_6::DrawTriangle(GLFWwindow* pWindow, double dCurrentTime)
{
	return GLuint();
}

