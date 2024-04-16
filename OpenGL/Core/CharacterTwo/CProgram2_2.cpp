#include "CProgram2_2.h"

CProgram2_2::CProgram2_2()
	: m_nRenderingProgram(0)
{

}

CProgram2_2::CProgram2_2(GLFWwindow* pWindow, int nNumVAOs, GLuint arrVAO[])
	: m_nRenderingProgram(0)
{
	Init(pWindow, nNumVAOs, arrVAO);
}

void CProgram2_2::Display(GLFWwindow* pWindow, double dCurrentTime)
{
	// ���ڽ����������ѱ������ɫ������������߽׶�(��GPU��), ��û��������ɫ��, ֻ�ǽ���ɫ�����ؽ�Ӳ��
	glUseProgram(m_nRenderingProgram);

	// �ı����ص��С
	glPointSize(30.0f);

	// �������ߴ������
	glDrawArrays(GL_POINTS, 0, 3);
}

void CProgram2_2::Init(GLFWwindow* pWindow, const int nNumVAOs, GLuint arrVAO[])
{
	m_strVertextShader = "GLSL\\CharacterTwo\\vertextShader.vert";
	m_strFragmentShader = "GLSL\\CharacterTwo\\fragmentShader.frag";
	m_nRenderingProgram = DrawAPoint(pWindow, glfwGetTime());

	// ��׼�������ݼ����͸�����ʱ�����ݼ����Ի���������ʽ���͵�
	// ���������������(VAO)
	glGenVertexArrays(nNumVAOs, arrVAO);
	glBindVertexArray(arrVAO[0]);
}

GLuint CProgram2_2::DrawAPoint(GLFWwindow* pWindow, double dCurrentTime)
{
	// ������־
	GLint nVertexComplied = 0;
	GLint nFragComplied = 0;
	GLint nLinked = 0;

	// ������ɫ������
	string strVShaderSource = FileUtil::ReadShaderSource(m_strVertextShader);
	const GLchar* cVShaderSource = strVShaderSource.c_str();

	// Ƭ����ɫ������
	string strFShaderSource = FileUtil::ReadShaderSource(m_strFragmentShader);
	const GLchar* cFShaderSource = strFShaderSource.c_str();

	// ����Shader�󷵻ص�uintΪΨһID
	GLuint nVShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint nFShader = glCreateShader(GL_FRAGMENT_SHADER);

	// �ú������ڽ�GLSL������ַ����������ɫ��������
	// ����: �����ɫ������ɫ������, ��ɫ�������е��ַ�������, ����Դ������ַ���ָ��, 
	glShaderSource(nVShader, 1, &cVShaderSource, nullptr);
	glShaderSource(nFShader, 1, &cFShaderSource, nullptr);

	// ������ɫ��
	glCompileShader(nVShader);
	// �����ɫ���������
	ErrorUtil::CheckOpenGLError();
	glGetShaderiv(nVShader, GL_COMPILE_STATUS, &nVertexComplied);
	if (nVertexComplied != 1)
	{
		cout << "Vertex compilation failed! " << endl;
		ErrorUtil::PrintShaderLog(nVShader);
	}

	// ������ɫ��
	glCompileShader(nFShader);
	// �����ɫ���������
	ErrorUtil::CheckOpenGLError();
	glGetShaderiv(nFShader, GL_COMPILE_STATUS, &nFragComplied);
	if (nFragComplied != 1)
	{
		cout << "Fragment compilation failed! " << endl;
		ErrorUtil::PrintShaderLog(nFShader);
	}

	// �����������
	GLuint nVFProgram = glCreateProgram();

	// ����ɫ������������
	glAttachShader(nVFProgram, nVShader);
	glAttachShader(nVFProgram, nFShader);

	// ����GLSL������, ��ȷ��������
	glLinkProgram(nVFProgram);
	// ���������ɫ������
	ErrorUtil::CheckOpenGLError();
	glGetProgramiv(nVFProgram, GL_LINK_STATUS, &nLinked);
	if (nLinked != 1)
	{
		cout << "Linked Failed! " << endl;
		ErrorUtil::PrintProgramLog(nVFProgram);
	}

	return nVFProgram;
}
