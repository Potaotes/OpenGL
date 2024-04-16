#version 430

// out表明了color变量是输出变量。
out vec4 color;

void main(void)
{
    // gl_FragCoord 表示当前片元着色器处理的候选片元窗口相对坐标信息。类型为vec4
    if (gl_FragCoord.x < 295)
    {
        color = vec4( 1.0, 0.0, 0.0, 1.0 );
    }
    else
    {
        color = vec4( 0.0, 0.0, 1.0, 1.0 );
    };
}