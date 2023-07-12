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
	// 用于将含有两个已编译的着色器程序载入管线阶段(在GPU上), 并没有运行着色器, 只是将着色器加载进硬件
	glUseProgram(nRenderingProgram);

	// 改变像素点大小
	//glPointSize(30.0f);

	// 启动管线处理过程
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void CProgram2_2::Init(GLFWwindow* pWindow, GLuint& nRenderingProgram, const int nNumVAOs, GLuint arrVAO[])
{

	nRenderingProgram = DrawTriangle(pWindow, glfwGetTime());

	// 当准备将数据集发送给管线时，数据集是以缓冲区的形式发送的
	// 创建顶点数组对象(VAO)
	glGenVertexArrays(nNumVAOs, arrVAO);
	glBindVertexArray(arrVAO[0]);
}

GLuint CProgram2_2::DrawAPoint(GLFWwindow* pWindow, double dCurrentTime)
{
	// 错误日志
	GLint nVertexComplied = 0;
	GLint nFragComplied = 0;
	GLint nLinked = 0;

	// 顶点着色器代码
	string strVShaderSource = FileUtil::ReadShaderSource("GLSL\\CharacterTwo\\vertextShader.vert");
	const GLchar* cVShaderSource = strVShaderSource.c_str();

	// 片段着色器代码
	string strFShaderSource = FileUtil::ReadShaderSource("GLSL\\CharacterTwo\\fragmentShader.frag");
	const GLchar* cFShaderSource = strFShaderSource.c_str();

	// 创建Shader后返回的uint为唯一ID
	GLuint nVShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint nFShader = glCreateShader(GL_FRAGMENT_SHADER);

	// 该函数用于将GLSL代码从字符串载入空着色器对象中
	// 参数: 存放着色器的着色器对象, 着色器代码中的字符串数量, 包含源代码的字符串指针, 
	glShaderSource(nVShader, 1, &cVShaderSource, nullptr);
	glShaderSource(nFShader, 1, &cFShaderSource, nullptr);

	// 编译着色器
	glCompileShader(nVShader);
	// 检测着色器编译错误
	ErrorUtil::CheckOpenGLError();
	glGetShaderiv(nVShader, GL_COMPILE_STATUS, &nVertexComplied);
	if (nVertexComplied != 1)
	{
		cout << "Vertex compilation failed! " << endl;
		ErrorUtil::PrintShaderLog(nVShader);
	}

	// 编译着色器
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

GLuint CProgram2_2::DrawTriangle(GLFWwindow* pWindow, double dCurrentTime)
{
	GLint nVertexComplied = 0;
	GLint nFragComplied = 0;
	GLint nLinked = 0;

	// 加载着色器代码
	string strVertextShader = FileUtil::ReadShaderSource("GLSL\\CharacterTwo\\triangleShader.vert");
	const GLchar* cVShaderSource = strVertextShader.c_str();
	string strFragmentShader = FileUtil::ReadShaderSource("GLSL\\CharacterTwo\\triangleShader.frag");
	const GLchar* vFShaderSource = strFragmentShader.c_str();

	// 创建着色器对象
	GLint nVertShader = glCreateShader(GL_VERTEX_SHADER);
	GLint nFragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// 加载着色器代码进入着色器对象
	glShaderSource(nVertShader, 1, &cVShaderSource, nullptr);
	glShaderSource(nFragShader, 1, &vFShaderSource, nullptr);

	// 编译着色器
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

	// 创建Program对象
	GLint nVFProgram = glCreateProgram();

	// 附加着色器对象到Program对象
	glAttachShader(nVFProgram, nVertShader);
	glAttachShader(nVFProgram, nFragShader);

	// 链接Program对象
	glLinkProgram(nVFProgram);
	ErrorUtil::CheckOpenGLError();
	glGetProgramiv(nVFProgram, GL_LINK_STATUS, &nLinked);
	if (nLinked != 1)
	{
		cout << "Linked Failed! " << endl;
		ErrorUtil::PrintProgramLog(nVFProgram);
	}

	// 返回Program对象
	return nVFProgram;
}
