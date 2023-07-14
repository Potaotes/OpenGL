#include "CProgram2_5.h"

CProgram2_5::CProgram2_5()
	: m_nRenderingProgram(0)
{
}

CProgram2_5::CProgram2_5(GLFWwindow* pWindow, int nNumVAOs, GLuint arrVAO[])
	: m_nRenderingProgram(0)
{
	Init(pWindow, nNumVAOs, arrVAO);
}

void CProgram2_5::Init(GLFWwindow* pWindow, const int nNumVAOs, GLuint arrVAO[])
{
	m_strVertextShader = "GLSL\\CharacterTwo\\triangleShader.vert";
	m_strFragmentShader = "GLSL\\CharacterTwo\\triangleShader.frag";
	//m_nRenderingProgram = DrawTriangle(pWindow, glfwGetTime());
	m_nRenderingProgram = ShaderUtil::GenShaderProgram(pWindow, m_strVertextShader, m_strFragmentShader);

	// ��׼�������ݼ����͸�����ʱ�����ݼ����Ի���������ʽ���͵�
	// ���������������(VAO)
	glGenVertexArrays(nNumVAOs, arrVAO);
	glBindVertexArray(arrVAO[0]);
}

void CProgram2_5::Display(GLFWwindow* pWindow, double dCurrentTime)
{
	// ���ڽ����������ѱ������ɫ������������߽׶�(��GPU��), ��û��������ɫ��, ֻ�ǽ���ɫ�����ؽ�Ӳ��
	glUseProgram(m_nRenderingProgram);

	// �ı����ص��С
	glPointSize(30.0f);

	// �������ߴ������
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLuint CProgram2_5::DrawTriangle(GLFWwindow* pWindow, double dCurrentTime)
{
	GLint nVertexComplied = 0;
	GLint nFragComplied = 0;
	GLint nLinked = 0;

	// ������ɫ������
	string strVertextShader = FileUtil::ReadShaderSource(m_strVertextShader);
	const GLchar* cVShaderSource = strVertextShader.c_str();
	string strFragmentShader = FileUtil::ReadShaderSource(m_strFragmentShader);
	const GLchar* vFShaderSource = strFragmentShader.c_str();

	// ������ɫ������
	GLint nVertShader = glCreateShader(GL_VERTEX_SHADER);
	GLint nFragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// ������ɫ�����������ɫ������
	glShaderSource(nVertShader, 1, &cVShaderSource, nullptr);
	glShaderSource(nFragShader, 1, &vFShaderSource, nullptr);

	// ������ɫ��
	glCompileShader(nVertShader);
	ErrorUtil::CheckOpenGLError();
	glGetShaderiv(nVertShader, GL_COMPILE_STATUS, &nVertexComplied);
	if (nVertexComplied != 1)
	{
		cout << "Vertex compilation failed! " << endl;
		ErrorUtil::PrintShaderLog(nVertShader);
	}
	glCompileShader(nFragShader);
	ErrorUtil::CheckOpenGLError();
	glGetShaderiv(nFragShader, GL_COMPILE_STATUS, &nVertexComplied);
	if (nVertexComplied != 1)
	{
		cout << "Fragment compilation failed! " << endl;
		ErrorUtil::PrintShaderLog(nFragShader);
	}

	// ����Program����
	GLint nVFProgram = glCreateProgram();

	// ������ɫ������Program����
	glAttachShader(nVFProgram, nVertShader);
	glAttachShader(nVFProgram, nFragShader);

	// ����Program����
	glLinkProgram(nVFProgram);
	ErrorUtil::CheckOpenGLError();
	glGetProgramiv(nVFProgram, GL_LINK_STATUS, &nLinked);
	if (nLinked != 1)
	{
		cout << "Linked Failed! " << endl;
		ErrorUtil::PrintProgramLog(nVFProgram);
	}

	// ����Program����
	return nVFProgram;
}
