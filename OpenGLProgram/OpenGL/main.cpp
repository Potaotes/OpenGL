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
	// 初始化GLFW库
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	// 该代码置顶了计算机必须与OpenGL版本 4.3 兼容
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);	// 主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// 此版本号

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

	// 自定义初始化函数
	init(pWindow);

	while (!glfwWindowShouldClose(pWindow))	// 判断窗口是否关闭
	{
		display(pWindow, glfwGetTime());
		glfwSwapBuffers(pWindow);	// 绘制屏幕 交换缓冲区
		glfwPollEvents();
	}

	glfwDestroyWindow(pWindow);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}