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
	// 错误日志
	GLint nVertexComplied = 0;
	GLint nFragComplied = 0;
	GLint nLinked = 0;

	// 顶点着色器代码
	string strVShaderSource = FileUtil::ReadShaderSource("GLSL\\vertShader.glsl");
	const GLchar* cVShaderSource = strVShaderSource.c_str();
	
	// 片段着色器代码
	string strFShaderSource = FileUtil::ReadShaderSource("GLSL\\fragShader.glsl");
	const GLchar* cFShaderSource = strFShaderSource.c_str();

	// 创建Shader后返回的uint为唯一ID
	GLuint nVShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint nFShader = glCreateShader(GL_FRAGMENT_SHADER);

	// 该函数用于将GLSL代码从字符串载入空着色器对象中
	// 参数: 存放着色器的着色器对象, 着色器代码中的字符串数量, 包含源代码的字符串指针, 
	glShaderSource(nVShader, 1, &cVShaderSource, nullptr);
	glShaderSource(nFShader, 1, &cFShaderSource, nullptr);

	// 稍后介绍
	glCompileShader(nVShader);
	// 检测着色器编译错误
	ErrorUtil::CheckOpenGLError();
	glGetShaderiv(nVShader, GL_COMPILE_STATUS, &nVertexComplied);
	if (nVertexComplied != 1)
	{
		cout << "Vertex compilation failed! " << endl;
		ErrorUtil::PrintShaderLog(nVShader);
	}

	glCompileShader(nFShader);
	// 检测着色器编译错误
	ErrorUtil::CheckOpenGLError();
	glGetShaderiv(nFShader, GL_COMPILE_STATUS, &nFragComplied);
	if (nFragComplied != 1)
	{
		cout << "Fragment compilation failed! " << endl;
		ErrorUtil::PrintShaderLog(nFShader);
	}

	// 创建程序对象
	GLuint nVFProgram = glCreateProgram();

	// 将着色器加入程序对象
	glAttachShader(nVFProgram, nVShader);
	glAttachShader(nVFProgram, nFShader);

	// 请求GLSL编译器, 以确保兼容性
	glLinkProgram(nVFProgram);
	// 检测链接着色器错误
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

	// 当准备将数据集发送给管线时，数据集是以缓冲区的形式发送的
	// 创建顶点数组对象(VAO)
	glGenVertexArrays(numVAOs, arrVAO);
	glBindVertexArray(arrVAO[0]);
}

void display(GLFWwindow* pWindow, double dCurrentTime)
{
	// 填充颜色缓冲区为红色 R,G,B,A
	// glClearColor(1.0, 0.0, 0.0, 1.0);
	// 重置缓冲区颜色 GL_COLOR_BUFFER_BIT包含了渲染后像素的颜色缓冲区
	// glClear(GL_COLOR_BUFFER_BIT);

	// 用于将含有两个已编译的着色器程序载入管线阶段(在GPU上), 并没有运行着色器, 只是将着色器加载进硬件
	glUseProgram(nRenderingProgram);

	// 改变像素点大小
	glPointSize(30.0f);

	// 启动管线处理过程
	glDrawArrays(GL_POINTS, 0, 1);
}

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

	// 自定义初始化函数
	init(pWindow);

	while (!glfwWindowShouldClose(pWindow))	// 判断窗口是否关闭
	{
		display(pWindow, glfwGetTime());	// 自定义绘制函数
		glfwSwapBuffers(pWindow);	// 绘制屏幕 交换缓冲区
		glfwPollEvents();	// 处理窗口相关事件（如按键事件）
	}

	// 销毁窗口
	glfwDestroyWindow(pWindow);
	// 终止运行
	glfwTerminate();

	exit(EXIT_SUCCESS);
}