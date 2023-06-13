#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

void init(GLFWwindow* pWindow)
{
	cout << "init" << endl;
}

void display(GLFWwindow* pWindow, double dCurrentTime)
{
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
	// ��ʼ��GLFW��
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	// �ô����ö��˼����������OpenGL�汾 4.3 ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);	// ���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// �˰汾��

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
		display(pWindow, glfwGetTime());
		glfwSwapBuffers(pWindow);	// ������Ļ ����������
		glfwPollEvents();
	}

	glfwDestroyWindow(pWindow);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}