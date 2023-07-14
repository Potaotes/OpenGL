#include "ShaderUtil.h"

GLint ShaderUtil::GenShaderProgram(GLFWwindow* pWindow, std::string strVertPath, std::string strFragPath)
{
    // 错误码
    GLint nVertState = GL_TRUE;
    GLint nFragState = GL_TRUE;
    GLint nLinkState = GL_TRUE;

    // 加载着色器代码
    string strVertSource = FileUtil::ReadShaderSource(strVertPath);
    const GLchar* cVertSource = strVertSource.c_str();
    string strFragSource = FileUtil::ReadShaderSource(strFragPath);
    const GLchar* cFragSource = strFragSource.c_str();

    // 创建着色器对象
    GLint nVertShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLint nFragShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // 加载代码进入着色器对象
    glShaderSource(nVertShaderId, 1, &cVertSource, nullptr);
    glShaderSource(nFragShaderId, 1, &cFragSource, nullptr);

    // 编译着色器
	glCompileShader(nVertShaderId);
	ErrorUtil::PrintShaderLog(nVertShaderId);
    if (ErrorUtil::CheckOpenGLError())
    {
        ErrorUtil::PrintShaderLog(nVertShaderId);
    }
	glCompileShader(nFragShaderId);
	ErrorUtil::PrintShaderLog(nFragShaderId);
	if (ErrorUtil::CheckOpenGLError())
	{
		ErrorUtil::PrintShaderLog(nFragShaderId);
	}

    // 创建Program对象
    GLint nRenderProgramId = glCreateProgram();

    // 将着色器附加到Program对象
    glAttachShader(nRenderProgramId, nVertShaderId);
    glAttachShader(nRenderProgramId, nFragShaderId);

    // 链接着色器
	glLinkProgram(nRenderProgramId);
	if (ErrorUtil::CheckOpenGLError())
	{
        ErrorUtil::PrintProgramLog(nRenderProgramId);
	}

    return nRenderProgramId;
}
