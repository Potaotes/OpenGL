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
	// 初始化GLFW库
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	// 该代码置顶了计算机必须与OpenGL版本 4.3 兼容
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);	// 主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// 次版本号

	// 创建GLFW窗口 参数: 宽, 高, 窗口标题, 允许全屏显示, 允许资源共享
	GLFWwindow* pWindow = glfwCreateWindow(600, 600, "TestTitle", nullptr, nullptr);

	// GLFW窗口默认双缓冲 GLFW窗口并不会自动将其与OpenGL实例以及状态信息（颜色缓冲区等）相关联。调用此函数关联内容
	glfwMakeContextCurrent(pWindow);

	// 初始化GLEW库
	if (glewInit() != GLEW_OK)
	{
		exit(EXIT_FAILURE);
	}

	// 开启垂直同步
	glfwSwapInterval(1);

	// 创建示例对象
	// 第二章
	CProgram2_2* pProgram2_2 = new CProgram2_2();
	CProgram2_5* pProgram2_5 = new CProgram2_5();
	CProgram2_6* pProgram2_6 = new CProgram2_6();

	// 自定义初始化函数
	pProgram2_2->Init(pWindow, numVAOs, arrVAO);
	pProgram2_5->Init(pWindow, numVAOs, arrVAO);
	pProgram2_6->Init(pWindow, numVAOs, arrVAO);

	while (!glfwWindowShouldClose(pWindow))	// 判断窗口是否关闭
	{
		//pProgram2_2->Display(pWindow, glfwGetTime());
		//pProgram2_5->Display(pWindow, glfwGetTime());
		pProgram2_6->Display(pWindow, glfwGetTime());

		glfwSwapBuffers(pWindow);	// 绘制屏幕 交换缓冲区
		glfwPollEvents();	// 处理窗口相关事件（如按键事件）
	}

	// 销毁窗口
	glfwDestroyWindow(pWindow);
	// 终止运行
	glfwTerminate();

	exit(EXIT_SUCCESS);
}