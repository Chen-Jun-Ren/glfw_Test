#version 330 core
out vec4 FragColor;
uniform vec4 color;
in vec3 ourColor;
void main()
{
    FragColor = vec4(ourColor, 1.0f);
   //FragColor = color;
};//片段著色器原始碼