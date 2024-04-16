#version 430

void main()
{
    // gl_VertextID 是OpenGL的内置变量，为当前被处理的顶点的索引。每个顶点运行时ID都不同。
    if (gl_VertexID == 0)
    {
        gl_Position = vec4(0.25, -0.25, 0.0, 1.0);
    }
    else if (gl_VertexID == 1)
    {
        gl_Position = vec4(-0.25, -0.25, 0.0, 1.0);
    }
    else
    {
        gl_Position = vec4(0.25, 0.25, 0.0, 1.0);
    }
}