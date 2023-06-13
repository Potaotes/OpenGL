#include "ErrorUtil.h"

void ErrorUtil::PrintShaderLog(GLuint nShaderId)
{
	int nLength = 0;
	int nChWrittn = 0;
	GLchar* pLog;

	glGetShaderiv(nShaderId, GL_INFO_LOG_LENGTH, &nLength);

	if (nLength > 0)
	{
		pLog = (GLchar*)malloc(nLength);
		glGetShaderInfoLog(nShaderId, nLength, &nChWrittn, pLog);

		cout << "Shader Info Log: " << pLog << endl;
		free(pLog);
	}
}

void ErrorUtil::PrintProgramLog(int nProgramId)
{
	int nLength = 0;
	int nChWrittn = 0;
	GLchar* pLog;

	glGetProgramiv(nProgramId, GL_INFO_LOG_LENGTH, &nLength);

	if (nLength > 0)
	{
		pLog = (GLchar*)malloc(nLength);
		glGetProgramInfoLog(nProgramId, nLength, &nChWrittn, pLog);

		cout << "Program Info Log: " << pLog << endl;
		free(pLog);
	}
}

bool ErrorUtil::CheckOpenGLError()
{
	bool bFoundError = false;
	int nGlError = glGetError();

	while (nGlError != GL_NO_ERROR)
	{
		cout << "OpenGL Error: " << nGlError << endl;
		bFoundError = true;
		nGlError = glGetError();
	}

	return bFoundError;
}


