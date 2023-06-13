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
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* pWindow = glfwCreateWindow(600, 600, "TestTitle", nullptr, nullptr);

	glfwMakeContextCurrent(pWindow);

	if (glewInit() != GLEW_OK)
	{
		exit(EXIT_FAILURE);
	}

	glfwSwapInterval(1);

	init(pWindow);

	while (!glfwWindowShouldClose(pWindow))
	{
		display(pWindow, glfwGetTime());
		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}

	glfwDestroyWindow(pWindow);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}