#include "FileUtil.h"

string FileUtil::ReadShaderSource(string strFilePath)
{
	string strContent = "";
	ifstream fileStream(strFilePath, ios::in);
	string line = "";

	while (!fileStream.eof())
	{
		getline(fileStream, line);
		strContent.append(line + "\n");
	}

	fileStream.close();

	return strContent;
}
