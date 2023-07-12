#include "CProgram2_2.h"

CProgram2_2::CProgram2_2()
{

}

CProgram2_2::CProgram2_2(GLFWwindow* pWindow, GLuint nRenderingProgram, int nNumVAOs, GLuint arrVAO[])
{
	Init(pWindow, nRenderingProgram, nNumVAOs, arrVAO);
}

void CProgram2_2::Display(GLFWwindow* pWindow, double dCurrentTime, GLuint& nRenderingProgram)
{
	// ���ڽ����������ѱ������ɫ������������߽׶�(��GPU��), ��û��������ɫ��, ֻ�ǽ���ɫ�����ؽ�Ӳ��
	glUseProgram(nRenderingProgram);

	// �ı����ص��С
	//glPointSize(30.0f);

	// �������ߴ������
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void CProgram2_2::Init(GLFWwindow* pWindow, GLuint& nRenderingProgram, const int nNumVAOs, GLuint arrVAO[])
{

	nRenderingProgram = DrawTriangle(pWindow, glfwGetTime());

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
	string strVShaderSource = FileUtil::ReadShaderSource("GLSL\\CharacterTwo\\vertextShader.vert");
	const GLchar* cVShaderSource = strVShaderSource.c_str();

	// Ƭ����ɫ������
	string strFShaderSource = FileUtil::ReadShaderSource("GLSL\\CharacterTwo\\fragmentShader.frag");
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

GLuint CProgram2_2::DrawTriangle(GLFWwindow* pWindow, double dCurrentTime)
{
	GLint nVertexComplied = 0;
	GLint nFragComplied = 0;
	GLint nLinked = 0;

	// ������ɫ������
	string strVertextShader = FileUtil::ReadShaderSource("GLSL\\CharacterTwo\\triangleShader.vert");
	const GLchar* cVShaderSource = strVertextShader.c_str();
	string strFragmentShader = FileUtil::ReadShaderSource("GLSL\\CharacterTwo\\triangleShader.frag");
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
		cout << "Vertex compilation failed! " << endl;
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
