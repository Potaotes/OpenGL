#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Util/FileUtil.h"
#include "Util/ErrorUtil.h"

constexpr int numVAOs = 1;

using namespace std;

extern GLuint nRenderingProgram = 0;
extern GLuint arrVAO[numVAOs] = {};

GLuint drawAPoint(GLFWwindow* pWindow, double dCurrentTime)
{
	// ������־
	GLint nVertexComplied = 0;
	GLint nFragComplied = 0;
	GLint nLinked = 0;

	// ������ɫ������
	string strVShaderSource = FileUtil::ReadShaderSource("GLSL\\vertShader.glsl");
	const GLchar* cVShaderSource = strVShaderSource.c_str();
	
	// Ƭ����ɫ������
	string strFShaderSource = FileUtil::ReadShaderSource("GLSL\\fragShader.glsl");
	const GLchar* cFShaderSource = strFShaderSource.c_str();

	// ����Shader�󷵻ص�uintΪΨһID
	GLuint nVShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint nFShader = glCreateShader(GL_FRAGMENT_SHADER);

	// �ú������ڽ�GLSL������ַ����������ɫ��������
	// ����: �����ɫ������ɫ������, ��ɫ�������е��ַ�������, ����Դ������ַ���ָ��, 
	glShaderSource(nVShader, 1, &cVShaderSource, nullptr);
	glShaderSource(nFShader, 1, &cFShaderSource, nullptr);

	// �Ժ����
	glCompileShader(nVShader);
	// �����ɫ���������
	ErrorUtil::CheckOpenGLError();
	glGetShaderiv(nVShader, GL_COMPILE_STATUS, &nVertexComplied);
	if (nVertexComplied != 1)
	{
		cout << "Vertex compilation failed! " << endl;
		ErrorUtil::PrintShaderLog(nVShader);
	}

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

void init(GLFWwindow* pWindow)
{
	nRenderingProgram = drawAPoint(pWindow, glfwGetTime());

	// ��׼�������ݼ����͸�����ʱ�����ݼ����Ի���������ʽ���͵�
	// ���������������(VAO)
	glGenVertexArrays(numVAOs, arrVAO);
	glBindVertexArray(arrVAO[0]);
}

void display(GLFWwindow* pWindow, double dCurrentTime)
{
	// �����ɫ������Ϊ��ɫ R,G,B,A
	// glClearColor(1.0, 0.0, 0.0, 1.0);
	// ���û�������ɫ GL_COLOR_BUFFER_BIT��������Ⱦ�����ص���ɫ������
	// glClear(GL_COLOR_BUFFER_BIT);

	// ���ڽ����������ѱ������ɫ������������߽׶�(��GPU��), ��û��������ɫ��, ֻ�ǽ���ɫ�����ؽ�Ӳ��
	glUseProgram(nRenderingProgram);

	// �ı����ص��С
	glPointSize(30.0f);

	// �������ߴ������
	glDrawArrays(GL_POINTS, 0, 1);
}

int main(void)
{
	// ��ʼ��GLFW��
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	// �ô����ö��˼����������OpenGL�汾 4.3 ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);	// ���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// �ΰ汾��

	// ����GLFW���� ����: ��, ��, ���ڱ���, ����ȫ����ʾ, ������Դ����
	GLFWwindow* pWindow = glfwCreateWindow(600, 600, "TestTitle", nullptr, nullptr);

	// GLFW����Ĭ��˫���� GLFW���ڲ������Զ�������OpenGLʵ���Լ�״̬��Ϣ����ɫ�������ȣ�����������ô˺�����������
	glfwMakeContextCurrent(pWindow);

	// ��ʼ��GLEW��
	if (glewInit() != GLEW_OK)
	{
		exit(EXIT_FAILURE);
	}

	// ������ֱͬ��
	glfwSwapInterval(1);

	// �Զ����ʼ������
	init(pWindow);

	while (!glfwWindowShouldClose(pWindow))	// �жϴ����Ƿ�ر�
	{
		display(pWindow, glfwGetTime());	// �Զ�����ƺ���
		glfwSwapBuffers(pWindow);	// ������Ļ ����������
		glfwPollEvents();	// ����������¼����簴���¼���
	}

	// ���ٴ���
	glfwDestroyWindow(pWindow);
	// ��ֹ����
	glfwTerminate();

	exit(EXIT_SUCCESS);
}