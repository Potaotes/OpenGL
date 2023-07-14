#include "CProgram2_5.h"

CProgram2_5::CProgram2_5()
	: m_nRenderingProgram(0)
{
}

CProgram2_5::CProgram2_5(GLFWwindow* pWindow, int nNumVAOs, GLuint arrVAO[])
	: m_nRenderingProgram(0)
{
	Init(pWindow, nNumVAOs, arrVAO);
}

void CProgram2_5::Init(GLFWwindow* pWindow, const int nNumVAOs, GLuint arrVAO[])
{
	m_strVertextShader = "GLSL\\CharacterTwo\\triangleShader.vert";
	m_strFragmentShader = "GLSL\\CharacterTwo\\triangleShader.frag";
	//m_nRenderingProgram = DrawTriangle(pWindow, glfwGetTime());
	m_nRenderingProgram = ShaderUtil::GenShaderProgram(pWindow, m_strVertextShader, m_strFragmentShader);

	// 当准备将数据集发送给管线时，数据集是以缓冲区的形式发送的
	// 创建顶点数组对象(VAO)
	glGenVertexArrays(nNumVAOs, arrVAO);
	glBindVertexArray(arrVAO[0]);
}

void CProgram2_5::Display(GLFWwindow* pWindow, double dCurrentTime)
{
	// 用于将含有两个已编译的着色器程序载入管线阶段(在GPU上), 并没有运行着色器, 只是将着色器加载进硬件
	glUseProgram(m_nRenderingProgram);

	// 改变像素点大小
	glPointSize(30.0f);

	// 启动管线处理过程
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLuint CProgram2_5::DrawTriangle(GLFWwindow* pWindow, double dCurrentTime)
{
	GLint nVertexComplied = 0;
	GLint nFragComplied = 0;
	GLint nLinked = 0;

	// 加载着色器代码
	string strVertextShader = FileUtil::ReadShaderSource(m_strVertextShader);
	const GLchar* cVShaderSource = strVertextShader.c_str();
	string strFragmentShader = FileUtil::ReadShaderSource(m_strFragmentShader);
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
		cout << "Fragment compilation failed! " << endl;
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
