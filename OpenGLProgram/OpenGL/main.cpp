#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Util/FileUtil.h"
#include "Util/ErrorUtil.h"

#include "../Core/CharacterTwo/CProgram2_2.h"
#include "../Core/CharacterTwo/CProgram2_5.h"
#include "../Core/CharacterTwo/CProgram2_6.h"

constexpr int numVAOs = 1;

using namespace std;

extern GLuint nRenderingProgram = 0;
extern GLuint arrVAO[numVAOs] = {};

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

	// ����ʾ������
	// �ڶ���
	CProgram2_2* pProgram2_2 = new CProgram2_2();
	CProgram2_5* pProgram2_5 = new CProgram2_5();
	CProgram2_6* pProgram2_6 = new CProgram2_6();

	// �Զ����ʼ������
	pProgram2_2->Init(pWindow, numVAOs, arrVAO);
	pProgram2_5->Init(pWindow, numVAOs, arrVAO);
	pProgram2_6->Init(pWindow, numVAOs, arrVAO);

	while (!glfwWindowShouldClose(pWindow))	// �жϴ����Ƿ�ر�
	{
		//pProgram2_2->Display(pWindow, glfwGetTime());
		//pProgram2_5->Display(pWindow, glfwGetTime());
		pProgram2_6->Display(pWindow, glfwGetTime());

		glfwSwapBuffers(pWindow);	// ������Ļ ����������
		glfwPollEvents();	// ����������¼����簴���¼���
	}

	// ���ٴ���
	glfwDestroyWindow(pWindow);
	// ��ֹ����
	glfwTerminate();

	exit(EXIT_SUCCESS);
}