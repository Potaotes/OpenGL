#include "ShaderUtil.h"

GLint ShaderUtil::GenShaderProgram(GLFWwindow* pWindow, std::string strVertPath, std::string strFragPath)
{
    // ������
    GLint nVertState = GL_TRUE;
    GLint nFragState = GL_TRUE;
    GLint nLinkState = GL_TRUE;

    // ������ɫ������
    string strVertSource = FileUtil::ReadShaderSource(strVertPath);
    const GLchar* cVertSource = strVertSource.c_str();
    string strFragSource = FileUtil::ReadShaderSource(strFragPath);
    const GLchar* cFragSource = strFragSource.c_str();

    // ������ɫ������
    GLint nVertShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLint nFragShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // ���ش��������ɫ������
    glShaderSource(nVertShaderId, 1, &cVertSource, nullptr);
    glShaderSource(nFragShaderId, 1, &cFragSource, nullptr);

    // ������ɫ��
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

    // ����Program����
    GLint nRenderProgramId = glCreateProgram();

    // ����ɫ�����ӵ�Program����
    glAttachShader(nRenderProgramId, nVertShaderId);
    glAttachShader(nRenderProgramId, nFragShaderId);

    // ������ɫ��
	glLinkProgram(nRenderProgramId);
	if (ErrorUtil::CheckOpenGLError())
	{
        ErrorUtil::PrintProgramLog(nRenderProgramId);
	}

    return nRenderProgramId;
}
