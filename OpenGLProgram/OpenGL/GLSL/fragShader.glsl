#version 430

// out标签表示color变量是输出变量, 在顶点着色器中不是必须, 因为gl_Position是预定义的输出变量
out vec4 color;

void main(void)
{
	color = vec4( 0.0, 0.0, 1.0, 1.0);
}