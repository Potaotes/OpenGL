#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

using namespace std;

class FileUtil
{
public:
	static string ReadShaderSource(string strFilePath);
};

