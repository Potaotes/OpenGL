#version 430

void main(void)
{
    // gl_Position变量无需指定out字段。其本身即为预定义的输出变量
	gl_Position = vec4( 0.0, 0.0, 0.0, 1.0);
}

